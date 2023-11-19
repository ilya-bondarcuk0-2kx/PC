//
// Created by tanya on 16.11.2023.
//

#include "Widgets.h"

Button::Button(QWidget *parent) : QPushButton(parent)
{
    ax = 120;
    ay = 300;
    aw = 150;
    ah = 30;
    this->setGeometry(ax, ay, aw, ah);
}

Button::~Button() {

}


Label::Label(QWidget *parent) : QLabel(parent)
{
    this->setFont(QFont("inter", 10));
}

Label::~Label() {

}

CheckBox::CheckBox(QWidget *parent) : QCheckBox(parent)
{
    this->setGeometry(90, 175, 18, 18);
}

CheckBox::~CheckBox() {

}

Message::Message(QWidget *parent) : QMessageBox(parent)
{
    this->setWindowTitle("Уведомление");
    this->setFixedSize(250, 150);
}

Message::~Message() {

}

ErrorMessage::ErrorMessage(QWidget *parent) : QErrorMessage(parent)
{
    this->setWindowTitle("Ошибка!");
    this->setFixedSize(250, 150);
}

ErrorMessage::~ErrorMessage() {

}


LineEdit::LineEdit(QWidget *parent) : QLineEdit(parent)
{
    this->setGeometry(90, 100, 200, 25);
}
LineEdit::~LineEdit()
{

}

ComboBox::ComboBox(QWidget *parent ) : QComboBox(parent)
{
    this->addItem("Темная");
    this->addItem("Светлая");
    connect(this, &QComboBox::currentTextChanged, parent, [=] {
        if (this->currentText() == "Темная") {

            QApplication::setStyle("MainWindow");
        }
        else if (this->currentText() == "Светлая")
        {
            QApplication::setStyle("windowsvista");
        }
    });
}
ComboBox::~ComboBox()
{

}