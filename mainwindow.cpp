#include "mainwindow.h"
#include "./ui_mainwindow.h"

std::vector<double> j0_vec, j1_vec, j2_vec;
bool run=0;
double tmax=0;

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
    myOpenGl->setInterval(0.01);

    //! Timer to simulate servo cycle.
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(thread()));
    timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_build_pressed()
{
    j0_vec.clear();

    motion->nr_of_joints(1);

    motion->set(id_J0,
                ui->doubleSpinBox_a->value(),
                ui->doubleSpinBox_dv->value());

    in_J0.curacc=ui->doubleSpinBox_acs->value();
    in_J0.curpos=0;
    in_J0.curvel=ui->doubleSpinBox_vo->value();
    in_J0.endacc=ui->doubleSpinBox_ace->value();
    in_J0.endpos=ui->doubleSpinBox_s->value();
    in_J0.endvel=ui->doubleSpinBox_ve->value();
    in_J0.maxvel=ui->doubleSpinBox_vm->value();

    motion->update(0,id_J0,in_J0,out_J0);
    T ct=motion->curve_time(id_J0);


    std::cout<<"curve time:"<<ct<<std::endl;

    for(T i=0; i<ct; i+=0.01){
        auto start = std::chrono::high_resolution_clock::now();
        motion->update(i,id_J0,in_J0,out_J0);
         motion->update(i,id_J0,in_J0,out_J0);
          motion->update(i,id_J0,in_J0,out_J0);
           motion->update(i,id_J0,in_J0,out_J0);
            motion->update(i,id_J0,in_J0,out_J0);
             motion->update(i,id_J0,in_J0,out_J0);
              motion->update(i,id_J0,in_J0,out_J0);
               motion->update(i,id_J0,in_J0,out_J0);
                motion->update(i,id_J0,in_J0,out_J0);

        auto end = std::chrono::high_resolution_clock::now();
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        double t=nanoseconds_to_milliseconds(nanoseconds.count());
        tmax=std::max(t,tmax);
        std::cout<<std::fixed<<"t:"<<t<<" tmax:"<<tmax<<std::endl;
        j0_vec.push_back(out_J0.newvel);
    }
    myOpenGl->setj0vec(j0_vec);
}

void MainWindow::on_pushButton_run_pressed()
{
    j0_vec.clear();
    j1_vec.clear();
    j2_vec.clear();

    motion->nr_of_joints(3);

    motion->set(sc_motion_joint_id::id_J0,
                ui->doubleSpinBox_a->value(),
                ui->doubleSpinBox_dv->value());

    motion->set(sc_motion_joint_id::id_J1,
                ui->doubleSpinBox_a->value(),
                ui->doubleSpinBox_dv->value());

    motion->set(sc_motion_joint_id::id_J2,
                ui->doubleSpinBox_a->value(),
                ui->doubleSpinBox_dv->value());

    in_J0.curacc=ui->doubleSpinBox_acs->value();
    in_J0.curpos=0;
    in_J0.curvel=ui->doubleSpinBox_vo->value();
    in_J0.endacc=ui->doubleSpinBox_ace->value();
    in_J0.endpos=ui->doubleSpinBox_s->value();
    in_J0.endvel=ui->doubleSpinBox_ve->value();
    in_J0.maxvel=ui->doubleSpinBox_vm->value();

    in_J1.curacc=0;
    in_J1.curpos=0;
    in_J1.curvel=2;
    in_J1.endacc=0;
    in_J1.endpos=150;
    in_J1.endvel=0;
    in_J1.maxvel=10;

    in_J2.curacc=0;
    in_J2.curpos=0;
    in_J2.curvel=1;
    in_J2.endacc=0;
    in_J2.endpos=150;
    in_J2.endvel=0;
    in_J2.maxvel=12;

    run=1;
}

//! This function simulates the servo cycle. And is called every 1 millisecond.
void MainWindow::thread(){

    if(run){
        auto start = std::chrono::high_resolution_clock::now();

        //! From here runs in servo cycle.
        motion->update(0.01,sc_motion_joint_id::id_J0,in_J0,out_J0);
        in_J0.curvel=out_J0.newvel;
        in_J0.curpos=out_J0.newpos;
        in_J0.curacc=out_J0.newacc;

        motion->update(0.01,sc_motion_joint_id::id_J1,in_J1,out_J1);
        in_J1.curvel=out_J1.newvel;
        in_J1.curpos=out_J1.newpos;
        in_J1.curacc=out_J1.newacc;

        motion->update(0.01,sc_motion_joint_id::id_J2,in_J2,out_J2);
        in_J2.curvel=out_J2.newvel;
        in_J2.curpos=out_J2.newpos;
        in_J2.curacc=out_J2.newacc;

        auto end = std::chrono::high_resolution_clock::now();
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        double t=nanoseconds_to_milliseconds(nanoseconds.count());
        tmax=std::max(t,tmax);
        std::cout<<std::fixed<<"t:"<<t<<" tmax:"<<tmax<<std::endl;

        j0_vec.push_back(in_J0.curvel);
        j1_vec.push_back(in_J1.curvel);
        j2_vec.push_back(in_J2.curvel);

    }
    myOpenGl->setj0vec(j0_vec);
    myOpenGl->setj1Vec(j1_vec);
    myOpenGl->setj2Vec(j2_vec);
}

void MainWindow::on_pushButton_stop_pressed()
{
    run=0;
}

void MainWindow::on_doubleSpinBox_acs_valueChanged(double arg1)
{
    on_pushButton_build_pressed();
}

void MainWindow::on_doubleSpinBox_ace_valueChanged(double arg1)
{
    on_pushButton_build_pressed();
}

void MainWindow::on_doubleSpinBox_vm_valueChanged(double arg1)
{
    on_pushButton_build_pressed();
}

void MainWindow::on_doubleSpinBox_a_valueChanged(double arg1)
{
    on_pushButton_build_pressed();
}

void MainWindow::on_doubleSpinBox_dv_valueChanged(double arg1)
{
    on_pushButton_build_pressed();
}

void MainWindow::on_doubleSpinBox_vo_valueChanged(double arg1)
{
    on_pushButton_build_pressed();
}

void MainWindow::on_doubleSpinBox_ve_valueChanged(double arg1)
{
    on_pushButton_build_pressed();
}

void MainWindow::on_doubleSpinBox_s_valueChanged(double arg1)
{
    on_pushButton_build_pressed();
}
