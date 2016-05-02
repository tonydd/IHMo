#ifndef IHMO_H
#define IHMO_H

#include <QMainWindow>
#include <QList>
#include "Models/modelannonce.h"
#include "datamanager.h"


namespace Ui {
class IHMo;
}

class IHMo : public QMainWindow
{
    Q_OBJECT

public:
    explicit IHMo(QWidget *parent = 0);
    ~IHMo();

    static IHMo* instance;
    static IHMo* getInstance();

    Datamanager *getManager();
    void refreshTablewidget();

private:
    Ui::IHMo *ui;
    Datamanager *manager;

private slots:
    void addAnnonce();
    void searchAnnonce();
    void showAnnonce();
    void showAPropos();
    void showAide();
};

#endif // IHMO_H
