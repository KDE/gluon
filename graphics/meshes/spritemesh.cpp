#include "spritemesh.h"

using namespace GluonGraphics;

class SpriteMesh::SpriteMeshPrivate
{
    public:
        QSizeF size;
};

SpriteMesh::SpriteMesh(QObject * parent)
        : Mesh(parent)
{
    d = new SpriteMeshPrivate;
    setSize(QSizeF(1.0f, 1.0f));
}

SpriteMesh::SpriteMesh(const QSizeF& size, QObject* parent)
        : Mesh(parent)
{
    d = new SpriteMeshPrivate;
    setSize(size);
}

SpriteMesh::~SpriteMesh()
{
    delete d;
}

void
SpriteMesh::setSize(const QSizeF &size)
{
    d->size = size;

    float halfw = size.width() / 2.0f;
    float halfh = size.height() / 2.0f;

    if (vertexCount() < 4)
    {
        for (int i = 0; i < 4; ++i)
        {
            addVertex(QVector2D());
        }
    }

    Vertex *vertex = vertexAt(0);
    vertex->setX(-halfw);
    vertex->setY(-halfh);
    vertex->setTex(QVector2D(0, 1));
    vertex->setColor(Qt::white);

    vertex = vertexAt(1);
    vertex->setX(-halfw);
    vertex->setY(halfh);
    vertex->setTex(QVector2D(0, 0));
    vertex->setColor(Qt::white);

    vertex = vertexAt(2);
    vertex->setX(halfw);
    vertex->setY(halfh);
    vertex->setTex(QVector2D(1, 0));
    vertex->setColor(Qt::white);

    vertex = vertexAt(3);
    vertex->setX(halfw);
    vertex->setY(-halfh);
    vertex->setTex(QVector2D(1, 1));
    vertex->setColor(Qt::white);
}

QSizeF GluonGraphics::SpriteMesh::size() const
{
    return d->size;
}

