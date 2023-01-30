/********************************************************************************
** Form generated from reading UI file 'scene.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENE_H
#define UI_SCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Scene
{
public:

    void setupUi(QWidget *Scene)
    {
        if (Scene->objectName().isEmpty())
            Scene->setObjectName(QString::fromUtf8("Scene"));
        Scene->resize(624, 566);

        retranslateUi(Scene);

        QMetaObject::connectSlotsByName(Scene);
    } // setupUi

    void retranslateUi(QWidget *Scene)
    {
        Scene->setWindowTitle(QCoreApplication::translate("Scene", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Scene: public Ui_Scene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENE_H
