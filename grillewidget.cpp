#include <cmath>

#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

#include "grillewidget.h"
#include "jeuLogique.h"

GrilleWidget::GrilleWidget(QWidget* parent) : QWidget(parent), randNumGenerator((std::random_device())()), randDistribution(1, 10)
{
    settransparence();
    setTimer();
    creategrille(dame);
}

GrilleWidget::~GrilleWidget()
{
    delete timer;
    deletegrille();
}

int GrilleWidget::getNombreLigne() const
{
    return nombreLigne;
}

void GrilleWidget::setnombreLigne(const int& nRows)
{
    deletegrille();
    nombreLigne = nRows;
    creategrille(dame);
    update();
}

int GrilleWidget::getColonneLigne() const
{
    return nombreColonne;
}

void GrilleWidget::setnombreColonne(const int& nColumns)
{
    deletegrille();
    nombreColonne = nColumns;
    creategrille(dame);
    update();
}

int GrilleWidget::getnombreGeneration() const
{
    return nombreGeneration;
}

void GrilleWidget::setnombreGeneration(const int& nGenerations)
{
    nombreGeneration = nGenerations;
}

int GrilleWidget::getTimerInterval() const
{
    return timer->interval();
}

void GrilleWidget::setTimerInterval(const int& msec)
{
    timer->setInterval(msec);
}

QColor GrilleWidget::getCouleurBackground() const
{
    return BordureCouleur;
}

void GrilleWidget::setBordureCouleur(const QColor& couleur)
{
    BordureCouleur = couleur;
}

qreal GrilleWidget::getBordureTaille() const
{
    return BordureTaille;
}

void GrilleWidget::setBordureTaille(const qreal& thickness)
{
    BordureTaille = thickness;
}

QColor GrilleWidget::getCouleurBlocs() const
{
    return CouleurBlocs;
}

void GrilleWidget::setCouleurBlocs(const QColor& couleur)
{
    CouleurBlocs = couleur;
}

QColor GrilleWidget::getCouleurCellule() const
{
    return CouleurCellule;
}

void GrilleWidget::setCouleurCellule(const QColor& couleur)
{
    CouleurCellule = couleur;
}

qreal GrilleWidget::getCeluleGrilleMarge() const
{
    return CeluleGrilleMarge;
}

void GrilleWidget::setCeluleGrilleMarge(const qreal& margin)
{
    CeluleGrilleMarge = margin;
}

bool GrilleWidget::getEvolution2() const
{
    return Evolution2;
}

void GrilleWidget::setEvolution2(const bool& cmd)
{
    Evolution2 = cmd;
}

void GrilleWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    couleurBordureAjout(painter);
    couleurCelluleAjout(painter);
}

void GrilleWidget::mousePressEvent(QMouseEvent* event)
{
    int ligneIdx = static_cast<int>(std::floor((event->y() - 1 * BordureTaille) / calculCeluleHauteur()));
    int colonneIdx = static_cast<int>(std::floor((event->x() - 1 * BordureTaille) / calculCeluleLargeur()));
    grille[ligneIdx][colonneIdx] ^= 1;
    update();
}

void GrilleWidget::couleurBordureAjout(QPainter& painter)
{
    QRect universeBorder(0, 0, width(), height());
    painter.setBrush(QBrush(CouleurBlocs));
    painter.fillRect(universeBorder, painter.brush());
    painter.drawRect(universeBorder);
}

void GrilleWidget::couleurCelluleAjout(QPainter& painter)
{
    for (int ligneIdx = 0; ligneIdx < nombreLigne; ++ligneIdx)
    {
        for (int colonneIdx = 0; colonneIdx < nombreColonne; ++colonneIdx)
        {
            if (grille[ligneIdx][colonneIdx] == 1)
            {
                qreal cellLeftIdx = 1 * BordureTaille + calculCeluleLargeur() * colonneIdx + CeluleGrilleMarge;
                qreal cellTopIdx = 1 * BordureTaille + calculCeluleHauteur() * ligneIdx + CeluleGrilleMarge;
                QRect cellField(cellLeftIdx, cellTopIdx, calculCeluleLargeur() - CeluleGrilleMarge, calculCeluleHauteur() - CeluleGrilleMarge);
                painter.setBrush(QBrush(CouleurCellule));
                painter.fillRect(cellField, painter.brush());
            }
        }
    }
}

void GrilleWidget::deletegrille()
{
    for (int ligneIdx = 0; ligneIdx < nombreLigne; ++ligneIdx)
    {
        delete[] grille[ligneIdx];
    }
    delete[] grille;
}

void GrilleWidget::creategrille(cellPopulationOption pattern)
{
    dame = pattern;
    createechecgrille();
}

void GrilleWidget::createechecgrille()
{
    grille = new int*[nombreLigne];
    for (int ligneIdx = 0; ligneIdx < nombreLigne; ++ligneIdx)
    {
        grille[ligneIdx] = new int[nombreColonne];
        for (int colonneIdx = 0; colonneIdx < nombreColonne; ++colonneIdx)
        {
            grille[ligneIdx][colonneIdx] = ((ligneIdx + colonneIdx) & 1) ? 0 : 1;
        }
    }
}

void GrilleWidget::setTimer()
{
    timer = new QTimer(this);
    timer->setInterval(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(LancerEvolution()));
}

void GrilleWidget::evolveContinuous()
{
    timer->start();
    emit universeSizeAdjustable(false);
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void GrilleWidget::stopEvolve()
{
    timer->stop();
    emit universeSizeAdjustable(true);
    this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void GrilleWidget::settransparence()
{
    BordureCouleur.setAlpha(255);
    CouleurBlocs.setAlpha(255);
    CouleurCellule.setAlpha(255);
}

qreal GrilleWidget::calculLargeur()
{
    return width() - 1.5 * BordureTaille;
}

qreal GrilleWidget::calculHauteur()
{
    return height() - 1.5 * BordureTaille;
}

qreal GrilleWidget::calculCeluleLargeur()
{
    return calculLargeur() / nombreColonne;
}

qreal GrilleWidget::calculCeluleHauteur()
{
    return calculHauteur() / nombreLigne;
}

void GrilleWidget::LancerEvolution()
{
    Generation(grille, nombreLigne, nombreColonne);
    emit nombreGenerationChanged(++nombreGeneration);
    update();
}

void GrilleWidget::DecisionDeLEvolution()
{
    Evolution2 = !Evolution2;

    if (Evolution2)
    {
        evolveContinuous();
    }
    else
    {
        stopEvolve();
    }
}
