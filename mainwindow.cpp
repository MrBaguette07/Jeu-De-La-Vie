#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grillewidget.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , grille(new GrilleWidget(this))
{
    ui->setupUi(this);
    ui->gridLayout->addWidget(grille);

    setLancerArret();
}

MainWindow::~MainWindow()
{
    delete grille;
    delete ui;
}

QColor MainWindow::getTextBouton() const
{
    return CouleurTextBouton;
}

void MainWindow::setCouleurTextBouton(const QColor& couleur)
{
    CouleurTextBouton = couleur;
}


void MainWindow::setLancerArret()
{
    ui->LancerArretBouton->setStyleSheet("QPushButton {background-color: " + grille->getCouleurBackground().name() + "; color: " + getTextBouton().name() + "; padding: 10px; border-radius: 10px}");
    connect(ui->LancerArretBouton, SIGNAL(clicked()), this, SLOT(editLancerArretBouton()));
    connect(ui->LancerArretBouton, SIGNAL(clicked()), grille, SLOT(DecisionDeLEvolution()));
}

void MainWindow::editLancerArret(const char* cmd)
{
    ui->LancerArretBouton->setText(cmd);
}

void MainWindow::editLancerArretBouton()
{
    if (grille->getEvolution2())
    {
        editLancerArret("LANCER");
    }
    else
    {
        editLancerArret("ARRÊTER");
    }
}
