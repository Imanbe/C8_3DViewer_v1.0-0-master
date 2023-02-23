#define GL_SILENCE_DEPRECATION
#include "scene.h"
#include <iostream>

Scene::Scene(QWidget *parent):
    QOpenGLWidget (parent)
{
    setWindowTitle("3D_VIEWER_1.0");
}

//
// initializeGL, resizeGl, paintGL - переопределенные нами стандартные функции OpenGL для отображения модели
//

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

void Scene::draw() {
        glVertexPointer(3, GL_DOUBLE, 0, obj.vertex_cords);
        glEnableClientState(GL_VERTEX_ARRAY);
        glLineWidth(1);
        glColor3f(1, 1, 1);
        glDisable(GL_LINE_STIPPLE);
        glDrawElements(GL_LINES, (obj.meta_inf.faces_count), GL_UNSIGNED_INT, obj.faces_cords);
        glDisableClientState(GL_VERTEX_ARRAY);
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

void Scene::read_file(data_t *obj)
{
    QByteArray ba = filepath.toLocal8Bit();
    char *path_file = ba.data();
    Parsing(path_file, obj);

    if (obj->meta_inf.memory_check == MEMORY_OK) normalizeModel(obj);
}


//
// Функция нормализации модели:
// Вычисляем максимальный элемент в массиве модулей наших координат, если он превышает n-ую величину (зависит от области видимости вашей модельки),
// то мы разделяем её на n-ое число (ручной подбор цифр) и делим получившийся коэфицент на все элементы массива координат.
// Итог: моделька становится пропорционально маленькой
//

void Scene::normalizeModel(data_t *obj) {
    double *aspected_vertex_cords = new double[obj->meta_inf.vertex_count];

    for (unsigned i = 0; i < obj->meta_inf.vertex_count; i++) {
        aspected_vertex_cords[i] = fabs(obj->vertex_cords[i]);
    }

    double *max_elem = std::max_element(aspected_vertex_cords, aspected_vertex_cords + obj->meta_inf.vertex_count);

    if (*max_elem >= 20) {
        double aspect = *max_elem / 10.0;
        scaleBigModel(aspect);
    }
    qDebug() << "OXOYOZ_max fabs element: " << *max_elem << "\n";
    qDebug() << "checking" << "faces count in file" << obj->meta_inf.faces_count << "\n";
    delete[] aspected_vertex_cords;
}

void Scene::scaleBigModel(double aspect) {
    for (uint i = 0; i < obj.meta_inf.vertex_count; i++) {
        obj.vertex_cords[i] /= aspect;
    }
    update();
}

//
// Функция для поворота матрицы с помощью мышки
//
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

//
// Вспомогательные функции
//

void Scene::cleanOBJ(data_t *obj)
{
    free(obj->faces_cords);
    free(obj->vertex_cords);
    obj->meta_inf.poligons_count = 0;
    obj->meta_inf.faces_count = 0;
    obj->meta_inf.vertex_count = 0;
    obj->meta_inf.memory_check = 0;
}

