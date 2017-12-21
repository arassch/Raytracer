#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QThread>
#include <QTimer>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Definitions.h"
#include "Scene.h"
#include "RenderAlg.h"
#include "DirectIllumination.h"
#include "GlobalIllumination.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new Scene();
    m_algorithm = new GlobalIllumination(m_scene);

    m_renderThread = new QThread;
    m_algorithm->moveToThread(m_renderThread);

    connect(m_renderThread, SIGNAL(started()), m_algorithm, SLOT(process()));
    connect(m_algorithm, SIGNAL(finished()), m_renderThread, SLOT(quit()));
//    connect(m_algorithm, SIGNAL(finished()), m_algorithm, SLOT(deleteLater()));
//    connect(m_renderThread, SIGNAL(finished()), m_renderThread, SLOT(deleteLater()));
    connect(m_algorithm, SIGNAL(finished()), this, SLOT(writeToFile()));
    m_renderThread->start();

    m_qscene = new QGraphicsScene( this );

    QImage image(( unsigned char*)m_algorithm->pixels,
                 m_scene->getResX(), m_scene->getResY(),
                 QImage::Format_RGB888);
    m_pixmapItem = m_qscene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(m_qscene);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);


}

MainWindow::~MainWindow()
{
    m_algorithm->deleteLater();
    m_renderThread->deleteLater();
    delete ui;
}

void MainWindow::update()
{
//    if(m_renderThread->isFinished())
//        return;
    QImage image(( unsigned char*)m_algorithm->pixels, m_scene->getResX(), m_scene->getResY(), QImage::Format_RGB888);
    m_pixmapItem->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::writeToFile()
{
    m_algorithm->writeToFile("out.png");
}

void MainWindow::restartRender()
{
    m_algorithm->restart();
    if(m_renderThread->isFinished())
        m_renderThread->start();
}

void MainWindow::setDrawNormals(bool draw)
{
    m_algorithm->setDrawNormals(draw);
    restartRender();
}

void MainWindow::setDrawAmbient(bool draw)
{
    m_algorithm->setDrawAmbient(draw);
    restartRender();
}

void MainWindow::setDrawDiffuse(bool draw)
{
    m_algorithm->setDrawDiffuse(draw);
    restartRender();
}

void MainWindow::setDrawSpecular(bool draw)
{
    m_algorithm->setDrawSpecular(draw);
    restartRender();
}

void MainWindow::setDrawIndirect(bool draw)
{
    m_algorithm->setDrawIndirect(draw);
    restartRender();
}

void MainWindow::setMaxDepth(int depth)
{
    m_algorithm->setMaxDepth(depth);
    restartRender();
}

void MainWindow::setNumBounceDirections(int numDirections)
{
    m_algorithm->setNumBounceDirections(numDirections);
    restartRender();
}

void MainWindow::setNumSubpixels(int num)
{
//    int pow2 = 0;
//    int exponent = -1;

//    // Find current exponent
//    do
//    {
//        exponent++;
//        pow2 = pow(2, exponent);
//    } while(m_algorithm->getNumSubpixels() > pow2);


//    if(m_algorithm->getNumSubpixels() < num)
//    {
//        exponent++;
//        pow2 = pow(2,exponent);
//    }
//    else
//    {
//        exponent--;
//        pow2 = pow(2,exponent);
//    }
//    ui->subpixels->setValue(pow2);
    m_algorithm->setNumSubpixels(num);
    restartRender();
}
