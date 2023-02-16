#include <math.h>
#include <mainwindow.h>
#include <iostream>
#include <opengl.h>
#include <vector>

double xScale=0;
double yScale=0;
double t=0;
double interval=0.01;

std::vector<double> y1Vec, y2Vec, y3Vec;
double shifty1Vec, shifty2Vec, shifty3Vec;

opengl::opengl(QWidget *parent)
    : QOpenGLWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(50);
}

opengl::~opengl()
{
    //! destructor
}

void opengl::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_STIPPLE);
    setMouseTracking(true);
}

void opengl::resizeGL(int w, int h)
{
    // std::cout<<"resize"<<std::endl;
    glViewport(0, 0, w, h);
}

void opengl::setScale(double thexScale, double theyScale){
    xScale=thexScale;
    yScale=theyScale;
}

void opengl::setInterval(double theInterval){
    interval=theInterval;
}

void opengl::set1Vec(std::vector<double> theyVec){
    y1Vec=theyVec;
}

void opengl::set2Vec(std::vector<double> theyVec){
    y2Vec=theyVec;
}

void opengl::set3Vec(std::vector<double> theyVec){
    y3Vec=theyVec;
}

void opengl::set1VecShift(double theyShift){
    shifty1Vec=theyShift;
}

void opengl::set2VecShift(double theyShift){
    shifty2Vec=theyShift;
}

void opengl::set3VecShift(double theyShift){
    shifty3Vec=theyShift;
}

void opengl::paintGL()
{


    glViewport(0, 0, this->width(), this->height());
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this->width(), this->height(), 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4d(255,0,0,255);
    glBegin(GL_LINE_STRIP);
    glLineWidth(1);
    t=0;
    for(uint i=0; i<y1Vec.size(); i++){
        glVertex2d(t*xScale,(this->height()+shifty1Vec)-(y1Vec.at(i)*yScale));
        t+=interval;
    }
    glEnd();

    glColor4d(255,255,0,255);
    glBegin(GL_LINE_STRIP);
    t=0;
    for(uint i=0; i<y2Vec.size(); i++){
        double scale=0.5;
        glVertex2d(t*xScale,(this->height()+shifty2Vec)-(y2Vec.at(i)*scale));
        t+=interval;
    }
    glEnd();

    glColor4d(255,255,255,255);
    glBegin(GL_LINE_STRIP);
    t=0;
    for(uint i=0; i<y3Vec.size(); i++){
        glVertex2d(t*xScale,(this->height()+shifty3Vec)-(y3Vec.at(i)*yScale));
        t+=interval;
    }
    glEnd();

}












