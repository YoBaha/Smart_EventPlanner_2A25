#ifndef STAT_ESP_H
#define STAT_ESP_H

#include <QDialog>

namespace Ui {
class stat_esp;
}

class stat_esp : public QDialog
{
    Q_OBJECT

public:
    explicit stat_esp(QWidget *parent = nullptr);
    ~stat_esp();
    QList<qreal> stat_espp();
    QList <QString> stat_espp_nom();

private:
    Ui::stat_esp *ui;

};

#endif // STAT_ESP_H
