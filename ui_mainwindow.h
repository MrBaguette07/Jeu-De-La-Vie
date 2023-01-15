#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *principalLayout;
    QVBoxLayout *controlLayout;
    QPushButton *LancerArretBouton;
    QVBoxLayout *gridLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(500, 500);

        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");

        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");

        principalLayout = new QVBoxLayout();
        principalLayout->setObjectName("principalLayout");

        LancerArretBouton = new QPushButton(centralwidget);
        LancerArretBouton->setObjectName("LancerArretBouton");
        QFont font1;
        font1.setPointSize(24);
        LancerArretBouton->setFont(font1);

        principalLayout->addWidget(LancerArretBouton, 0, Qt::AlignHCenter);

        gridLayout = new QVBoxLayout();
        gridLayout->setObjectName("gridLayout");

        principalLayout->addLayout(gridLayout);
        gridLayout_2->addLayout(principalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    }

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Jeu de la vie", nullptr));
        LancerArretBouton->setText("LANCER");
    }

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
}

QT_END_NAMESPACE

#endif
