#include "../include/mainwindow.h"

#include "../gui/ui_mainwindow.h"


MainWindow::MainWindow( QWidget *parent ): QMainWindow( parent ), ui( new Ui::MainWindow ), game(CARNIVORES, HERBIVORES, 3, MAP_HEIGHT, MAP_WIDTH) {
    ui->setupUi( this );

    // setup scene
    scene = new QGraphicsScene(this);
    ui->map->setScene(scene);

    // setup timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_scene()));
    timer->start(TIME_BETWEEN_REFRESHES);


    // setup exit button
    QPushButton* exitButton = MainWindow::findChild<QPushButton *>("exitButton");
    connect(exitButton, SIGNAL(released()), this, SLOT(exit_button_pressed()));
}

MainWindow::~MainWindow() {
    delete timer;
    delete scene;
    delete ui;
}


void MainWindow::update_scene() {

    rectangles.clear();
    scene->clear();

    QPen white_pen(Qt::white);
    white_pen.setWidth(0);

    game.play();
    Map map = game.get_map();
    for (unsigned int i = 0; i < MAP_HEIGHT * MAP_WIDTH; ++i) {

        if(map.get_field_by_idx(i)->get_specimen()){
            std::string color = map.get_field_by_idx(i)->get_specimen()->get_brush_color();
            QColor qcolor(QString::fromStdString(color));
            QBrush brush(qcolor);
            scene->addRect(SQUARE_SIZE * (i % MAP_WIDTH), SQUARE_SIZE * (i / MAP_WIDTH), SQUARE_SIZE, SQUARE_SIZE, white_pen, brush);
        }
    }
}


void MainWindow::exit_button_pressed() {
    QApplication::quit();
}
