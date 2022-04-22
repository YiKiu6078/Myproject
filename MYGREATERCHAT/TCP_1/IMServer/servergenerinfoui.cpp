#include "servergenerinfoui.h"
#include "ui_servergenerinfoui.h"

ServerGenerInfoUI::ServerGenerInfoUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerGenerInfoUI)
{
    ui->setupUi(this);
}

ServerGenerInfoUI::~ServerGenerInfoUI()
{
    delete ui;
}
