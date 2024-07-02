#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plot.h"

#include <QMainWindow>
#include <QLabel>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    virtual void timerEvent( QTimerEvent* ) QWT_OVERRIDE;

private:
    PlotCirc *m_plotCirc;
    PlotErr *m_plotErr;
    QLabel *m_labelPi;
    int m_pointIn;
    int m_pointTotal;
    int m_idTimer;

};
#endif // MAINWINDOW_H
