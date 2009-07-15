#ifndef KGLITEM2_H
#define KGLITEM2_H
#include <GL/glew.h>


#include "kglbaseitem.h"
#include "kgltexture.h"
#include "kglfx.h"

class KGLEngine;
class KGLItem;
class KGLItem : public KGLBaseItem
{
    Q_OBJECT
public:
    virtual void draw();
    virtual void updateTransform();
    explicit KGLItem(KGLEngine * parent=0);
    explicit KGLItem(const QPolygonF &poly, KGLEngine * parent=0);
    explicit KGLItem(const QSizeF &box, KGLEngine * parent=0);
    explicit KGLItem(const QLineF &line,KGLEngine * parent=0);
    KGLItem *clone();
    void addChildItem(KGLItem* item){m_childItems.append(item);}
    void remChildItem(KGLItem * item){m_childItems.removeOne(item);}
    ~KGLItem();


    //set
    void setMode(GLenum m){m_mode=m;}
    void setTexture(const GLuint& t){m_texture->setGLTexture(t);}
    void setTexture( KGLTexture *t){m_texture = t;}
    void setTexture(const QString& fileName){m_texture = new KGLTexture(fileName);}
    void setTexture(const QImage& image) {m_texture = new KGLTexture(image);}
    void setTexture(const QPixmap &pix){m_texture = new KGLTexture(pix);}
    void setColor(const QColor &c);
    void setAlpha(const float &a);
    void showBoundingBox(bool b){f_showBoundingBox = b; m_isCreated=false;}
    void showCenter(bool b){f_showCenter = b;m_isCreated=false;}
    void setTextureEnable(bool t){f_textureEnable = t;}

    KGLTexture * texture(){return m_texture;}




    //get
    const QColor &color(){return m_color;}
    const float &alpha(){return m_alpha;}
    QList<KGLItem*> childItems(){return m_childItems;}

    KGLBlurFx * blurFx(){return m_blurFx;}
    KGLPixelateFx *pixelateFx(){return m_pixelateFx;}
    KGLLightFx * m_lightFx;

signals:
    void painted();

protected:

    virtual void create();
    void drawChild();
    void init();
    virtual void drawGLPoint(KGLPoint &p);
    virtual void drawBoundingBox();
    virtual void drawCenter();


private:
    int m_GLCallList;
    bool m_isCreated;
    QPointF m_texRepeat;
    QColor m_color;
    float m_alpha;
    GLenum m_mode;
    KGLTexture *m_texture;
    QList<KGLItem*> m_childItems;


    //flags.....
    bool f_showBoundingBox;
    bool f_showCenter;
    bool f_textureEnable;

    //fx
    KGLBlurFx * m_blurFx;
    KGLPixelateFx * m_pixelateFx;

};






#endif // KGLITEM2_H
