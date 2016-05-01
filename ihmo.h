#ifndef IHMO_H
#define IHMO_H

#include <QMainWindow>
#include <QList>
#include "Models/modelannonce.h"


namespace Ui {
class IHMo;
}

class IHMo : public QMainWindow
{
    Q_OBJECT

public:
    explicit IHMo(QWidget *parent = 0);
    ~IHMo();

    static QList<ModelAnnonce> annonces;
    static QList<ModelAnnonce>* getAnnonces();
    static void registerAnnonce(ModelAnnonce a);

private:
    Ui::IHMo *ui;

private slots:
    void addAnnonce();
    void searchAnnonce();
    void showAPropos();
    void showAide();
};

#endif // IHMO_H
