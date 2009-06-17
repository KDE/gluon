#ifndef KGLTEXTURE_H
#define KGLTEXTURE_H
#include <GL/glew.h>
#include <QPixmap>
#include <QImage>
class KGLTexture
{
public:
    KGLTexture();
    KGLTexture (const QString& fileName);
    KGLTexture ( const QImage &img);
    KGLTexture(const QPixmap &pix);
    void setGLTexture(const GLuint& t){m_texture = t;}
    ~KGLTexture();
    void bind();
    void unBind();
    void load(const QImage &img, int width=0, int height=0);
    GLuint gltexture(){return m_texture;}
    QImage getQImage(){return m_img;}
    QSizeF dim(){return m_dim;}
    void setTranslate(QPointF t){m_translate = t;}
    void setRotate(float r){m_rotate= r;}
    void setScale(QPointF s){m_scale = s;}
    void translate(QPointF t){m_translate += t;}
    void rotate(float r){m_rotate += r;}
    void scale(QPointF s){m_scale+=s;}
    void updateTransform();

protected:
    void init();
private:
    GLuint m_texture;
    QSizeF m_dim;
    QImage m_img;
    QPointF m_translate;
    float m_rotate;
    QPointF m_scale;
};

#endif // KGLTEXTURE_H
