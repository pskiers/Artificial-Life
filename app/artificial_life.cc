#include "game.h"
#include "herbivore.h"
#include "./include/mainwindow.h"

#include <iostream>

#include <QApplication>

using namespace std;


int main(int argc, char *argv[])
{
    Game game( 1, 2, 3, 4, 5 );
    game.play();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
