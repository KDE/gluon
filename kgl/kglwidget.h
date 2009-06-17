/*
 * This file is part of the KGLWidget project.
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KGLWIDGET_H
#define KGLWIDGET_H
#include <KDebug>
#include <QStandardItemModel>
#include <QMap>
#include <GL/glew.h>

#include <QtOpenGL/QGLWidget>
#include <QtCore/QTimer>
#include <Eigen/Geometry>



#include "kglitembase.h"
#include "kglitemlist.h"
#include "kglitem.h"
#include "kglboxitem.h"
#include "kgltextitem.h"


typedef QMap<unsigned int, KGLItemList > IndexGroupMap;


class KGLWidget: public QGLWidget
{
    Q_OBJECT
public:
    
    explicit KGLWidget( QSize size, float frameRate ,QWidget* parent = 0);
    explicit KGLWidget(QWidget * parent=0);
    virtual ~KGLWidget();

    bool initGlew();
    bool isExtensionSupported(QString name){return glewIsSupported(name.toUtf8());}


    inline QPointF mapToGL(const QPointF &p) {
        return QPointF((m_orthoView.width() / 2 * p.x() * 2 / QGLWidget::width()) - m_orthoView.width() / 2, m_orthoView.height() / 2 - p.y() * m_orthoView.height() / QGLWidget::height());
    }
    inline QPointF mapFromGL(const QPointF &p) {
        return QPointF((p.x() + m_orthoView.width() / 2) * QGLWidget::width() / (m_orthoView.width()), (m_orthoView.height() / 2 - p.y()) * (QGLWidget::height() / m_orthoView.height()));
    }

    KGLItemList itemList();
public Q_SLOTS:
    
    void addItem(KGLItem* item);
    void addItems(const KGLItemList* items);
    bool removeItem(KGLItem* item);
    bool removeItems(const KGLItemList *item);
    bool eraseItem(KGLItem* item);
    bool eraseItems(const KGLItemList *item);
    KGLItem * itemAt(int id, unsigned int layer=0);
    int itemsCount() const;
    KGLBoxItem * addBox(float w, float h){KGLBoxItem * b = new KGLBoxItem(w,h); addItem(b); return b;}
    KGLTextItem *addText(float x, float y,const QString& text){
        KGLTextItem * t = new KGLTextItem(text,this);
        t->setPosition(x,y);
        t->updateTransform();
        addItem(t);
        return t;
    }

    
    inline void startGame() {
        m_timer->start(m_frameRate);
        m_fpsTimer->start(1000);
    }
    inline void pauseGame() {
        m_timer->stop();
        m_fpsTimer->stop();
    }
    inline void setFrameRate(int f)
    {
        m_frameRate=f;
        pauseGame();
        startGame();
    }
    inline void startPause() {
        if (m_timer->isActive()) {
            pauseGame();
        } else {
            startGame();
        }
    }
    inline void setShowFps(bool b) {
        m_hasFps = b;
    }
    inline bool showFps() {
        return m_hasFps;
    }
    inline float fps(){return m_fps;}
    inline void setShowAxis(bool b){m_hasAxis=b;}
    inline bool showAxis() {
        return m_hasAxis;
    }
    inline int countFrame() {
        return m_countFrame;
    }

    inline void setOrthoView(QRectF &rect) {
        m_orthoView = rect;
        resizeGL(width(), height());
    }
    
    inline void setOrthoView(const float& left,const float& right,const float& bottom,const float& top)
    {
        m_orthoView.setLeft(left);
        m_orthoView.setRight(right);
        m_orthoView.setBottom(bottom);
        m_orthoView.setTop(top);
        resizeGL(width(),height());
    }
    
    inline QRectF orthoView() const {
        return m_orthoView;
    }
    inline float ratio() const {
        return m_ratio;
    }
    void kglDebug(QString txt);
    QStandardItemModel * getStandardItemModel();
protected slots:
    
    virtual void mainLoop();
    inline void calculFps() {
        m_fps = m_countFrame;
        m_countFrame = 0;
    }
    
protected:
    void initalize();
    void initializeGL();
    void resizeGL(int w, int h);
    virtual void paintGL();
    void drawGLItems() const;
    void drawRepere(float scalex, float scaley) ;
    inline void drawCross(const QPointF &pos) {
        drawCross(pos.x(), pos.y());
    }
    
    void drawCross(float x, float y);
    void drawGLPoint(GLPoint* p);
    void drawPolygon(const QPolygonF &polygon);
    void drawRectangle(const QRectF &rect);
private:
    

    IndexGroupMap m_items;
    QRectF m_orthoView;
    
    bool  m_sleep;
    float m_countFrame;
    float m_fps;
    float m_frameRate;
    float m_ratio;
    QTimer* m_timer;
    QTimer* m_fpsTimer;
    bool m_hasAxis;
    bool m_hasFps;
    QStringList m_debugList;
//    GLint ctx;

};

#endif //KGLWidget_H
