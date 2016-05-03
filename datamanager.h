#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QList>
#include <QtXml>
#include <QMessageBox>
#include "Models/modelannonce.h"

class Datamanager
{
public:
    Datamanager();
    static Datamanager *getInstance();

    QList<ModelAnnonce> *annonces;
    QList<ModelAnnonce> *getAnnonces();
    ModelAnnonce getAnnonce(int index);

    void registerAnnonce(ModelAnnonce a);
    void updateAnnonce(ModelAnnonce a, int index);
    void deleteAnnonce(int idx);

    bool saveToXML();
    QString loadFromXML();

    int getNewIdAnnonce();

private:
    static Datamanager *instance;


};

#endif // DATAMANAGER_H
