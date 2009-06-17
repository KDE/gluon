#ifndef KGLITEM2_H
#define KGLITEM2_H
#include <GL/glew.h>


#include "kglitembase.h"
#include "kgltexture.h"
#include "kglprogram.h"
class KGLWidget;
class KGLItem : public KGLItemBase
{
public:
    virtual void draw();
    explicit KGLItem(KGLWidget * parent=0);
    explicit KGLItem(const QPolygonF &poly, QObject * parent=0);
    explicit KGLItem(const QSizeF &box, QObject * parent=0);
    explicit KGLItem(const QLineF &line,QObject * parent=0);
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
    void setProgram(KGLProgram * p){m_program = p ;}
    KGLTexture * texture(){return m_texture;}
    KGLProgram * program(){return m_program;}


    //get
    const QColor &color(){return m_color;}
    const float &alpha(){return m_alpha;}
protected:

    virtual void create();
    void init();
    virtual void drawGLPoint(GLPoint *p);
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
    KGLProgram * m_program;

    //flags.....
    bool f_showBoundingBox;
    bool f_showCenter;
    bool f_textureEnable;




};






#endif // KGLITEM2_H
