#ifndef ADDFRDDLG_H
#define ADDFRDDLG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AddFrdDlg;
}

class AddFrdDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddFrdDlg(QWidget *parent = nullptr);
    ~AddFrdDlg();

    QString userId;
signals:
    void sendAddUserId(QString);
    void sendAddGroupId(QString);
private slots:
    void on_ConfirmBtn_clicked();

    void on_CancelBtn_clicked();

private:
    Ui::AddFrdDlg *ui;
};

#endif // ADDFRDDLG_H
