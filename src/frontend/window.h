#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "chart.h"
#include "../backend/SystemRessource.h"


class Window : public QWidget
{
    Q_OBJECT

//private:
//    SystemRessource systemRessource;
//    MySysInfo mySysInfo

public:
    Window();
private:
    void update(Chart);
};


#endif
