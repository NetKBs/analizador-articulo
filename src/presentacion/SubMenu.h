// SubMenu.h
#ifndef SubMenu_h
#define SubMenu_h

#include <iostream>
#include <map>
#include <ncurses.h>
#include <vector>


using namespace std;


class SubMenu {

private:
    void clearScreen();
    void imprimirMarco(string titulo="");

public:
    SubMenu();  // constructor
    ~SubMenu(); // destructor
    //void tagsHtml(map<string, pair<int, double>> tagCounts);
    //void buscarUnTag(HTMLParser parser);
    //void enlacesHtml(vector<string> links);
    //void imagenesHtml(vector<string> imagenes);

    void imprimirDocumento(string textoProcesado);


};

#endif





