#include "ApplicationRun.h"
ApplicationRun::ApplicationRun(int argc, char * argv[]) : QApplication(argc, argv)
{
    setlocale(LC_ALL, "");
    this->setStyle("Windows");
    mainWindow = new MainWindow();
    ApplicationRun::exec();
}
ApplicationRun::~ApplicationRun()
{
    delete mainWindow;
    delete this;
}