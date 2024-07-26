#define _USE_MATH_DEFINES

#include "include/mainwindow.h"
#include "include/quasirandom.h"

#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Monte Carlo Pi");
    m_pointIn1 = 0;
    m_pointIn2 = 0;
    m_pointIn3 = 0;
    m_pointTotal = 0;
    m_pause = 0;
    m_numIterations = 10000;

    unsigned int initial1[18] {1};
    sobolRNG1 = new sobolDimension(1, 1,  initial1, true);

    unsigned int initial2[18] {1};
    sobolRNG2 = new sobolDimension(1, 1, initial2, false);
    sobolRNG2->nextPoint();

    m_labelPi1 = new QLabel(this);
    m_labelPi1->setText(QString::number(0));
    m_plotCirc1 = new PlotCirc("Uniform Random");
    m_plotErr1 = new PlotErr(m_numIterations);

    m_labelPi2 = new QLabel(this);
    m_labelPi2->setText(QString::number(0));
    m_plotCirc2 = new PlotCirc("Halton Sequence");
    m_plotErr2 = new PlotErr(m_numIterations);

    m_labelPi3 = new QLabel(this);
    m_labelPi3->setText(QString::number(0));
    m_plotCirc3 = new PlotCirc("Sobol Sequence");
    m_plotErr3 = new PlotErr(m_numIterations);

    QHBoxLayout* layout1 = new QHBoxLayout();
    layout1->addWidget(m_plotCirc1,45);
    layout1->addWidget(m_plotErr1,45);
    layout1->addWidget(m_labelPi1,10);

    QHBoxLayout* layout2 = new QHBoxLayout();
    layout2->addWidget(m_plotCirc2,45);
    layout2->addWidget(m_plotErr2,45);
    layout2->addWidget(m_labelPi2,10);

    QHBoxLayout* layout3 = new QHBoxLayout();
    layout3->addWidget(m_plotCirc3,45);
    layout3->addWidget(m_plotErr3,45);
    layout3->addWidget(m_labelPi3,10);

    QVBoxLayout* layoutmain = new QVBoxLayout(this);
    layoutmain->addLayout(layout1);
    layoutmain->addLayout(layout2);
    layoutmain->addLayout(layout3);

    m_idTimer = startTimer(1);
    m_timer.start();
}

void MainWindow::timerEvent( QTimerEvent* )
{
    if (m_pause==0){
        if (m_timer.elapsed()>5000){
            m_pause=1;
            m_timer.start();
        }
    }
    else{
        m_pointTotal = m_pointTotal+1;

        double newX {0};// (arc4random() / pow(2,32) * 2)-1;
        double newY {0};// (arc4random() / pow(2,32) * 2)-1;

        // if (pow(newX, 2)+pow(newY, 2) < 1){
        //     m_pointIn1 = m_pointIn1+1;
        // }

        double result {0};// = static_cast<double>(m_pointIn1)/static_cast<double>(m_pointTotal)*4.0;

        // m_plotCirc1->updatePlot(newX, newY);
        // m_plotErr1->updatePlot(m_pointTotal, result-M_PI);
        // m_labelPi1->setText(QString::number(result));

        // --------------------------------------------------

        // newX = (haltonQuasi(m_timer.elapsed(), 2)*2)-1;
        // newY = (haltonQuasi(m_timer.elapsed(), 3)*2)-1;

        // if (pow(newX, 2)+pow(newY, 2) < 1){
        //     m_pointIn2 = m_pointIn2+1;
        // }

        // result = static_cast<double>(m_pointIn2)/static_cast<double>(m_pointTotal)*4.0;

        // m_plotCirc2->updatePlot(newX, newY);
        // m_plotErr2->updatePlot(m_pointTotal, result-M_PI);
        // m_labelPi2->setText(QString::number(result));

        // --------------------------------------------------

        newX = (sobolRNG1->getPoint()*2)-1;
        newY = (sobolRNG2->getPoint()*2)-1;
        sobolRNG1->nextPoint();
        sobolRNG2->nextPoint();

        if (pow(newX, 2)+pow(newY, 2) < 1){
            m_pointIn3 = m_pointIn3+1;
        }

        result = static_cast<double>(m_pointIn3)/static_cast<double>(m_pointTotal)*4.0;

        m_plotCirc3->updatePlot(newX, newY);
        m_plotErr3->updatePlot(m_pointTotal, result-M_PI);
        m_labelPi3->setText(QString::number(result));

        if (m_pointTotal==m_numIterations){
            (void) killTimer(m_idTimer);
        }
    }
}
