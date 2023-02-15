#define GL_SILENCE_DEPRECATION
#include "scene.h"
#include <iostream>

Scene::Scene(QWidget *parent):
    QOpenGLWidget (parent)
{
    setWindowTitle("3D_VIEWER_1.0");
}

void Scene::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}

void Scene::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
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

    aspected_model_width = w / 10;
    aspected_model_height = h / 10;

    int left_width = -aspected_model_width / 2;
    int right_width = aspected_model_width / 2;
    int top_height = aspected_model_height / 2;
    int down_height = -aspected_model_height / 2;
    int view_zone = 100;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left_width, right_width, down_height, top_height, -view_zone, view_zone);
}

void Scene::normalizeModel() {
//    double *aspected_vertex_cords = new double[obj.meta_inf.vertex_count*3];

//    for (unsigned i = 0; i < obj.meta_inf.vertex_count; i++) {
//        aspected_vertex_cords[i] = fabs(obj.vertex_cords[i]);
//    }

//    double *max_elem = std::max_element(aspected_vertex_cords, aspected_vertex_cords + obj.meta_inf.vertex_count*3);
//    delete[] aspected_vertex_cords;

//    if (*max_elem >= 20) {
//        double aspect = *max_elem / 10.0;
//        scaleBigModel(aspect);
//    }
//    qDebug() << "OXOYOZ_max fabs element: " << *max_elem << "\n";
    qDebug() << "checking" << "faces count in file" << obj.meta_inf.faces_count << "\n";
//    free(max_elem);
}

void Scene::scaleBigModel(double aspect) {
    for (uint i = 0; i < obj.meta_inf.vertex_count*3; i++) {
        obj.vertex_cords[i] /= aspect;
    }
    update();
}

void Scene::read_file()
{
    QByteArray ba = filepath.toLocal8Bit();  // перевод из Qstring in *str
    char *path_file = ba.data();
//    char *path_file = "/opt/goinfre/marcelit/32-mercedes-benz-gls-580-2020/uploads_files_2787791_Mercedes+Benz+GLS+580.obj";
    Parsing(path_file, &obj);
}

void Scene::draw() {
    glVertexPointer(3, GL_DOUBLE, 0, obj.vertex_cords);
    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(1);
    glColor3f(1, 1, 1);
    glDisable(GL_LINE_STIPPLE);
    glDrawElements(GL_LINES, (obj.meta_inf.faces_count * 2), GL_UNSIGNED_INT, obj.faces_cords);
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

void Scene::cleanOBJ() {
    free(obj.faces_cords);
    free(obj.vertex_cords);
    obj.meta_inf.faces_count = 0;
    obj.meta_inf.vertex_count = 0;
    obj.meta_inf.memory_check = 0;
}
