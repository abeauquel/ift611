#include "application.h"

Application::Application(int argc, char** argv) : app(argc, argv)
{
    window.resize(800, 800);
    window.show();
}
