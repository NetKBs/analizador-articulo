#include <ncurses.h>
#include "GUI.h"
#include "SubMenu.h"

GUI::GUI(Documento documento) : documento(documento) {

    initscr();
    start_color(); // Habilitar el uso de colores
    keypad(stdscr, TRUE); // Habilitar el teclado numérico
    init_pair(1, COLOR_WHITE, COLOR_BLACK); 
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    
    showMenu();
}

GUI::~GUI() {
    endwin(); // Finalizar ncurses al destruir la instancia de la clase
}

void GUI::clearScreen() {
    clear();
    refresh();
}


void GUI::showMenu() {
    int max_y, max_x;
    int current_option = 1;
    getmaxyx(stdscr, max_y, max_x); // Obtener el tamaño de la terminal

   std::vector<std::string> ascii_art = {
    " ,--,--'      .      ,.           .                  ",
    "`- | ,-. . , |-    / |   ,-. ,-. |  . . ,_, ,-. ,-. ",
    " , | |-'  X  |    /~~|-. | | ,-| |  | |  /  |-' |   ",
    " `-' `-' ' ` `' ,'   `-' ' ' `-^ `' `-| '\"' `-' '   ",
    "                                     /|             ",
    "                                    `-'             "
};


    do {
        clearScreen();
        // Calcular las coordenadas para centrar el menú
        int menu_y = (max_y - 11) / 2; 
        int menu_x = (max_x - 40) / 2;

        attron(COLOR_PAIR(1));
        // Imprimir el arte ASCII
        for (size_t i = 0; i < ascii_art.size(); ++i) {
            mvprintw(menu_y - 7 + i, menu_x - 5, ascii_art[i].c_str());
        }
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(3));
        mvprintw(menu_y - 1, menu_x - 1, "+----------------------------------------+");
        mvprintw(menu_y + 10, menu_x - 1, "+----------------------------------------+");
        for (int i = 0; i < 11; ++i) {
            mvprintw(menu_y + i, menu_x - 1, "*");
            mvprintw(menu_y + i, menu_x + 40, "*");
        }
        attroff(COLOR_PAIR(3));

        // Imprimir el menú
        attron(COLOR_PAIR(3));
        mvprintw(menu_y + 1, menu_x, "1. Indice De Palabras");
        mvprintw(menu_y + 2, menu_x, "2. Eliminar Palabra");
        mvprintw(menu_y + 3, menu_x, "3. Estadistica Del Documento");
        mvprintw(menu_y + 4, menu_x, "4. Busqueda De Palabras");
        mvprintw(menu_y + 5, menu_x, "5. Busqueda De Un Capitulo ");
        mvprintw(menu_y + 6, menu_x, "6. Imprimir Documento");
        attroff(COLOR_PAIR(3));

        // Pintar opción actual
        attron(COLOR_PAIR(2));
        switch (current_option) {
            case 1:
                mvprintw(menu_y + 1, menu_x, "1. Indice De Palabras");
                break;
            case 2:
                mvprintw(menu_y + 2, menu_x, "2. Eliminar Palabra");
                break;
            case 3:
                mvprintw(menu_y + 3, menu_x, "3. Estadistica Del Documento");

                break;
            case 4:
                mvprintw(menu_y + 4, menu_x, "4. Busqueda De Palabra");
                break;
            case 5:
                mvprintw(menu_y + 5, menu_x, "5. Busqueda De Un Capitulo ");
                break;
            case 6:
                mvprintw(menu_y + 6, menu_x, "6. Imprimir Documento ");
                break;
        }
        attroff(COLOR_PAIR(2));

        mvprintw(menu_y + 8, menu_x, "Seleccione una opción (w/s/enter) ");
        refresh();
 
        int ch = getch();
        if (ch == 'w' || ch == KEY_UP) {
            if (current_option > 1) {
                current_option--;
            }
        } else if (ch == 's' || ch == KEY_DOWN) {
            if (current_option < 6) {
                current_option++;
            }
        } else if (ch == '\n') {
            if (current_option >= 1 && current_option <= 6) {
                handleOption(current_option); 
            }

        }
    } while (true);
}

void GUI::handleOption(int option) {
    SubMenu submenu;

    switch (option) {
        case 1:
            submenu.imprimirIndicePalabras(documento.getIndice());
            break;
        case 2:
            submenu.EliminarPalabra(documento);
            break;
        case 3:
            
            break;
        case 4:
            
            break;

        case 5: {
            submenu.buscarUnCapitulo(documento);
           
            break;
        case 6:
            clearScreen();
            submenu.imprimirDocumento(documento.getTextoProcesado());
            refresh();
            break;
        }
    }
}