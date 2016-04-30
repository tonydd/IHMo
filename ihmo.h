#ifndef IHMO_H
#define IHMO_H

#include <QMainWindow>


namespace Ui {
class IHMo;
}

class IHMo : public QMainWindow
{
    Q_OBJECT

public:
    explicit IHMo(QWidget *parent = 0);
    ~IHMo();

private:
    Ui::IHMo *ui;

private slots:
    void addAnnonce();
    void searchAnnonce();
    void showAPropos();
    void showAide();
};

#endif // IHMO_H
