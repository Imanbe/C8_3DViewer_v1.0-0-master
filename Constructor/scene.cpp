#include "scene.h"
#include <iostream>

#define GL_SILENCE_DEPRECATION

Scene::Scene(QWidget *parent):
    QOpenGLWidget (parent)
{
    setWindowTitle("3D_VIEWER_1.0");
}

void Scene::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}

void Scene::paintGL() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -3);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glRotatef(zRot, 0, 0, 1);
    draw();
}

void Scene::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, 2, 99999);
//    glFrustum(-1, 1, -1, 1, 1, 99999);
}

void Scene::read_file()
{
    QByteArray ba = filepath.toLocal8Bit();  // перевод из Qstring in *str
    char *path_file = ba.data();
    Parsing(path_file, &obj);
    update();
}

void Scene::draw() {
    glVertexPointer(3, GL_DOUBLE, 0, obj.vertex_cords);

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1, 1, 1);
    glDrawArrays(GL_POINTS, 0, obj.vertex_count);
    glDisable(GL_LINE_STIPPLE);
    glEnable(GL_LINE);
    glDrawElements(GL_LINES, (obj.faces_count * 3), GL_UNSIGNED_INT, obj.faces_cords);
    glLineWidth(1);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Scene::mousePressEvent(QMouseEvent * mo)
{
    mPos = mo->pos();
}

void Scene::mouseMoveEvent(QMouseEvent *mo)
{
    xRot = 1/M_PI*(mo->pos().y() - mPos.y());
    yRot = 1/M_PI*(mo->pos().x() - mPos.x());
    update();
}
