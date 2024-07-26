#include "include/plot.h"

#include <QPainter>
#include <QPen>
#include <QwtPlotCurve>

Plot::Plot(QWidget* parent) : QwtPlot(parent)
{
    setMinimumSize(200,200);
    setCanvasBackground( Qt::white );
}

PlotCirc::PlotCirc(QString name, QWidget* parent) : Plot(parent)
{
    setTitle(QString(name));
    setAxisScale( QwtAxis::YLeft, -1.1, 1.1 );
    setAxisScale( QwtAxis::XBottom, -1.1, 1.1 );

    QPolygonF circlePoints;
    QwtPlotCurve *circleCurve = new QwtPlotCurve();

    for (float x {0}; x<2*3.15; x+=0.1){
        circlePoints<<QPointF(cos(x), sin(x));
    }

    circleCurve -> setCurveAttribute(QwtPlotCurve::Fitted, true);
    circleCurve -> setSamples(circlePoints);
    circleCurve -> attach(this);

    m_scatterCurve = new QwtPlotCurve();
    m_scatterCurve -> setStyle( QwtPlotCurve::Dots );
    m_scatterCurve -> setPen(Qt::red, 1);
    m_scatterCurve -> attach(this);
}

void PlotCirc::updatePlot(double newX, double newY){
    m_scatterPoint << QPointF(newX, newY);
    m_scatterCurve -> setSamples(m_scatterPoint);
    replot();
}

PlotErr::PlotErr(int numIterations, QWidget* parent) : Plot(parent)
{
    setTitle("Error");
    setAxisScale( QwtAxis::YLeft, -1, 1 );

    QwtPlotCurve *zeroCurve = new QwtPlotCurve();
    QPolygonF zeroPoint;
    zeroPoint<<QPointF(0,0)<<QPointF(numIterations, 0);
    zeroCurve->setSamples(zeroPoint);
    zeroCurve->attach(this);

    m_errorCurve = new QwtPlotCurve();
    m_errorCurve->setCurveAttribute(QwtPlotCurve::Fitted, true);
    m_errorCurve->setPen(Qt::red, 1);
    m_errorCurve->attach(this);

}

void PlotErr::updatePlot(int total, double error)
{
    m_errorPoint<<QPointF(total, error);
    m_errorCurve->setSamples(m_errorPoint);
    replot();
}
