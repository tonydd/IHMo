#ifndef ANNONCE_H
#define ANNONCE_H

#include <QDialog>

namespace Ui {
class Annonce;
}

class Annonce : public QDialog
{
    Q_OBJECT

public:
    explicit Annonce(QWidget *parent = 0);
    ~Annonce();

private:
    Ui::Annonce *ui;

private slots:
    void addAnnonce();
    void searchAnnonce();
};

#endif // ANNONCE_H
