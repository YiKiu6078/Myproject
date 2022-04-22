#ifndef PERSONINFO_H
#define PERSONINFO_H

#include <QDialog>

namespace Ui {
class PersonInfo;
}

class PersonInfo : public QDialog
{
    Q_OBJECT

public:
    explicit PersonInfo(QWidget *parent = nullptr);
    ~PersonInfo();

    void rcvPersonInfo(QString userId,QString nickName, QString signature,QString age,
                       QString sex, QString email);
private:
    Ui::PersonInfo *ui;
};

#endif // PERSONINFO_H
