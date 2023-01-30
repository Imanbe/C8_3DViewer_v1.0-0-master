#include "scene.h"

#define GL_SILENCE_DEPRECATION

Scene::Scene(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setWindowTitle("3DViewer1.0");
    setGeometry(400, 200, 800, 600);
    initializeGL();
    paintGL();
}

//Scene::~Scene()
//{
//    delete ui;
//}

void Scene::InitalizationGL()
{
    glEnable(GL_DEPTH_TEST);
}

void Scene::ResizeGL(int w, int h)
{
    glViewport(0,0, w, h);
}

void Scene::PaintGL()
{
    glClearColor(0, 1, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glVertex2d(0, 0);
    glVertex2d(1, 0);
    glVertex2d(0, 1);
    glEnd();

}
