#include "../include/mainwindow.h"

#include "../gui/ui_mainwindow.h"


MainWindow::MainWindow( QWidget *parent ): QMainWindow( parent ), ui( new Ui::MainWindow ) {
    ui->setupUi( this );
    game = new Game( CARNIVORES, HERBIVORES, 3, MAP_HEIGHT, MAP_WIDTH );

    // setup scene
    scene = new QGraphicsScene( this );
    ui->map->setScene( scene );

    // setup timer
    timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( update() ) );
    timer->setInterval( TIME_BETWEEN_REFRESHES );


    // setup exit button
    connect( ui->exitButton, SIGNAL( released() ), this, SLOT( exit_button_pressed() ) );

    // setup reset button
    connect( ui->resetButton, SIGNAL( released() ), this, SLOT( reset_button_pressed() ) );

    // setup start/stop button
    connect( ui->startStopButton, SIGNAL( released() ), this, SLOT( start_stop_button_pressed() ) );
}

MainWindow::~MainWindow() {
    delete game;
    delete timer;
    delete scene;
    delete ui;
}


void MainWindow::update() {

    rectangles.clear();
    scene->clear();

    QBrush plant_brush( Qt::green );
    QPen white_pen( Qt::white );
    white_pen.setWidth( 0 );


    game->play();
    Map map = game->get_map();
    for ( unsigned int i = 0; i < MAP_HEIGHT; ++i ) {
        for ( unsigned int j = 0; j < MAP_WIDTH; ++j ) {
            if ( map.get_field( j, i )->get_specimen() ) {
                std::string color = map.get_field( j, i )->get_specimen()->get_brush_color();
                QColor qcolor( QString::fromStdString( color ) );
                QBrush brush( qcolor );
                scene->addRect( SQUARE_SIZE * j, SQUARE_SIZE * i, SQUARE_SIZE, SQUARE_SIZE, white_pen, brush );
            } else if ( map.get_field( j, i )->has_plant() )
                scene->addRect( SQUARE_SIZE * j, SQUARE_SIZE * i, SQUARE_SIZE, SQUARE_SIZE, white_pen, plant_brush );
        }
    }
    ui->carnivoresLabel->setText( QString::number( this->game->get_carnivores_amount() ) );
    ui->herbivoresLabel->setText( QString::number( this->game->get_herbivores_amount() ) );
    ui->plantLabel->setText( QString::number( this->game->get_plants_amount() ) );
}


void MainWindow::exit_button_pressed() {
    QApplication::quit();
}


void MainWindow::reset_button_pressed() {
    if ( this->timer->isActive() )
        this->timer->stop();
    this->scene->clear();
    this->rectangles.clear();

    delete this->game;

    unsigned int carnivores = ui->carnivoresSpinBox->value();
    unsigned int herbivores = ui->herbivoresSpinBox->value();
    unsigned int plants = ui->plantsSpinBox->value();
    this->game = new Game( carnivores, herbivores, plants, MAP_HEIGHT, MAP_WIDTH );
}

void MainWindow::start_stop_button_pressed() {
    if ( this->timer->isActive() )
        this->timer->stop();
    else {
        this->timer->start();
        ui->specTypeLabel->setText( "-" );
        ui->specSpeedLabel->setText( "-" );
        ui->specSightRangeLabel->setText( "-" );
        ui->specSightAngleLabel->setText( "-" );
        ui->specSleepLabel->setText( "-" );
        ui->specMaxSleepLabel->setText( "-" );
        ui->specHungerLabel->setText( "-" );
        ui->specMaxHungerLabel->setText( "-" );
    }
}

void MainWindow::mousePressEvent( QMouseEvent *event ) {
    if ( this->timer->isActive() )
        return;
    QPointF point = ui->map->mapFromGlobal( event->pos() );
    Field *field = this->game->get_map().get_field( point.x() / SQUARE_SIZE, point.y() / SQUARE_SIZE );
    if ( field && field->get_specimen() ) {
        ui->specTypeLabel->setText( QString::fromStdString( field->get_specimen()->describeMyself() ) );
        ui->specSpeedLabel->setText( QString::number( field->get_specimen()->get_speed() ) );
        ui->specSightRangeLabel->setText( QString::number( field->get_specimen()->get_sight_range() ) );
        ui->specSightAngleLabel->setText( QString::number( field->get_specimen()->get_sight_angle() ) );
        ui->specSleepLabel->setText( QString::number( field->get_specimen()->get_time_to_sleep() ) );
        ui->specMaxSleepLabel->setText( QString::number( field->get_specimen()->get_max_time_to_sleep() ) );
        ui->specHungerLabel->setText( QString::number( field->get_specimen()->get_current_hunger() ) );
        ui->specMaxHungerLabel->setText( QString::number( field->get_specimen()->get_max_hunger() ) );
    } else {
        ui->specTypeLabel->setText( "-" );
        ui->specSpeedLabel->setText( "-" );
        ui->specSightRangeLabel->setText( "-" );
        ui->specSightAngleLabel->setText( "-" );
        ui->specSleepLabel->setText( "-" );
        ui->specMaxSleepLabel->setText( "-" );
        ui->specHungerLabel->setText( "-" );
        ui->specMaxHungerLabel->setText( "-" );
    }
}
