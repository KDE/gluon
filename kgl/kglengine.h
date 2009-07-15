#ifndef KGLENGINE_H
#define KGLENGINE_H

#include <QObject>
#include <QMap>
#include "kglbaseitem.h"
#include "kglitemlist.h"
#include "kglitem.h"
#include "kglboxitem.h"
#include "kgltextitem.h"

typedef QMap<unsigned int, KGLItemList > IndexGroupMap;

class KGLEngine : public QObject
{
    Q_OBJECT
public:
    KGLEngine(QObject * parent=0);
    virtual void mainLoop(float fps=60);
    void addItem(KGLItem* item);
    void addItems(const KGLItemList* items);
    bool removeItem(KGLItem* item);
    bool removeItems(const KGLItemList *item);
    bool eraseItem(KGLItem* item);
    bool eraseItems(const KGLItemList *item);
    KGLItem * itemAt(int id, unsigned int layer=0);
    int itemsCount() const;
    KGLBoxItem * addBox(float w, float h){KGLBoxItem * b = new KGLBoxItem(w,h); addItem(b); return b;}
    IndexGroupMap items(){return m_items;}





    private:
      IndexGroupMap m_items;
};

#endif // KGLENGINE_H
