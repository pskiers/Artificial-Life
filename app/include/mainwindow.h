#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include "game.h"
#include <vector>
#include <string>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

static const unsigned int MAP_WIDTH = 200;
static const unsigned int MAP_HEIGHT = 128;
static const unsigned int SQUARE_SIZE = 8;
static const unsigned int CARNIVORES = 20;
static const unsigned int HERBIVORES = 20;
static const unsigned int TIME_BETWEEN_REFRESHES = 1000;


class MainWindow: public QMainWindow {
    Q_OBJECT

  public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

  private:
    Ui::MainWindow *ui;
    Game game;
    QGraphicsScene *scene;
    std::vector <QGraphicsRectItem*> rectangles;
    QTimer *timer;

  private slots:
    void update_scene();
};
#endif    // MAINWINDOW_H