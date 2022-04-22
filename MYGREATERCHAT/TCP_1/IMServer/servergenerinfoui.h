#ifndef SERVERGENERINFOUI_H
#define SERVERGENERINFOUI_H

#include <QWidget>

namespace Ui {
class ServerGenerInfoUI;
}

class ServerGenerInfoUI : public QWidget
{
    Q_OBJECT

public:
    explicit ServerGenerInfoUI(QWidget *parent = nullptr);
    ~ServerGenerInfoUI();

private:
    Ui::ServerGenerInfoUI *ui;
};

#endif // SERVERGENERINFOUI_H
