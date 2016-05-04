#ifndef IHMO_H
#define IHMO_H

#include <QMainWindow>
#include <QList>
#include <QModelIndex>
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

    void refreshTablewidget();

private:
    Ui::IHMo *ui;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void addAnnonce();
    void searchAnnonce();
    void emptySearch();
    void showAnnonce(QModelIndex index);
    void showAPropos();
    void showAide();
    void saveAnnonces();
    void showStatistiques();

    void deleteRow();
};

#endif // IHMO_H
