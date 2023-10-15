#ifndef FM_PONTOS_H
#define FM_PONTOS_H

#include <QDialog>

namespace Ui {
class fm_pontos;
}

class fm_pontos : public QDialog
{
    Q_OBJECT

public:
    explicit fm_pontos(QWidget *parent = nullptr);
    ~fm_pontos();

private:
    Ui::fm_pontos *ui;
};

#endif // FM_PONTOS_H
