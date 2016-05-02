#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QList>
#include "Models/modelannonce.h"

class Datamanager
{
public:
    Datamanager();

    QList<ModelAnnonce> *annonces;
    QList<ModelAnnonce> *getAnnonces();
    ModelAnnonce getAnnonce(int index);

    void registerAnnonce(ModelAnnonce a);
    void updateAnnonce(ModelAnnonce a, int index);

    static Datamanager *getInstance();

private:
    static Datamanager *instance;

    void saveToXML();
    void loadFromXML();

};

#endif // DATAMANAGER_H
