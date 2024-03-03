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
    init_pair(1, COLOR_WHITE, COLOR_BLACK); 
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    
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
    map <string, set<string>> palabrasOrdenadas;

    for (const auto& mapa : indicePalabras) {
        for (const auto& par : mapa) {
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
        imprimirMarco("Índice de Palabras");

        int max_line = LINES - 3;
        int current_line = 2;

        int i = 0;
        for (const auto& par : palabrasOrdenadas) {
            if (i < scroll_offset) {
                i++;
                continue;
            }

            // Cada palabra y su información asociada
            string palabra = par.first;
            set<string> informacion = par.second;

            mvprintw(current_line++, MARGIN, "Palabra: %s", palabra.c_str());

            for (const auto& info : informacion) {
                if (current_line <= max_line) {
                    mvprintw(current_line++, MARGIN + 2, "Info: %s", info.c_str());
                } else {
                    break;  // Rompe el bucle si alcanzamos el límite de líneas
                }
            }

            if (current_line <= max_line) {
                // Separador entre palabras
                mvprintw(current_line++, MARGIN, "----------------");
            } else {
                break;  // Rompe el bucle si alcanzamos el límite de líneas
            }
        }

        int ch = getch();
        switch (ch) {
            case KEY_MOUSE:
                if (getmouse(&event) == OK) {
                    if (event.bstate & BUTTON4_PRESSED) {
                        scroll_offset -= SCROLL_LINE_STEP;
                        if (scroll_offset < 0) scroll_offset = 0;
                    } else if (event.bstate & BUTTON5_PRESSED) {
                        scroll_offset += SCROLL_LINE_STEP;
                        int max_offset = static_cast<int>(indicePalabras.size()) - max_line;
                        if (scroll_offset > max_offset) scroll_offset = max_offset;
                    }
                }
                break;
            case 'q':
                quit = true;
                break;
        }
    }
}

<<<<<<< HEAD
void SubMenu::imprimirEstadisticas(int numeroDeCapitulos, int numeroDeLineas, int numeroDePaginas, int numeroPalabrasTotal, int numeroDePalabrasUnicas) {
    clearScreen();

    box(stdscr, 0, 0);
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int x = (max_x - 75) / 2;
    mvprintw(max_y/2, x, "Estadísticas del documento:");
    mvprintw(max_y/2+2, x, "Número de capítulos: %d", numeroDeCapitulos);
    mvprintw(max_y/2+3, x, "Número de líneas: %d", numeroDeLineas);
    mvprintw(max_y/2+4, x, "Número de páginas: %d", numeroDePaginas);
    mvprintw(max_y/2+5, x, "Número de palabras totales: %d", numeroPalabrasTotal);
    mvprintw(max_y/2+6, x, "Número de palabras únicas: %d", numeroDePalabrasUnicas);
    mvprintw(max_y/2+8, x, "Presione 'Cualquier Tecla' para salir");
    refresh();
    getch();
    
    
}
=======
void SubMenu::buscarUnCapitulo(Documento documento) {
    imprimirMarco(""); // Imprime el marco inicial
    attron(COLOR_PAIR(1));
    echo(); // Habilita el eco de los caracteres ingresados por el usuario
    mvprintw(LINES / 2 - 10, COLS / 2 - 10, "BUSCAR UN CAPITULO");
    mvprintw(LINES / 2 - 10 + 2, COLS / 2 - 15, ">>> ");
    attroff(COLOR_PAIR(1));

    char userInput[256];
    getnstr(userInput, sizeof(userInput) - 1);
    noecho(); // Deshabilita el eco de los caracteres

    string nombreCapitulo = userInput;
    vector<string> resultado = documento.getCapituloIndice(nombreCapitulo);

    imprimirConScroll(resultado);
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
        imprimirMarco("Capítulo Encontrado");

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
>>>>>>> 55d9ab441ea29c1a7e0aef233c89345b4e17dcc3
