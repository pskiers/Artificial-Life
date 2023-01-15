#include "../include/mainwindow.h"

#include "../gui/ui_mainwindow.h"


MainWindow::MainWindow( QWidget *parent ): QMainWindow( parent ), ui_( new Ui::MainWindow ) {
    ui_->setupUi( this );
    game_ = new Game( CARNIVORES, HERBIVORES, 3, MAP_HEIGHT, MAP_WIDTH );

    // setup scene
    scene_ = new QGraphicsScene( this );
    ui_->map->setScene( scene_ );

    // setup timer
    timer_ = new QTimer( this );
    connect( timer_, SIGNAL( timeout() ), this, SLOT( update() ) );
    timer_->setInterval( TIME_BETWEEN_REFRESHES );


    // setup exit button
    connect( ui_->exitButton, SIGNAL( released() ), this, SLOT( exit_button_pressed() ) );

    // setup reset button
    connect( ui_->resetButton, SIGNAL( released() ), this, SLOT( reset_button_pressed() ) );

    // setup start/stop button
    connect( ui_->startStopButton, SIGNAL( released() ), this, SLOT( start_stop_button_pressed() ) );
}

MainWindow::~MainWindow() {
    delete game_;
    delete timer_;
    delete scene_;
    delete ui_;
}


void MainWindow::update() {

    rectangles_.clear();
    scene_->clear();

    QBrush plant_brush( Qt::green );
    QPen white_pen( Qt::white );
    white_pen.setWidth( 0 );


    game_->play();
    Map map = game_->get_map();
    for ( unsigned int i = 0; i < MAP_HEIGHT; ++i ) {
        for ( unsigned int j = 0; j < MAP_WIDTH; ++j ) {
            if ( map.get_field( j, i )->get_specimen() ) {
                std::string color = map.get_field( j, i )->get_specimen()->get_brush_color();
                QColor qcolor( QString::fromStdString( color ) );
                QBrush brush( qcolor );
                scene_->addRect( SQUARE_SIZE * j, SQUARE_SIZE * i, SQUARE_SIZE, SQUARE_SIZE, white_pen, brush );
            } else if ( map.get_field( j, i )->has_plant() )
                scene_->addRect( SQUARE_SIZE * j, SQUARE_SIZE * i, SQUARE_SIZE, SQUARE_SIZE, white_pen, plant_brush );
        }
    }
    ui_->carnivoresLabel->setText( QString::number( this->game_->get_carnivores_amount() ) );
    ui_->herbivoresLabel->setText( QString::number( this->game_->get_herbivores_amount() ) );
    ui_->plantLabel->setText( QString::number( this->game_->get_plants_amount() ) );
}


void MainWindow::exit_button_pressed() {
    QApplication::quit();
}


void MainWindow::reset_button_pressed() {
    if ( this->timer_->isActive() )
        this->timer_->stop();
    this->scene_->clear();
    this->rectangles_.clear();

    delete this->game_;

    unsigned int carnivores = ui_->carnivoresSpinBox->value();
    unsigned int herbivores = ui_->herbivoresSpinBox->value();
    unsigned int plants = ui_->plantsSpinBox->value();
    this->game_ = new Game( carnivores, herbivores, plants, MAP_HEIGHT, MAP_WIDTH );
}

void MainWindow::start_stop_button_pressed() {
    if ( this->timer_->isActive() )
        this->timer_->stop();
    else {
        this->timer_->start();
        ui_->specTypeLabel->setText( "-" );
        ui_->specSpeedLabel->setText( "-" );
        ui_->specSightRangeLabel->setText( "-" );
        ui_->specSightAngleLabel->setText( "-" );
        ui_->specSleepLabel->setText( "-" );
        ui_->specMaxSleepLabel->setText( "-" );
        ui_->specHungerLabel->setText( "-" );
        ui_->specMaxHungerLabel->setText( "-" );
    }
}

void MainWindow::mousePressEvent( QMouseEvent *event ) {
    if ( this->timer_->isActive() )
        return;
    QPointF point = ui_->map->mapFromGlobal( event->pos() );
    Field *field = this->game_->get_map().get_field( point.x() / SQUARE_SIZE, point.y() / SQUARE_SIZE );
    if ( field && field->get_specimen() ) {
        ui_->specTypeLabel->setText( QString::fromStdString( field->get_specimen()->describeMyself() ) );
        ui_->specSpeedLabel->setText( QString::number( field->get_specimen()->get_speed() ) );
        ui_->specSightRangeLabel->setText( QString::number( field->get_specimen()->get_sight_range() ) );
        ui_->specSightAngleLabel->setText( QString::number( field->get_specimen()->get_sight_angle() ) );
        ui_->specSleepLabel->setText( QString::number( field->get_specimen()->get_time_to_sleep() ) );
        ui_->specMaxSleepLabel->setText( QString::number( field->get_specimen()->get_max_time_to_sleep() ) );
        ui_->specHungerLabel->setText( QString::number( field->get_specimen()->get_current_hunger() ) );
        ui_->specMaxHungerLabel->setText( QString::number( field->get_specimen()->get_max_hunger() ) );
    } else {
        ui_->specTypeLabel->setText( "-" );
        ui_->specSpeedLabel->setText( "-" );
        ui_->specSightRangeLabel->setText( "-" );
        ui_->specSightAngleLabel->setText( "-" );
        ui_->specSleepLabel->setText( "-" );
        ui_->specMaxSleepLabel->setText( "-" );
        ui_->specHungerLabel->setText( "-" );
        ui_->specMaxHungerLabel->setText( "-" );
    }
}
