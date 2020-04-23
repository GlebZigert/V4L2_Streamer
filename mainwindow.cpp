#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(&cam,SIGNAL(draw_YUV()),this,SLOT(draw_YUV()));
    connect(&cam,SIGNAL(draw_MJPEG()),this,SLOT(draw_MJPEG()));
    ui->setupUi(this);
    cam.dev_open();
    cam.dev_init();
    SDL.init_view(cam.fmt);
    SDL.run_SDL_SetEventFilter();;
    cam.start_capturing();
    cam.mainloop();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::draw_YUV()
{
SDL.draw_YUV(cam.buffer_start,cam.length,cam.fmt);
}

void MainWindow::draw_MJPEG()
{

}
