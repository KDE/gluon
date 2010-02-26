#include "item.h"
#include "engine.h"
#include <QDebug>
namespace GluonGraphics
{
    Item::Item(Mesh * mesh , QObject * parent)
        :Transform(parent)
    {
        m_mesh = mesh;
        init();
    }

    void Item::init()
    {

        Engine::instance()->addItem(this);
        setObjectName(metaObject()->className());

    }

    void  Item::paintGL()
    {

        qDebug()<<"paint";

    }




}
