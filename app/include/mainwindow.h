#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <string>
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// MAP_WIDTH * SQUARE_SIZE <= 1600 && MAP_HEIGHT * SQUARE_SIZE <= 1024
static const unsigned int MAP_WIDTH = 50;
static const unsigned int MAP_HEIGHT = 32;
static const unsigned int SQUARE_SIZE = 32;
static const unsigned int CARNIVORES = 20;
static const unsigned int HERBIVORES = 20;
static const unsigned int TIME_BETWEEN_REFRESHES = 500;


class MainWindow: public QMainWindow {
    Q_OBJECT

  public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();
    void mousePressEvent( QMouseEvent *event );

  private:
    Ui::MainWindow *ui_;
    Game *game_;
    QGraphicsScene *scene_;
    std::vector<QGraphicsRectItem *> rectangles_;
    QTimer *timer_;

  private slots:
    void update();
    void exit_button_pressed();
    void reset_button_pressed();
    void start_stop_button_pressed();
};
#endif    // MAINWINDOW_H