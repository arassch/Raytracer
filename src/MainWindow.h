#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "Scene.h"
#include "RenderAlg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

public Q_SLOTS:
    void update();
    void writeToFile();

    void restartRender();
    void setDrawNormals(bool draw);
    void setDrawAmbient(bool draw);
    void setDrawDiffuse(bool draw);
    void setDrawSpecular(bool draw);
    void setDrawIndirect(bool draw);

    void setMaxDepth(int depth);
    void setNumBounceDirections(int numDirections);

    void setNumSubpixels(int num);


private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_qscene;
    QGraphicsPixmapItem *m_pixmapItem;

    Scene *m_scene;
    RenderAlg *m_algorithm;
    QThread* m_renderThread;
};

#endif // MAINWINDOW_H
