#include "windowterminal.h"

WindowTerminal::WindowTerminal() : QWidget(){
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);
    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    layout->addWidget(textEdit);
    this->setVisible(true);
}

void WindowTerminal::addText(QString txt){
    string += txt + "\n";
    textEdit->setText(string);
}
