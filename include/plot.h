#ifndef PLOT_H
#define PLOT_H

#include <QwtPlot>
#include <QwtPlotCurve>
#include <QMainWindow>

class Plot : public QwtPlot
{

public:
    Plot( QWidget *parent = nullptr);

};

class PlotCirc : public Plot
{

public:
    PlotCirc(QString name, QWidget *parent = nullptr);
    void updatePlot(double newX, double newY);

private:
    QPolygonF m_scatterPoint;
    QwtPlotCurve *m_scatterCurve;
};

class PlotErr : public Plot
{
public:
    PlotErr( int numIterations, QWidget *parent = nullptr);
    void updatePlot(int total, double error);
private:
    QPolygonF m_errorPoint;
    QwtPlotCurve *m_errorCurve;
};

#endif // PLOT_H
