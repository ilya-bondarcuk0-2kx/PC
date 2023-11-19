//
// Created by tanya on 16.11.2023.
//

#ifndef PASSWORDCONTAINERPROD_MAINWINDOW_H
#define PASSWORDCONTAINERPROD_MAINWINDOW_H


#include "../../Application/Sections/Sections.h"
#include "../../Application/Service/SqlDB/DataBase.h"
#include "../../Application/User/User.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void showUpdateWindow();
    ~MainWindow() override;
private:
    HelloSection *helloSection;
    SignInSection *signInSection;
    SignUpSection *signUpSection;
    MainSection *mainSection;
    EmailCodeSection *emailSection;
    QStackedWidget *stackedWidget;
    DataBase *dataBase;
    User *user;
    Button *updateWindowButton;
    UpdateAppWindow *updateWindow;
    ComboBox *themeComboBox;
    SqlQuery *sqlQuery;
    bool isUserRemembered;
};



#endif //PASSWORDCONTAINERPROD_MAINWINDOW_H
