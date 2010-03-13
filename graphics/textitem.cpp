#include "textitem.h"
#include "meshes/polygonmesh.h"
#include "meshes/spritemesh.h"
#include <QFontMetrics>
#include <cmath>
namespace GluonGraphics
{
    TextItem::TextItem(const QString& txt,const QFont& fnt,QObject *parent)
        :Item(parent)
    {

        mText=txt;
        mFont=fnt;
        initTexture();

    }

    bool TextItem::initTexture()
    {

        mesh()->clear();

        QFontMetrics metrics(mFont);
        int texwidth = metrics.width(mText);
        int texheight= metrics.height();


        QImage image( texwidth, texheight, QImage::Format_RGB32 );
        QPainter painter;
        // start painting the image
        painter.begin( &image );
        painter.setFont( mFont);
        painter.setRenderHint( QPainter::TextAntialiasing );
        painter.setBackground( Qt::black);
        painter.eraseRect( image.rect() );
        //    // use an artificial blue color. This image is only used internally anyway.
        painter.setPen( Qt::white );
        painter.drawText(image.rect(),Qt::AlignCenter,mText);
        painter.end();

//        ////     int x=1;
//        ////     while ( w
//        //    image = image.scaled(64,16);
//        //    texwidth = image.width();
//        //    texheight = image.height();
//
//        int w = pow(2,static_cast<int>(log(image.width())/log(2))+1); //change if it's not 2^n
//        //   int h = pow(2,static_cast<int>(log(image.height())/log(2))+1);
//
//        image = image.scaled(w,16);
//        texwidth = image.width();
//        texheight = image.height();
//
//
//        GLubyte *bitmap = new GLubyte[ texwidth * texheight ];
//        if( bitmap == 0 ) return false;
//
//        for( int j = texheight - 1, n = 0; j >= 0; j-- )
//            for( int i = 0; i < texwidth; i++, n++ )
//            {
//            bitmap[n] = qBlue( image.pixel( i, j ) );
//        }
//
//        GLuint text;
//        glGenTextures( 1, &text );
//        if( text== 0 ) return false;
//
//
//
//
//        glBindTexture( GL_TEXTURE_2D, text);
//        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
//        glTexImage2D(
//                GL_TEXTURE_2D,
//                0,
//                GL_ALPHA,
//                texwidth,
//                texheight,
//                0,
//                GL_ALPHA,
//                GL_UNSIGNED_BYTE,
//                bitmap );
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        delete [] bitmap;
//
      int ratio = texwidth/texheight;
//        float rp = (float)texheight/2/10;
//
//        qDebug()<<"ratio"<<ratio*rp<<rp;

        PolygonMesh * rect = new PolygonMesh(QRectF(0,0,1,ratio));
        setMesh(rect);



        setTexture(image);
        return true;

    }
    void TextItem::setText(const QString& txt)
    {
        mText = txt;
        initTexture();
    }
    void TextItem::setFont(const QFont& fnt)
    {
        mFont = fnt;
        initTexture();
    }
    const QString& TextItem::text()
    {
        return mText;

    }
    const QFont& TextItem::font()
    {
        return mFont;

    }
}
