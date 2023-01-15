#ifndef GRILLEWIDGET_H
#define GRILLEWIDGET_H

#include <QWidget>
#include <random>

class GrilleWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor BordureCouleur READ getCouleurBackground WRITE setBordureCouleur DESIGNABLE true)
    Q_PROPERTY(qreal BordureTaille READ getBordureTaille WRITE setBordureTaille DESIGNABLE true)
    Q_PROPERTY(QColor CouleurBlocs READ getCouleurBlocs WRITE setCouleurBlocs DESIGNABLE true)
    Q_PROPERTY(QColor CouleurCellule READ getCouleurCellule WRITE setCouleurCellule DESIGNABLE true)
    Q_PROPERTY(qreal CeluleGrilleMarge READ getCeluleGrilleMarge WRITE setCeluleGrilleMarge DESIGNABLE true)
    Q_PROPERTY(bool Evolution2 READ getEvolution2 WRITE setEvolution2 DESIGNABLE true)

public:
    explicit GrilleWidget(QWidget* parent = nullptr);
    ~GrilleWidget();

    int getNombreLigne() const;
    int getColonneLigne() const;
    int getnombreGeneration() const;
    int getTimerInterval() const;

    QColor getCouleurBackground() const;
    void setBordureCouleur(const QColor& couleur);

    qreal getBordureTaille() const;
    void setBordureTaille(const qreal& thickness);

    QColor getCouleurBlocs() const;
    void setCouleurBlocs(const QColor& couleur);

    QColor getCouleurCellule() const;
    void setCouleurCellule(const QColor& couleur);

    qreal getCeluleGrilleMarge() const;
    void setCeluleGrilleMarge(const qreal& margin);

    bool getEvolution2() const;
    void setEvolution2(const bool& cmd);

    enum cellPopulationOption
    {
        Empty,
        Filled,
        echec,
        Random
    };

public slots:
    void setnombreLigne(const int& nRows);
    void setnombreColonne(const int& nColumns);
    void setnombreGeneration(const int& nGenerations);
    void setTimerInterval(const int& msec);

    void creategrille(cellPopulationOption pattern);
    void deletegrille();

    void stopEvolve();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void nombreGenerationChanged(const int& nGenerations);
    void universeSizeAdjustable(const bool& cmd);

private:

    int nombreLigne = 20;
    int nombreColonne = 20;
    int** grille;
    QTimer* timer;
    bool Evolution2 = false;
    int nombreGeneration = 0;
    cellPopulationOption dame = echec;

    // Méthode random trouvée sur internet, c'était compliqué...
    std::mt19937 randNumGenerator;
    std::uniform_int_distribution<int> randDistribution;

    void setTimer();
    void evolveContinuous();
    void createechecgrille();

    QColor BordureCouleur = "#ffbb00";
    qreal BordureTaille = 0.0;
    QColor CouleurBlocs = "#fff";
    QColor CouleurCellule = "#ffbb00";
    qreal CeluleGrilleMarge = 1.0;

    void settransparence();

    qreal calculLargeur();
    qreal calculHauteur();
    qreal calculCeluleLargeur();
    qreal calculCeluleHauteur();

    void couleurBordureAjout(QPainter& painter);
    void couleurCelluleAjout(QPainter& painter);

private slots:
    void LancerEvolution();
    void DecisionDeLEvolution();
};

#endif
