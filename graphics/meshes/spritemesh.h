#ifndef GLUON_GRAPHICS_SPRITEMESH_H
#define GLUON_GRAPHICS_SPRITEMESH_H

#include "gluon_graphics_export.h"
#include "mesh.h"

#include <QSizeF>

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT SpriteMesh: public Mesh
    {
        public:
            SpriteMesh(QObject * parent=0);
            SpriteMesh(const QSizeF& Size, QObject * parent=0);
            ~SpriteMesh();

            QSizeF size() const;

        public slots:
            void setSize(const QSizeF& size);

        private:
            class SpriteMeshPrivate;
            SpriteMeshPrivate *d;
    };
}

#endif // GLUON_GRAPHICS_SPRITEMESH_H
