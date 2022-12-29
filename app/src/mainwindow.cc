#include "../include/mainwindow.h"

#include "../gui/ui_mainwindow.h"


MainWindow::MainWindow( QWidget *parent ): QMainWindow( parent ), ui( new Ui::MainWindow ), game(CARNIVORES, HERBIVORES, 3, MAP_HEIGHT, MAP_WIDTH) {
    ui->setupUi( this );

    map = new QGraphicsScene(this);
    ui->map->setScene(map);

    QPen black(Qt::black);
    black.setWidth(0);

    Map gamemap = game.get_map();
    for (unsigned int i = 0; i < MAP_HEIGHT * MAP_WIDTH; ++i) {
        if(gamemap.get_field(i)->get_specimen()){
            std::string color = gamemap.get_field(i)->get_specimen()->get_brush();
            QString qstr = QString::fromStdString(color);
            QColor qcolor(qstr);
            QBrush brush(qcolor);
            map->addRect(SQUARE_SIZE * (i % MAP_WIDTH), SQUARE_SIZE * (i / MAP_WIDTH), SQUARE_SIZE, SQUARE_SIZE, black, brush);
        }
    }
}

MainWindow::~MainWindow() {
    delete map;
    delete ui;
}
