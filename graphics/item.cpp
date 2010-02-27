#include "item.h"
#include "engine.h"
#include <QDebug>
namespace GluonGraphics
{


    Item::Item(QObject * parent)
        :Transform(parent)
    {
        m_mesh = new Mesh;
        init();
    }

    //------------------------------------------------------------
    Item::Item(Mesh * mesh , QObject * parent)
        :Transform(parent)
    {
        m_mesh = mesh;
        init();
    }
    //------------------------------------------------------------

    void Item::init()
    {
        Engine::instance()->addItem(this);
        setObjectName(metaObject()->className());

        m_texture = new Texture();
        m_color = Qt::white;
        m_alpha = 1;
        m_gl_mode = GL_POLYGON;
    }
    //------------------------------------------------------------

    void  Item::paintGL()
    {
        glPushMatrix();
        glMultMatrixd((GLdouble*)(matrix().data()));


        m_texture->bind();
        drawMesh();
        m_texture->unBind();



        glPopMatrix();
    }
    //------------------------------------------------------------
    void Item::drawMesh()
    {

        glPolygonMode(GL_FRONT_AND_BACK,m_gl_mode);


        /*enable client state */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        /* send data */
        glVertexPointer(3, GL_FLOAT,sizeof(Vertex),m_mesh->vertexArray());
        glTexCoordPointer(2,GL_FLOAT,sizeof(Vertex),m_mesh->texCoordsArray());
        glColorPointer(4, GL_FLOAT,sizeof(Vertex),m_mesh->colorArray());

        //    /* create vertex */
        glDrawArrays(m_gl_mode, 0, m_mesh->vertexCount());

        /* disable client state */
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);


    }
    //------------------------------------------------------------

    void Item::setColor(const QColor& col)
    {
        QVector <Vertex> * vertexes = m_mesh->vertexes();
        for ( int i=0; i<vertexes->size(); ++i)
            (*vertexes)[i].setColor(col);
        m_color = col;

    }
    //------------------------------------------------------------
    void Item::setAlpha(const float& alpha)
    {

        QVector <Vertex> * vertexes = m_mesh->vertexes();
        for ( int i=0; i<vertexes->size(); ++i)
            (*vertexes)[i].setAlpha(alpha);

        m_alpha = alpha;

    }
    //------------------------------------------------------------
    const QColor& Item::color()
    {
        return m_color;
    }
    //------------------------------------------------------------
    const float& Item::alpha()
    {
        return m_alpha;
    }
    //------------------------------------------------------------
    void Item::setTexture(Texture * texture)
    {
        m_texture = texture;
    }
    //------------------------------------------------------------
    void Item::setTexture(const QPixmap& pix)
    {
        m_texture= new Texture(pix);
    }
    //------------------------------------------------------------
    void Item::setTexture(const QImage& img)
    {
        m_texture= new Texture(img);
    }
    //------------------------------------------------------------
    void Item::setTexture(const QString& path)
    {
        m_texture =new Texture(path);
    }
    //------------------------------------------------------------

}
