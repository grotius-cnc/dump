#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <chrono>
#include <stdio.h>
#include <math.h>
#include <vector>

//! Function elapsed time in milliseconds.
double nanoseconds_to_milliseconds(double nanoseconds){
    //! Convert from nano- to milliseconds.
    return nanoseconds*0.000001;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //! OpenGl output to verify.
    myOpenGl = new opengl();
    //! Graph scale.
    myOpenGl->setScale(10,10);
    myOpenGl->setInterval(0.001);

    scurve=new class sc();

    //! Startup calculation.
    on_pushButton_pressed();

    //! Timer to simulate servo cycle.
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(thread()));
    timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//! This function simulates the servo cycle. And is called every 1 millisecond.
void MainWindow::thread(){

}


void MainWindow::on_pushButton_run_pressed()
{

}

void MainWindow::on_pushButton_pressed()
{
    double vo=ui->doubleSpinBox_vo->value();
    double vm=ui->doubleSpinBox_vm->value();
    double ve=ui->doubleSpinBox_ve->value();
    double a=ui->doubleSpinBox_a->value();
    double dv=ui->doubleSpinBox_dv->value();
    double acs=ui->doubleSpinBox_acs->value();
    double ace=ui->doubleSpinBox_ace->value();
    double s=ui->doubleSpinBox_s->value();

    scurve->set(a,dv);

    scurve->build_motion(vo,vm,ve,acs,ace,s);

    std::vector<double> vvec, svec, avec;
    scurve->vo_ve_plot(0.001,vvec,svec,avec);
    //scurve->vo_ve_print_interpolation(0.1);

    myOpenGl->set1Vec(vvec);
    myOpenGl->set2Vec(svec);
    myOpenGl->set3VecShift(-150);
    myOpenGl->set3Vec(avec);
}

void MainWindow::on_doubleSpinBox_vm_valueChanged(double arg1)
{
    on_pushButton_pressed();
}

void MainWindow::on_doubleSpinBox_a_valueChanged(double arg1)
{
    on_pushButton_pressed();
}

void MainWindow::on_doubleSpinBox_vo_valueChanged(double arg1)
{
    on_pushButton_pressed();
}

void MainWindow::on_doubleSpinBox_ve_valueChanged(double arg1)
{
    on_pushButton_pressed();
}

void MainWindow::on_doubleSpinBox_s_valueChanged(double arg1)
{
    on_pushButton_pressed();
}

void MainWindow::on_doubleSpinBox_acs_valueChanged(double arg1)
{
    on_pushButton_pressed();
}

void MainWindow::on_doubleSpinBox_ace_valueChanged(double arg1)
{
    on_pushButton_pressed();
}

void MainWindow::on_doubleSpinBox_dv_valueChanged(double arg1)
{
    on_pushButton_pressed();
}
