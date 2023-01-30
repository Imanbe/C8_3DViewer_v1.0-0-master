#include "scene.h"

Scene::Scene(QWidget *parent):
    QOpenGLWidget (parent)
{

}

void Scene::initializeGL() {
    glClearColor(1, 1, 0, 1);
}

void Scene::paintGL() {
//    glClear(GL_COLOR_BUFFER_BIT);

//    glBegin(GL_TRIANGLES);
}

void Scene::resizeGL(int w, int h) {

}
