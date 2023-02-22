#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <opengl.h>
#include <sc_motion.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void thread();

    void on_pushButton_run_pressed();

    void on_pushButton_stop_pressed();

    void on_pushButton_build_pressed();

    void on_doubleSpinBox_acs_valueChanged(double arg1);

    void on_doubleSpinBox_ace_valueChanged(double arg1);

    void on_doubleSpinBox_vm_valueChanged(double arg1);

    void on_doubleSpinBox_a_valueChanged(double arg1);

    void on_doubleSpinBox_dv_valueChanged(double arg1);

    void on_doubleSpinBox_vo_valueChanged(double arg1);

    void on_doubleSpinBox_ve_valueChanged(double arg1);

    void on_doubleSpinBox_s_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    opengl *myOpenGl;

    sc_motion *motion = new sc_motion();
    sc_motion_in in_J0, in_J1, in_J2;
    sc_motion_out out_J0, out_J1, out_J2;
    sc_status status;
};
#endif
