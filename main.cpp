#include "src/backend/WriteFile.h"
#include "src/frontend/application.h"

int main(int argc, char* argv[]) 
{
    WriteFile::startArchive(1000);
    Application app(argc, argv);
    return app.exec();
}

