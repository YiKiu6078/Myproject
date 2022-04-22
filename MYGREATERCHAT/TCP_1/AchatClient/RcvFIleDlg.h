#ifndef RCVFILEDLG_H
#define RCVFILEDLG_H

#include <QDialog>
#include <QMessageBox>
#include <QtDebug>

namespace Ui {
class RcvFIleDlg;
}

class RcvFIleDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RcvFIleDlg(QWidget *parent = nullptr);
    ~RcvFIleDlg();

    qint64 fileTotalSize;
    QString userId;

private slots:
    void processSlot(qint64);

private:
    Ui::RcvFIleDlg *ui;
};

#endif // RCVFILEDLG_H
