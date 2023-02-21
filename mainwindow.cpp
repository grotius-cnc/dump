#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <sc_motion.h>

std::vector<double> vvec, svec, avec;

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

    //! Timer to simulate servo cycle.
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(thread()));
    timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_run_pressed()
{
    sc_motion *motion = new sc_motion();
    sc_motion_in in;
    sc_motion_out out;
    sc_status status;

    motion->nr_of_joints(3);

    sc_motion_joint_id id=sc_motion_joint_id::id_J1;
    sc_motion_params params={ui->doubleSpinBox_a->value(),ui->doubleSpinBox_dv->value()};
    motion->set(id,params);

    in.curacc=ui->doubleSpinBox_acs->value();
    in.curpos=0;
    in.curvel=ui->doubleSpinBox_vo->value();
    in.endacc=ui->doubleSpinBox_ace->value();
    in.endpos=ui->doubleSpinBox_s->value();
    in.endvel=ui->doubleSpinBox_ve->value();
    in.maxvel=ui->doubleSpinBox_vm->value();

    //! From here runs in servo cycle.
    status=motion->update(0.001,id,in,out);

    if(status==sc_status::Error){
        std::cerr<<"motion error"<<std::endl;
    }

    if(!out.finished){
        in.curvel=out.newvel;
        in.curpos=out.newpos;
        in.curacc=out.newacc;
    } else {
        //! Feed new motion block.
    }
}

//! This function simulates the servo cycle. And is called every 1 millisecond.
void MainWindow::thread(){

}

void MainWindow::on_doubleSpinBox_vm_valueChanged(double arg1)
{
    on_pushButton_run_pressed();
}

void MainWindow::on_doubleSpinBox_a_valueChanged(double arg1)
{
    on_pushButton_run_pressed();
}

void MainWindow::on_doubleSpinBox_vo_valueChanged(double arg1)
{
    on_pushButton_run_pressed();
}

void MainWindow::on_doubleSpinBox_ve_valueChanged(double arg1)
{
    on_pushButton_run_pressed();
}

void MainWindow::on_doubleSpinBox_s_valueChanged(double arg1)
{
    on_pushButton_run_pressed();
}

void MainWindow::on_doubleSpinBox_acs_valueChanged(double arg1)
{
    on_pushButton_run_pressed();
}

void MainWindow::on_doubleSpinBox_ace_valueChanged(double arg1)
{
    on_pushButton_run_pressed();
}

void MainWindow::on_doubleSpinBox_dv_valueChanged(double arg1)
{
    on_pushButton_run_pressed();
}
