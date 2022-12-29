#include "./include/mainwindow.h"
#include "game.h"
#include "herbivore.h"

#include <QApplication>
#include <iostream>

using namespace std;


int main( int argc, char *argv[] ) {
    QApplication a( argc, argv );
    MainWindow w;
    w.setWindowState(Qt::WindowFullScreen);
    w.show();
    return a.exec();
}
