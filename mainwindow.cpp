#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <functions.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //! OpenGl output to verify.
    myOpenGl = new opengl();
    //! Graph scale.
    myOpenGl->setScale(10,10);
    myOpenGl->setInterval(0.01);

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

void MainWindow::on_pushButton_pressed()
{
    std::vector<double> vvec, svec, avec;

    double vo=ui->doubleSpinBox_vo->value();
    double vm=ui->doubleSpinBox_vm->value();
    double ve=ui->doubleSpinBox_ve->value();
    double a=ui->doubleSpinBox_a->value();
    double dv=ui->doubleSpinBox_dv->value();
    double acs=ui->doubleSpinBox_acs->value();
    double ace=ui->doubleSpinBox_ace->value();
    double s=ui->doubleSpinBox_s->value();
    bool debug=ui->checkBox_debug->isChecked();

    sc *sc= new class sc();
    sc->set(a,dv);
    sc->construct_motion(vo,vm,ve,acs,ace,s);
    sc->plot(0.01,vvec,svec,avec);
    //sc->print_journal();
    sc->print_interpolation(0.01);


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
