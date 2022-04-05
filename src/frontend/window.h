#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "chart.h"
#include "../backend/SystemRessource.h"
#include <QTabWidget>

class Window : public QWidget
{
    Q_OBJECT

//private:
//    SystemRessource systemRessource;
//    MySysInfo mySysInfo
private:
    enum{ windowSize = 800 };
    QTabWidget *tab;

public:
    Window();
private:
    void update(Chart);
    void createDetailPage();
};


#endif
