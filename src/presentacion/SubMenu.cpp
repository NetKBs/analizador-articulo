// SubMenu.cpp
#include "SubMenu.h"
#include <algorithm>
#include <array>
#include <cctype>
#include <cstring>
#include <ncurses.h>
#include <sstream>

#define SCROLL_LINE_STEP 1
#define MARGIN 2

SubMenu::SubMenu() {
  initscr();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
}

SubMenu::~SubMenu() { endwin(); }

void SubMenu::clearScreen() {
  clear();
  refresh();
}

void SubMenu::imprimirMarco(string titulo) {
  int terminal_width = COLS;   // Ancho de la terminal
  int terminal_height = LINES; // Altura de la terminal

  clearScreen();
  attron(COLOR_PAIR(3));
  // Top border
  mvprintw(0, 0, "+");
  for (int i = 1; i < terminal_width - 1; ++i) {
    mvprintw(0, i, "-");
  }
  mvprintw(0, terminal_width - 1, "+");
  // Side borders
  for (int i = 1; i < terminal_height - 1; ++i) {
    mvprintw(i, 0, "|");
    mvprintw(i, terminal_width - 1, "|");
  }
  // Bottom border
  mvprintw(terminal_height - 1, 0, "+");
  for (int i = 1; i < terminal_width - 1; ++i) {
    mvprintw(terminal_height - 1, i, "-");
  }
  mvprintw(terminal_height - 1, terminal_width - 1, "+");
  // Title
  mvprintw(1, (COLS - strlen(titulo.c_str())) / 2, titulo.c_str());
  attroff(COLOR_PAIR(1));
  refresh();
}

void addLineWithWrapping(std::vector<std::string> &lines,
                         const std::string &line, size_t maxLineWidth) {
  size_t start = 0;
  while (start < line.length()) {
    size_t end = start + maxLineWidth;
    if (end > line.length())
      end = line.length();

    // Encuentra el último espacio en blanco para evitar cortar palabras
    if (end < line.length()) {
      size_t lastSpace = line.rfind(' ', end);
      if (lastSpace != std::string::npos && lastSpace > start) {
        end = lastSpace;
      }
    }

    lines.push_back(line.substr(start, end - start));
    start = end + ((end < line.length())
                       ? 1
                       : 0); // Saltar el espacio si no es el final de la línea
  }
}

void SubMenu::imprimirDocumento(string textoProcesado) {

  // Convertir el texto procesado en un vector de strings, cada uno
  // representando una línea
  std::istringstream iss(textoProcesado);
  std::string line;
  std::vector<std::string> lines;
  while (getline(iss, line)) {

    // Verifica si la línea se ajusta dentro del ancho del marco
    int maxLineWidth = COLS - 2 * MARGIN; // Ajuste según el ancho del marco
    if (line.length() <= maxLineWidth) {
      lines.push_back(line);
    } else {
      // Si la línea es más larga, divídela en sublíneas
      for (size_t i = 0; i < line.length(); i += maxLineWidth) {
        lines.push_back(line.substr(i, maxLineWidth));
      }
    }
  }
  // Inicialización para capturar eventos del mouse
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
  keypad(stdscr, TRUE);
  MEVENT event;

  int scroll_offset = 0; // Esto va a llevar el registro de cuánto hemos scrolleado

  // Bucle principal para mostrar el documento y manejar el scroll
  bool quit = false;
  while (!quit) {
    clearScreen(); // Limpia la pantalla antes de volver a dibujar
    imprimirMarco("Documento");

    // Imprimir el documento desde el scroll_offset
    int max_line = LINES - 3; // Ajuste para el espacio vertical del marco
    for (int i = 0; i < max_line && (i + scroll_offset) < lines.size(); ++i) {
        string line = lines[i + scroll_offset];
        if (line.find("Capitulo") != string::npos) {
             attron(COLOR_PAIR(4));
             mvprintw(i + 2, MARGIN, "%s", line.c_str()); // Ajusta para el margen horizontal
             attroff(COLOR_PAIR(4));
        } else {
            mvprintw(i + 2, MARGIN, "%s", line.c_str()); // Ajusta para el margen horizontal
        }
      
    }
    // Capturar eventos
    int ch = getch();
    switch (ch) {
    case KEY_MOUSE:
      if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON4_PRESSED) { // Scroll hacia arriba
          scroll_offset -= SCROLL_LINE_STEP;
          if (scroll_offset < 0)
            scroll_offset = 0;
        } else if (event.bstate & BUTTON5_PRESSED) { // Scroll hacia abajo
          scroll_offset += SCROLL_LINE_STEP;
          if (scroll_offset > lines.size() - max_line)
            scroll_offset = lines.size() - max_line;
        }
      }
      break;
    case 'q': // Presionar 'q' para salir
      quit = true;
      break;
      // Añade más casos si necesitas más controles
    }
  }
}

void SubMenu::imprimirIndicePalabras(
    vector<map<string, set<string>>> indicePalabras) {
  map<string, set<string>> palabrasOrdenadas;

  for (const auto &mapa : indicePalabras) {
    for (const auto &par : mapa) {
      string palabra = par.first;
      set<string> informacion = par.second;
      palabrasOrdenadas[palabra] = informacion;
    }
  }

  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
  keypad(stdscr, TRUE);
  MEVENT event;

  int scroll_offset = 0;
  bool quit = false;

  while (!quit) {
    clearScreen();
    imprimirMarco("Indice de Palabras");

    int max_line = LINES - 3;
    int current_line = 2;

    int i = 0;
    char last_initial = ' ';
    for (const auto &par : palabrasOrdenadas) {
      if (i < scroll_offset) {
        i++;
        continue;
      }

      char current_initial = par.first[0];
      if (current_initial != last_initial) {
        mvprintw(current_line++, MARGIN, "");
        attron(COLOR_PAIR(4));
        mvprintw(current_line++, MARGIN, "----- %c -----", current_initial);
        attroff(COLOR_PAIR(4));
        current_line++;
        last_initial = current_initial;
      }

      // Cada palabra y sus paginas asociada
      string palabra = par.first;
      set<string> paginas = par.second;

      string concatPaginas = "";
      for (const auto &pagina : paginas) {
        if (concatPaginas.empty()) {
          concatPaginas = pagina;
        } else {
          concatPaginas += ", " + pagina;
        }
      }

      mvprintw(current_line++, MARGIN, "%s - %s", palabra.c_str(),
               concatPaginas.c_str());

      if (current_line > max_line) {
        break; // Rompe el bucle si alcanzamos el límite de líneas
      }
    }

    int ch = getch();
    switch (ch) {
    case KEY_MOUSE:
      if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON4_PRESSED) {
          scroll_offset -= SCROLL_LINE_STEP;
          if (scroll_offset < 0)
            scroll_offset = 0;
        } else if (event.bstate & BUTTON5_PRESSED) {
          scroll_offset += SCROLL_LINE_STEP;
          int max_offset = static_cast<int>(indicePalabras.size()) - max_line;
          if (scroll_offset > max_offset)
            scroll_offset = max_offset;
        }
      }
      break;
    case 'q':
      quit = true;
      break;
    }
  }
}

void SubMenu::imprimirEstadisticas(int numeroDeCapitulos, int numeroDeLineas, int numeroDePaginas, int numeroPalabrasTotal, int numeroDePalabrasUnicas) {
  clearScreen();
  imprimirMarco("Estadisticas Del Documento");

  int center = COLS / 2 - 9;

  mvprintw(2, 2, "Numero de capitulos: %d", numeroDeCapitulos);
  mvprintw(3, 2, "Numero de lineas: %d", numeroDeLineas);
  mvprintw(4, 2, "Numero de paginas: %d", numeroDePaginas);
  mvprintw(5, 2, "Numero de palabras totales: %d", numeroPalabrasTotal);
  mvprintw(6, 2, "Numero de palabras unicas: %d", numeroDePalabrasUnicas);

  getch();
}

void SubMenu::buscarUnCapitulo(Documento documento) {
  imprimirMarco(""); // Imprime el marco inicial
  attron(COLOR_PAIR(1));
  echo(); // Habilita el eco de los caracteres ingresados por el usuario
  mvprintw(LINES / 2 - 10, COLS / 2 - 10, "BUSCAR UN CAPITULO");
  attron(COLOR_PAIR(3));
  mvprintw(LINES / 2 - 10 + 2, COLS / 2 - 15, ">>> ");
  attroff(COLOR_PAIR(3));
  attroff(COLOR_PAIR(1));

  char userInput[256];
  getnstr(userInput, sizeof(userInput) - 1);
  noecho(); // Deshabilita el eco de los caracteres

  string nombreCapitulo = userInput;
  pair<bool, vector<string>> resultado =
      documento.getCapituloIndice(nombreCapitulo);

  if (resultado.first) {

    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    keypad(stdscr, TRUE);
    MEVENT event;

    int scroll_offset = 0; // Moved outside the while loop
    bool quit = false;

    while (!quit) {
      clearScreen();
      imprimirMarco("Indice de Capitulo");

      int max_line = LINES - 3;
      int current_line = 2;

      int i = 0;
      char last_initial = ' ';
      for (const auto &palabra : resultado.second) {
        if (i < scroll_offset) {
          i++;
          continue;
        }

        char current_initial = palabra[0];
        if (current_initial != last_initial) {
          mvprintw(current_line++, MARGIN, "");
          attron(COLOR_PAIR(4));
          mvprintw(current_line++, MARGIN, "----- %c -----", current_initial);
          attroff(COLOR_PAIR(4));
          current_line++;
          last_initial = current_initial;
        }

        mvprintw(current_line++, MARGIN, "%s", palabra.c_str());

        if (current_line > max_line) {
          break; // Rompe el bucle si alcanzamos el límite de líneas
        }
      }

      int ch = getch();
      switch (ch) {
      case KEY_MOUSE:
        if (getmouse(&event) == OK) {
          if (event.bstate & BUTTON4_PRESSED) {
            scroll_offset -= SCROLL_LINE_STEP;
            if (scroll_offset < 0)
              scroll_offset = 0;
          } else if (event.bstate & BUTTON5_PRESSED) {
            scroll_offset += SCROLL_LINE_STEP;
            int max_offset = static_cast<int>(resultado.second.size()) - max_line;
            if (scroll_offset > max_offset)
              scroll_offset = max_offset;
          }
        }
        break;
      case 'q':
        quit = true;
        break;
      }
    }

  } else {
    mvprintw(LINES / 2, COLS / 2 - 15, "<< Coincidencias no encontradas >>");
    getch();
  }
}

void SubMenu::imprimirConScroll(const vector<string>& lines) {
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    keypad(stdscr, TRUE);
    MEVENT event;

    int scroll_offset = 0; // Lleva el registro de cuánto hemos scrolleado
    int max_line = LINES - 3; // Ajuste para el espacio vertical del marco

    // Bucle principal para mostrar el contenido y manejar el scroll
    bool quit = false;
    while (!quit) {
        clearScreen(); // Limpia la pantalla antes de volver a dibujar
        imprimirMarco("Resultado de la busqueda");

        // Imprimir el contenido desde scroll_offset
        int max_line_actual = min(max_line, static_cast<int>(lines.size() - scroll_offset));
        for (int i = 0; i < max_line_actual; ++i) {
            mvprintw(i + 2, MARGIN, "%s", lines[i + scroll_offset].c_str()); // Ajusta para el margen horizontal
        }

        // Capturar eventos
        int ch = getch();
        switch (ch) {
            case KEY_MOUSE:
                if (getmouse(&event) == OK) {
                    if (event.bstate & BUTTON4_PRESSED) { // Scroll hacia arriba
                        scroll_offset -= SCROLL_LINE_STEP;
                        if (scroll_offset < 0) scroll_offset = 0;
                    } else if (event.bstate & BUTTON5_PRESSED) { // Scroll hacia abajo
                        scroll_offset += SCROLL_LINE_STEP;
                        if (scroll_offset > lines.size() - max_line) scroll_offset = lines.size() - max_line;
                    }
                }
                break;
            case 'q': // Presionar 'q' para salir
                quit = true;
                break;
            // Agrega más casos si necesitas más controles
        }
    }
}
void SubMenu::EliminarPalabra(Documento &documento) {
  int fila = 3;
  int columna = (COLS - 60) / 2;
  int indice = 0;
  int pagina = 0;
  int elementosPorPagina =
      LINES - 10; // Calcula cuántos elementos caben en una página

  imprimirMarco("");
  attron(COLOR_PAIR(1));
  echo(); // Habilitar el eco de los caracteres ingresados por el usuario
  mvprintw(LINES / 2 - 10, COLS / 2 - 10, "BUSCAR PALABRA");
  attron(COLOR_PAIR(4));
  mvprintw(LINES / 2 - 10 + 2, COLS / 2 - 15, ">>> ");
  attroff(COLOR_PAIR(4));
  attroff(COLOR_PAIR(1));

  char userInput[256];
  getnstr(userInput, sizeof(userInput) - 1);
  noecho();

  // Llama al método eliminarPalabra de la clase Documento
  bool palabraEliminada = documento.eliminarPalabra(userInput);

  if (palabraEliminada) {
    // Realiza las acciones necesarias después de eliminar la palabra
    // Puedes mostrar un mensaje de éxito o realizar otras operaciones
    mvprintw(LINES / 2, COLS / 2 - 17, "<< Palabra eliminada con éxito >>");
  } else {
    // La palabra no se encontró o no se pudo eliminar
    mvprintw(LINES / 2, COLS / 2 - 24,
             "<< Palabra no encontrada o no se pudo eliminar >>");
  }
  getch();
}

void SubMenu::MostrarPalabras(Documento documento) {
  int fila = 3;
  int columna = (COLS - 60) / 2;
  int indice = 0;
  int pagina = 0;
  int elementosPorPagina =
      LINES - 10; // Calcula cuántos elementos caben en una página

  imprimirMarco("");
  attron(COLOR_PAIR(1));
  echo(); // Habilitar el eco de los caracteres ingresados por el usuario
  mvprintw(LINES / 2 - 10, COLS / 2 - 10, "BUSCAR PALABRA");
  attron(COLOR_PAIR(3));
  mvprintw(LINES / 2 - 10 + 2, COLS / 2 - 15, ">>> ");
  attroff(COLOR_PAIR(3));
  attroff(COLOR_PAIR(1));

  char userInput[256];
  getnstr(userInput, sizeof(userInput) - 1);
  noecho(); // Deshabilitar el eco

  std::string palabra(userInput);
  auto resultados = documento.buscarPalabra(palabra);

  if (resultados.first) { // Sí hubieron coincidencias
    std::vector<std::string> lines;
    for (const auto &par : resultados.second) {
      std::string linea = par.first + ": ";
      for (const auto &ubicacion : par.second) {
        linea += ubicacion + " ";
      }
      lines.push_back(linea);
    }
    imprimirConScroll(lines);
  } else {
    mvprintw(LINES / 2, COLS / 2 - 15, "<< Coincidencias no encontradas >>");
    getch();
  }
}
