#define _USE_MATH_DEFINES

#include "include/mainwindow.h"

#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Monte Carlo Pi");
    m_pointIn = 0;
    m_pointTotal = 0;

    m_labelPi = new QLabel(this);
    m_labelPi->setText(QString::number(0));


    m_plotCirc = new PlotCirc();
    m_plotErr = new PlotErr();

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_plotCirc,45);
    layout->addWidget(m_plotErr,45);
    layout->addWidget(m_labelPi,10);

    m_idTimer = startTimer(1);
}

void MainWindow::timerEvent( QTimerEvent* )
{
    double newX = (arc4random() / pow(2,32) * 2)-1;
    double newY = (arc4random() / pow(2,32) * 2)-1;

    m_pointTotal = m_pointTotal+1;
    if (pow(newX, 2)+pow(newY, 2) < 1){
        m_pointIn = m_pointIn+1;
    }

    double result = static_cast<double>(m_pointIn)/static_cast<double>(m_pointTotal)*4.0;

    m_plotCirc->updatePlot(newX, newY);
    m_plotErr->updatePlot(m_pointTotal, result-M_PI);
    m_labelPi->setText(QString::number(result));

    if (m_pointTotal==10000){
        (void) killTimer(m_idTimer);
    }
}
