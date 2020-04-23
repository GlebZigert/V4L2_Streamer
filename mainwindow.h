#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <my_camera.h>
#include <sdl_class.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    My_Camera cam;
    SDL_class SDL;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

 public slots:
     void draw_YUV();
     void draw_MJPEG();
};

#endif // MAINWINDOW_H
