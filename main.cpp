#include <QApplication>
#include "src/frontend/chart.h"
#include "src/frontend/window.h"
#include "src/frontend/application.h"

int main(int argc, char* argv[]) 
{
    /*
    QApplication app(argc, argv);
    Window window;
    window.resize(800,800);
    window.show();
    return app.exec();
*/
    Application app(argc, argv);
    return app.exec();
}

