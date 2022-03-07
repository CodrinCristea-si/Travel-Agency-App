#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <Qapplication>
#include <qdebug.h>
#include <QLabel>
#include <QWidget>
#include "Ui.h"
#include "test.h"
#include "GUI.h"
int main(int argc,char** argv) {
    toate_testele();
    //Ui ui;
    //ui.meniu();
    //_CrtDumpMemoryLeaks();
    {
        QApplication a{argc, argv};
        Controller cont;
        Repository rep;
        Wishlist wish;
        MeniuAplicatie men{cont, rep,wish};
        //Cos_GUI{rep,cont,wish};
        a.exec();
        cont.salveaza_fisier_repo(rep, "repo.txt");
    }
    return 0;
}
