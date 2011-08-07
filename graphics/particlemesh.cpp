/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include "particlemesh.h"
#include "vertexattribute.h"
#include "glheaders.h"

#include <QVector3D>
#include <QQuaternion>
#include <QColor>

#define PI 3.1415927

using namespace GluonGraphics;

struct Particle
{
    Particle(const QVector3D& pos, const QVector3D& vel)
    {
        position = pos;
        velocity = vel;
        age = 0;
        color = Qt::white;
    }

    QVector3D position;
    QVector3D velocity;
    QColor color;
    int age;
};

class ParticleMesh::Private
{
    public:
        QList<Particle*> particles;
        int counter;
};

ParticleMesh::ParticleMesh( QObject* parent )
    : AbstractMesh( parent ), d( new Private )
{
    glEnable(GL_POINT_SPRITE);
    glPointSize(8.f);
    d->counter = 0;
}

ParticleMesh::~ParticleMesh()
{

}

void ParticleMesh::initialize()
{
    VertexBuffer* buffer = vertexBuffer();
    buffer->setBufferDataMode(VertexBuffer::BM_DYNAMIC_DRAW);

    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.00f,  1.00f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.38f,  0.92f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.71f,  0.71f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.92f,  0.38f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  1.00f,  0.00f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.92f, -0.38f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.71f, -0.71f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.38f, -0.92f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.00f, -1.00f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -0.38f, -0.92f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -0.71f, -0.71f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -0.92f, -0.38f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -1.00f,  0.00f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -0.92f,  0.38f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -0.71f,  0.71f, 0 ) * 2.f );
    d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -0.38f,  0.92f, 0 ) * 2.f );

    VertexAttribute vertexAttrib( "vertex", 3 );
    foreach( Particle* particle, d->particles )
    {
        vertexAttrib << particle->position.x() << particle->position.y() << particle->position.z();
    }
    buffer->addAttribute(vertexAttrib);

    VertexAttribute ageAttrib( "age", 1 );
    for(int i = 0; i < d->particles.size(); ++i)
    {
        ageAttrib << 0.0f;
    }
    buffer->addAttribute(ageAttrib);

    QVector<uint> indices;
    indices << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    buffer->setIndices(indices);

    buffer->initialize();
}

void ParticleMesh::update()
{
    d->counter++;
    if(d->counter > 0)
    {
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.00f,  1.00f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.38f,  0.92f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.71f,  0.71f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.92f,  0.38f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  1.00f,  0.00f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.92f, -0.38f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.71f, -0.71f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.38f, -0.92f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D(  0.00f, -1.00f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -0.38f, -0.92f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -0.71f, -0.71f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -0.92f, -0.38f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -1.00f,  0.00f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -0.92f,  0.38f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -0.71f,  0.71f, 0 ) * 2.f );
        d->particles << new Particle( QVector3D( 0, 0, 0 ), QVector3D( -0.38f,  0.92f, 0 ) * 2.f );
        d->counter = 0;

        QVector<uint> indices;
        for(int i = d->particles.size() - 1; i >= 0; --i)
        {
            indices << i;
        }
        vertexBuffer()->setIndices(indices);
    }

    VertexAttribute& vertexAttrib = vertexBuffer()->attributeRef("vertex");
    vertexAttrib.clear();

    VertexAttribute& ageAttrib = vertexBuffer()->attributeRef("age");
    ageAttrib.clear();

    QQuaternion q = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), 2*3.1415927);

    foreach( Particle* particle, d->particles )
    {
        particle->velocity = q.rotatedVector(particle->velocity);
        particle->position +=  particle->velocity;
        vertexAttrib << particle->position.x() << particle->position.y() << particle->position.z();

        particle->age++;
        ageAttrib << particle->age / 50.f;
        if(particle->age > 50)
        {
            d->particles.removeOne(particle);
            delete particle;
        }
    }

    vertexBuffer()->update();
}

void ParticleMesh::render(GluonGraphics::MaterialInstance* material, GluonGraphics::VertexBuffer::RenderMode mode)
{
    vertexBuffer()->render(VertexBuffer::RM_POINTS, material);
}

