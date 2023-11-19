//
// Created by tanya on 20.11.2023.
//

#ifndef PASSWORDCONTAINERPROD_APPLICATIONRUN_H
#define PASSWORDCONTAINERPROD_APPLICATIONRUN_H

#include "../../Application/MainWindow/MainWindow.h"
class ApplicationRun : public QApplication {
public:
    ApplicationRun(int argc, char * argv[]);
    ~ApplicationRun() override;
private:
    MainWindow *mainWindow;
};


#endif //PASSWORDCONTAINERPROD_APPLICATIONRUN_H
