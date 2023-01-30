#ifndef SCENE_H
#define SCENE_H

#include <QMessageBox>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

#define GL_SILENCE_DEPRECATION

extern "C" {
#include <../src/parser.h>
}

namespace Ui {
class Scene;
}

class Scene : public QOpenGLWidget
{
    Q_OBJECT

public:
    Scene(QWidget *parent = nullptr);
    void InitalizationGL();
    void ResizeGL(int w, int h);
    void PaintGL();

private:
    Ui::Scene *ui;
};

#endif // SCENE_H
