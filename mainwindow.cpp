#include "mainwindow.h"
#include "./ui_mainwindow.h"

std::vector<double> j0_vec, j1_vec, j2_vec;
bool run=0;
double tmax=0;
int cycle_delay=0;

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
    myOpenGl->set2VecShift(100);
    myOpenGl->set1VecScale(0.1);

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
    j0_vec.clear();
    j1_vec.clear();
    j2_vec.clear();

    motion->nr_of_joints(1);

    motion->set(sc_motion_joint_id::id_J0,
                ui->doubleSpinBox_a->value(),
                ui->doubleSpinBox_dv->value());

    in_J0.curacc=ui->doubleSpinBox_acs->value();
    in_J0.curpos=0;
    in_J0.curvel=ui->doubleSpinBox_vo->value();
    in_J0.endacc=ui->doubleSpinBox_ace->value();
    in_J0.endpos=ui->doubleSpinBox_s->value();
    in_J0.endvel=ui->doubleSpinBox_ve->value();
    in_J0.maxvel=ui->doubleSpinBox_vm->value();

    run=1;
}

//! This function simulates the servo cycle. And is called every 1 millisecond.
void MainWindow::thread(){

    if(run){
        //! Check for interupts.
        in_J0.maxvel=ui->doubleSpinBox_vm->value();

        auto start = std::chrono::high_resolution_clock::now();

        //! From here runs in servo cycle.
        sc_status status=motion->update(0.01,sc_motion_joint_id::id_J0,in_J0,out_J0);

        auto end = std::chrono::high_resolution_clock::now();
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        double t=nanoseconds_to_milliseconds(nanoseconds.count());
        tmax=std::max(t,tmax);
        std::cout<<std::fixed<<"t:"<<t<<" tmax:"<<tmax<<std::endl;

        j0_vec.push_back(out_J0.newvel);
        j1_vec.push_back(out_J0.newpos);
        j2_vec.push_back(out_J0.newacc);

        if(cycle_delay<50){
            cycle_delay+=1;
        } else {
            ui->label_pos->setText(QString::number(out_J0.newpos,'f',3));
            ui->label_vel->setText(QString::number(out_J0.newvel,'f',3));
            ui->label_acc->setText(QString::number(out_J0.newacc,'f',3));
            cycle_delay=0;
        }

        if(status==sc_status::Finished){
            run=0;
        }

    }
    myOpenGl->setj0vec(j0_vec);
    myOpenGl->setj1Vec(j1_vec);
    myOpenGl->setj2Vec(j2_vec);
}

void MainWindow::on_pushButton_stop_pressed()
{
    run=0;
}

