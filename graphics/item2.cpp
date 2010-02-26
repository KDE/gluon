#include "item2.h"
namespace GluonGraphics
{
    Item2::Item2(Mesh * mesh , QObject * parent)
        :Transform(parent)
    {
        m_mesh = mesh;
    }

    void Item2::init()
    {
        setObjectName(metaObject()->className());

    }

    void  Item2::paintGL()
    {

        glPushMatrix();
        glMultMatrixd((GLdouble*)(matrix().data()));






        glPopMatrix();

    }




}
