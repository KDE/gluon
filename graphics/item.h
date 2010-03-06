#ifndef Item_H
#define Item_H
#include "transform.h"
#include "mesh.h"
#include "glpainter.h"
#include "texture.h"
#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    class Engine;
    class GLUON_GRAPHICS_EXPORT Item : public Transform
    {

    public:
        Item(QObject * parent = 0);
        Item(Mesh * mesh, QObject* parent=0);
        //Item(QSizeF size){init();}
        virtual void paintGL();
        void setColor(const QColor& col);
        void setAlpha(const float& alpha);
        void setTexture(Texture * texture);
        void setTexture(const QPixmap& pix);
        void setTexture(const QImage& img);
        void setTexture(const QString& path);
        void setMesh(Mesh * mesh)
        {
            m_mesh = mesh;
        }
        const QColor& color();
        const float& alpha();
        Mesh * mesh(){return m_mesh;}
    protected:
        void init();
        void drawMesh();

    private:
        Mesh * m_mesh;



    };

}
#endif // Item_H
