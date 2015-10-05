#ifndef WINDOWTERMINAL_H
#define WINDOWTERMINAL_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>

class WindowTerminal : public QWidget
{
    public:
        WindowTerminal();
        void addText(QString);

    private:
        QString string;
        QTextEdit* textEdit;
};

#endif // WINDOWTERMINAL_H
