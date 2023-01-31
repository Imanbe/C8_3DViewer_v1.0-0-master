#include "scene.h"

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
    glClearColor(0, 1, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -2);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    drawCube(0.5);
}

void Scene::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-1, 1, -1, 1, 1, 2);
    glFrustum(-1, 1, -1, 1, 1, 3);
}

void Scene::drawCube(float a)
{
    float ver_cub[] = {
        -a, -a, a, a, -a, a, a, a, a, -a, a, a,
        a, -a, -a, -a, -a, -a, -a, a, -a, a, a, -a,
        -a, -a, -a, -a, -a, a, -a, a, a, -a, a, -a,
        a, -a, a, a, -a, -a, a, a, -a, a, a, a,
        -a, -a, a, a, -a, a, a, -a, -a, -a, -a, -a,
        -a, a, a, a, a, a, a, a, -a, -a, a, -a
    };
    float color_arr[] = {
        1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,
        0, 0, 1,  0, 0, 1,  0, 0, 1,  0, 0, 1,
        1, 1, 0,  1, 1, 0,  1, 1, 0,  1, 1, 0,
        0, 1, 1,  0, 1, 1,  0, 1, 1,  0, 1, 1,
        1, 0, 1,  1, 0, 1,  1, 0, 1,  1, 0, 1,
        1, 0.5, 0.5,  1, 0.5, 0.5,  1, 0.5, 0.5,  1, 0.5, 0.5
    };
    glVertexPointer(3, GL_FLOAT, 0, &ver_cub);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_COLOR_ARRAY);
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
