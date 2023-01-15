#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "grillewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QColor CouleurTextBouton READ getTextBouton WRITE setCouleurTextBouton DESIGNABLE true)

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    QColor getTextBouton() const;
    void setCouleurTextBouton(const QColor& colour);

private:
    Ui::MainWindow* ui;
    GrilleWidget* grille;
    QColor CouleurTextBouton = Qt::white;
    void setLayout();
    void setLancerArret();
    void editLancerArret(const char* cmd);

private slots:
    void editLancerArretBouton();
};
#endif
