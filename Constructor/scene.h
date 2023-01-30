#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <stdio.h>

class Scene : public QOpenGLWidget
{
public:
    Scene(QWidget *parent);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
};

#endif // SCENE_H
