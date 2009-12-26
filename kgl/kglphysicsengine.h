/*
 * This file is part of the Gluon library.
 * Copyright 2009 Gluon team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KGLPHYSICSENGINE_H
#define KGLPHYSICSENGINE_H

#include "kgl_export.h"
#include "kglengine.h"

#include <QtCore/QList>

/**
 * \defgroup KGL KGL
 */
//@{

class KGLPhysicsEnginePrivate;
class KGLPhysicsItem;
class b2World;

class KGL_EXPORT KGLPhysicsEngine : public KGLEngine
{
    Q_OBJECT
public:
    KGLPhysicsEngine(QObject * parent=0);
    ~KGLPhysicsEngine();

    void computeSimulation(int iterations = 10, float fps=60);
    void addItem(KGLPhysicsItem *  item);
    void addItem(KGLItem* item);
    bool removeItem(KGLPhysicsItem * item);
    bool removeItem(KGLItem * item);
    void createWorld(const QPointF &gravity = QPointF(0.0f,-10.0f), bool sleep = true);
    b2World *world() const;

    QList<KGLPhysicsItem*> physicsItems() const;
    
    KGLPhysicsItem* itemAt(const QPointF &pos) const;

public slots:
    void clearPhysicsItems();

protected:
    virtual void mainLoop(float fps);

private:
    Q_DISABLE_COPY(KGLPhysicsEngine)
    KGLPhysicsEnginePrivate *d;
};

//@}
#endif // KGLPHYSICSENGINE_H
