#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include <QDialog>
#include <QList>
#include "Models/modelannonce.h"

namespace Ui {
class Statistiques;
}

class Statistiques : public QDialog
{
    Q_OBJECT

public:
    explicit Statistiques(QWidget *parent = 0);
    ~Statistiques();
    void StatMaison(QList<ModelAnnonce> *loMaison);
    void StatAppartement(QList<ModelAnnonce> *loAppartement);
    void StatChateau(QList<ModelAnnonce> *loChateau);
    void StatVilla(QList<ModelAnnonce> *loVilla);
    void setAnnonces(QList<ModelAnnonce> *annonces);

private:
    Ui::Statistiques *ui;
};

#endif // STATISTIQUES_H
