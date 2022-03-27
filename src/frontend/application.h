#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "window.h"

class Application
{

public:
    Application(int, char**);
    int exec() { return app.exec(); }
private:
    QApplication app;
    Window window;

};

#endif
