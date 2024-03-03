// SubMenu.cpp
#include "SubMenu.h"
#include <array>
#include <cctype>
#include <cstring>
#include <ncurses.h>
#include <sstream>
#include <algorithm>

#define SCROLL_LINE_STEP 1
#define MARGIN 2

SubMenu::SubMenu() {
  initscr();
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
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
  attron(COLOR_PAIR(1));
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

void addLineWithWrapping(std::vector<std::string>& lines, const std::string& line, size_t maxLineWidth) {
    size_t start = 0;
    while (start < line.length()) {
        size_t end = start + maxLineWidth;
        if (end > line.length()) end = line.length();

        // Encuentra el último espacio en blanco para evitar cortar palabras
        if (end < line.length()) {
            size_t lastSpace = line.rfind(' ', end);
            if (lastSpace != std::string::npos && lastSpace > start) {
                end = lastSpace;
            }
        }

        lines.push_back(line.substr(start, end - start));
        start = end + ((end < line.length()) ? 1 : 0); // Saltar el espacio si no es el final de la línea
    }
}


void SubMenu::imprimirDocumento(string textoProcesado) {
    
    // Convertir el texto procesado en un vector de strings, cada uno representando una línea
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
        imprimirMarco("Titulo del Documento"); // Asegúrate de que este método no limpie la pantalla

        // Imprimir el documento desde el scroll_offset
        int max_line = LINES - 3; // Ajuste para el espacio vertical del marco
        for (int i = 0; i < max_line && (i + scroll_offset) < lines.size(); ++i) {
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
            // Añade más casos si necesitas más controles
        }
    }
}


void SubMenu::imprimirIndicePalabras(vector<map<string, set<string>>> indicePalabras) {
    clearScreen();
    box(stdscr, 0, 0);

    
    vector<string> letrasUnicas;
    for (map<string, set<string>> palabras: indicePalabras) {
        char letra = palabras.begin()->first[0];
        if (find(letrasUnicas.begin(), letrasUnicas.end(), string(1, letra)) == letrasUnicas.end()) {
            letrasUnicas.push_back(string(1, letra));
        }
    }
    
    vector<vector<map<string, set<string>>>> indicesPorLetra;
    for (string letra: letrasUnicas) {
        vector<map<string, set<string>>> indicesPorLetraAux;
        for (map<string, set<string>> palabras: indicePalabras) {
            if (palabras.begin()->first[0] == letra[0]) {
                indicesPorLetraAux.push_back(palabras);
            }
        }
        indicesPorLetra.push_back(indicesPorLetraAux);
    }
    
    for (vector<map<string, set<string>>> indicePorLetra: indicesPorLetra) {
        for (map<string, set<string>> palabras: indicePorLetra) {
            for (pair<string, set<string>> palabra: palabras) {
                string palabraFormateada = palabra.first + ": ";
                for (string pagina: palabra.second) {
                    palabraFormateada += pagina + " ";
                }
                mvprintw(LINES / 2, (COLS - palabraFormateada.length()) / 2, palabraFormateada.c_str());
                getch();
            }
        }
    }
    


  /*
    int fila = 3;
    int columna = (COLS - 60) / 2;
    int cantidadPalabras = indicePalabras.size();
    int indice = 0;
    int pagina = 0;
    int elementosPorPagina = LINES - 10; // Calcula cuántos elementos caben en una 

    while (indice < cantidadPalabras) {
    clear(); // Borra la pantalla antes de imprimir la siguiente página
    imprimirMarco("ENLACES EN EL HTML");

    for (int i = 0; i < elementosPorPagina && indice < cantidadPalabras; ++i) {

      if (links[indice].length() > COLS - 10) {
        mvprintw(fila, 2, "[%d] %s", indice + 1, (links[indice].substr(0, COLS - 15) + "...").c_str());
      } else {
        mvprintw(fila, 2, "[%d] %s", indice + 1, links[indice].c_str());
      }
      ++fila;
      ++indice;
    }

    mvprintw(LINES - 3, columna - 3, "<< Página %d - Presione 'q' para salir o 'cualquier tecla' para continuar >>", pagina + 1);
    refresh();
    int continuar = getch();

    if (continuar == 'q') {
      return;
    }
    fila = 3;
    ++pagina;
  }

    refresh();*/
}

/*
void SubMenu::buscarUnTag(HTMLParser parser) {

  int fila = 3;
  int columna = (COLS - 60) / 2;
  int indice = 0;
  int pagina = 0;
  int elementosPorPagina = LINES - 10; // Calcula cuántos elementos caben en una página

  imprimirMarco("");
  attron(COLOR_PAIR(1));
  echo(); // Habilitar el eco de los caracteres ingresados por el usuariomvprin
  mvprintw(LINES / 2 - 10, COLS / 2 - 10, "BUSCAR UN TAG");
  mvprintw(LINES / 2 - 10 + 2, COLS / 2 - 15, ">>> ");
  attroff(COLOR_PAIR(1));

  char userInput[256];
  getnstr(userInput, sizeof(userInput) - 1);
  noecho(); // Deshabilitar el eco de los caracteres

  vector<string> etiquetas = parser.getTag(userInput);
  if (etiquetas.empty()) {
    clear();
    mvprintw(LINES / 2 - 10, COLS / 2 - 10, "No se encontraron etiquetas");
    refresh();
    getch();
    return;
  }

  int cantidadEtiquetas = etiquetas.size();
  while (indice < cantidadEtiquetas) {
    imprimirMarco("");

    for (int i = 0; i < elementosPorPagina && indice < cantidadEtiquetas; ++i) {

      if (etiquetas[indice].length() > COLS - 10) {
        mvprintw(fila, 2, "[%d] <%s>", indice + 1, (etiquetas[indice].substr(0, COLS - 15) + "...").c_str());
      } else {
        mvprintw(fila, 2, "[%d] <%s>", indice + 1, etiquetas[indice].c_str());
      }
      ++fila;
      ++indice;
    }

    mvprintw(LINES - 3, columna - 3, "<< Página %d - Presione 'q' para salir o 'cualquier tecla' para continuar >>", pagina + 1);
    refresh();

    int continuar = getch();
    if (continuar == 'q') {
      return;
    }
    fila = 3;
    ++pagina;
  }
}
*/

/*
void SubMenu::enlacesHtml(vector<string> links) {

  if(links.empty()){
    clear();
    mvprintw(LINES / 2 - 10, COLS / 2 - 10, "No se encontraron enlaces");
    refresh();
    getch();
    return;
  }

  int fila = 3;
  int columna = (COLS - 60) / 2;
  int cantidadLinks = links.size();
  int indice = 0;
  int pagina = 0;
  int elementosPorPagina = LINES - 10; // Calcula cuántos elementos caben en una 

  while (indice < cantidadLinks) {
    clear(); // Borra la pantalla antes de imprimir la siguiente página
    imprimirMarco("ENLACES EN EL HTML");

    for (int i = 0; i < elementosPorPagina && indice < cantidadLinks; ++i) {

      if (links[indice].length() > COLS - 10) {
        mvprintw(fila, 2, "[%d] %s", indice + 1, (links[indice].substr(0, COLS - 15) + "...").c_str());
      } else {
        mvprintw(fila, 2, "[%d] %s", indice + 1, links[indice].c_str());
      }
      ++fila;
      ++indice;
    }

    mvprintw(LINES - 3, columna - 3, "<< Página %d - Presione 'q' para salir o 'cualquier tecla' para continuar >>", pagina + 1);
    refresh();
    int continuar = getch();

    if (continuar == 'q') {
      return;
    }
    fila = 3;
    ++pagina;
  }
}
*/

/*
void SubMenu::imagenesHtml(vector<string> imagenes) {

  if (imagenes.empty()) {
    clear();
    mvprintw(LINES / 2 - 10, COLS / 2 - 10, "No se encontraron imágenes");
    refresh();
    getch();
    return;
  }

  int fila = 3;
  int columna = (COLS - 60) / 2;
  int cantidadImagenes = imagenes.size();
  int indice = 0;
  int pagina = 0;
  int elementosPorPagina = LINES - 10; // Calcula cuántos elementos caben en una página

  while (indice < cantidadImagenes) {
    clear(); // Borra la pantalla antes de imprimir la siguiente página
    imprimirMarco("IMAGENES EN EL HTML");

    for (int i = 0; i < elementosPorPagina && indice < cantidadImagenes; ++i) {

      if (imagenes[indice].length() > COLS - 10) {
        mvprintw(fila, 2, "[%d] %s", indice + 1,
                 (imagenes[indice].substr(0, COLS - 15) + "...").c_str());
      } else {
        mvprintw(fila, 2, "[%d] %s", indice + 1, imagenes[indice].c_str());
      }
      ++fila;
      ++indice;
    }

    mvprintw(LINES - 3, columna - 3, "<< Página %d - Presione 'q' para salir o 'cualquier tecla' para continuar >>", pagina + 1);
    refresh();

    int continuar = getch();
    if (continuar == 'q') {
      return;
    }
    fila = 3;
    ++pagina;
  }
}
*/