//
// Created by tanya on 16.11.2023.
//

#ifndef PASSWORDCONTAINERPROD_WIDGETS_H
#define PASSWORDCONTAINERPROD_WIDGETS_H

#include <QPushButton>
#include <QLabel>
#include <QErrorMessage>
#include <QMessageBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QApplication>

class Button : public QPushButton{
public:
    explicit Button(QWidget *parent = nullptr);
    ~Button() override;
private:
    short ax;
    short ay;
    short aw;
    short ah;
};

class Label : public QLabel{
public:
    explicit Label(QWidget *parent = nullptr);
    ~Label() override;
};

class ErrorMessage : public QErrorMessage{
public:
    explicit ErrorMessage(QWidget *parent);
    ~ErrorMessage() override;
};

class Message : public QMessageBox{
public:
    explicit Message(QWidget *parent = nullptr);
    ~Message() override;
};

class CheckBox : public QCheckBox {
public:
    explicit CheckBox(QWidget *parent = nullptr);
    ~CheckBox() override;
};

class LineEdit : public QLineEdit
{
public:
    explicit LineEdit(QWidget *parent = nullptr);
    ~LineEdit() override;
};

class ComboBox : public QComboBox
{
public:
    explicit ComboBox(QWidget *parent = nullptr);
    ~ComboBox() override;
};



#endif //PASSWORDCONTAINERPROD_WIDGETS_H
