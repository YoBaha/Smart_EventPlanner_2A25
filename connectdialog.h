#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>

namespace Ui {
class connectdialog;
}

class connectdialog : public QDialog
{
    Q_OBJECT

public:
    explicit connectdialog(QWidget *parent = nullptr);
    ~connectdialog();
    QString hostname() const{
            return mHostname;
        }
        quint16 port() const{
            return mPort;
    }
private slots:
    void on_acceptbu_clicked();
    void on_cancelbu_clicked();

private:
    Ui::connectdialog *ui;
    QString mHostname;
    quint16 mPort;
};

#endif // CONNECTDIALOG_H
