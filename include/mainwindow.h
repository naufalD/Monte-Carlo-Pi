#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plot.h"

#include <QMainWindow>
#include <QLabel>
#include <QElapsedTimer>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    virtual void timerEvent( QTimerEvent* ) QWT_OVERRIDE;

private:
    PlotCirc *m_plotCirc1;
    PlotErr *m_plotErr1;
    QLabel *m_labelPi1;

    PlotCirc *m_plotCirc2;
    PlotErr *m_plotErr2;
    QLabel *m_labelPi2;

    QElapsedTimer m_timer;
    int m_pointIn1;
    int m_pointIn2;
    int m_pointTotal;
    int m_idTimer;
    int m_pause;
    int m_numIterations;

};
#endif // MAINWINDOW_H
