#ifndef ITEM2_H
#define ITEM2_H
#include "transform.h"
#include "mesh.h"
#include "glpainter.h"
#include "texture.h"
#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT Item2 : public Transform
    {
          class Engine;
    public:
        Item2(Mesh * mesh, QObject* parent=0);
        virtual void paintGL();
    protected:
        void init();

    private:
        Mesh * m_mesh;
        GLPainter * m_painter;
        Texture * m_texture;
    };

}
#endif // ITEM2_H
