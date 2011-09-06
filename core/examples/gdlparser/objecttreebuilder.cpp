/*************************************************************************
 * This file is part of the Gluon Development Platform
 *
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */



#include "objecttreebuilder.h"

#include <core/gluonobject.h>
#include <core/gluonobjectfactory.h>

#include <core/gdl/gdllexer.h>
#include <core/gdl/gdlparser.h>

#include <QtCore/QSizeF>
#include <QtGui/QColor>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#include <QtGui/QQuaternion>

using namespace GDL;
using namespace GluonCore;

class ObjectTreeBuilder::Private
{
    public:
        Private() : currentObject(0) { }
        
        QString textForToken(Lexer::Token token);
        QString stripQuotes(const QString& input);
        
        Lexer* lexer;
        QString content;

        QList<GluonCore::GluonObject*> objects;
        GluonCore::GluonObject* currentObject;
        QVariant currentPropertyValue;
};

ObjectTreeBuilder::ObjectTreeBuilder(Lexer* lexer, const QString& content)
    : d(new Private)
{
    d->lexer = lexer;
    d->content = content;
}

ObjectTreeBuilder::~ObjectTreeBuilder()
{

}

QList< GluonCore::GluonObject* > ObjectTreeBuilder::objects()
{
    return d->objects;
}

void ObjectTreeBuilder::visitObject(GDL::ObjectAst* node)
{
    GluonObject* newObject = GluonObjectFactory::instance()->instantiateObjectByName(d->textForToken(d->lexer->token(node->type)));

    if(d->currentObject)
    {
        d->currentObject->addChild(newObject);
    }
    else
    {
        d->objects.append(newObject);
    }

    GluonObject* parent = d->currentObject;
    d->currentObject = newObject;
    
    GDL::DefaultVisitor::visitObject(node);

    d->currentObject = parent;
}

void ObjectTreeBuilder::visitProperty(GDL::PropertyAst* node)
{
    if(!d->currentObject)
    {
        qFatal("Cannot set properties on non-existing object");
        return;
    }
    
    GDL::DefaultVisitor::visitProperty(node);

    QString propertyName = d->textForToken(d->lexer->token(node->propertyName));

    d->currentObject->setProperty(propertyName.toUtf8(), d->currentPropertyValue);
}

void ObjectTreeBuilder::visitBoolean_type(GDL::Boolean_typeAst* node)
{
    Lexer::Token boolToken = d->lexer->token(node->value);
    d->currentPropertyValue = QVariant::fromValue<bool>(boolToken.kind == Parser::Token_TRUE_VALUE);
}

void ObjectTreeBuilder::visitInteger_type(GDL::Integer_typeAst* node)
{
    Lexer::Token intToken = d->lexer->token(node->value);
    d->currentPropertyValue = QVariant::fromValue<int>(d->textForToken(intToken).toInt());
}

void ObjectTreeBuilder::visitUnsigned_int_type(GDL::Unsigned_int_typeAst* node)
{
    Lexer::Token uintToken = d->lexer->token(node->value);
    d->currentPropertyValue = QVariant::fromValue<uint>(d->textForToken(uintToken).toUInt());
}

void ObjectTreeBuilder::visitLong_long_type(GDL::Long_long_typeAst* node)
{
    Lexer::Token longToken = d->lexer->token(node->value);
    d->currentPropertyValue = QVariant::fromValue<qlonglong>(d->textForToken(longToken).toLongLong());
}

void ObjectTreeBuilder::visitFloat_type(GDL::Float_typeAst* node)
{
    Lexer::Token floatToken = d->lexer->token(node->value);
    d->currentPropertyValue = QVariant::fromValue<float>(d->textForToken(floatToken).toFloat());
}

void ObjectTreeBuilder::visitString_type(GDL::String_typeAst* node)
{
    Lexer::Token stringToken = d->lexer->token(node->value);
    d->currentPropertyValue = QVariant::fromValue<QString>(d->textForToken(stringToken));
}

void ObjectTreeBuilder::visitUrl_type(GDL::Url_typeAst* node)
{
    Lexer::Token urlToken = d->lexer->token(node->path);
    d->currentPropertyValue = QVariant::fromValue<QUrl>(QUrl(d->textForToken(urlToken)));
}

void ObjectTreeBuilder::visitRgba_type(GDL::Rgba_typeAst* node)
{
    QColor color;
    Lexer::Token token = d->lexer->token(node->r);
    color.setRed(d->textForToken(token).toInt());
    token = d->lexer->token(node->g);
    color.setGreen(d->textForToken(token).toInt());
    token = d->lexer->token(node->b);
    color.setBlue(d->textForToken(token).toInt());
    token = d->lexer->token(node->a);
    color.setAlpha(d->textForToken(token).toInt());

    d->currentPropertyValue = QVariant::fromValue<QColor>(color);
}

void ObjectTreeBuilder::visitVector2d_type(GDL::Vector2d_typeAst* node)
{
    QVector2D vector;
    GDL::Lexer::Token token = d->lexer->token(node->x);
    vector.setX(d->textForToken(token).toFloat());
    token = d->lexer->token(node->y);
    vector.setY(d->textForToken(token).toFloat());

    d->currentPropertyValue = QVariant::fromValue<QVector2D>(vector);
}

void ObjectTreeBuilder::visitVector3d_type(GDL::Vector3d_typeAst* node)
{
    QVector3D vector;
    GDL::Lexer::Token token = d->lexer->token(node->x);
    vector.setX(d->textForToken(token).toFloat());
    token = d->lexer->token(node->y);
    vector.setY(d->textForToken(token).toFloat());
    token = d->lexer->token(node->z);
    vector.setZ(d->textForToken(token).toFloat());

    d->currentPropertyValue = QVariant::fromValue<QVector3D>(vector);
}

void ObjectTreeBuilder::visitVector4d_type(GDL::Vector4d_typeAst* node)
{
    QVector4D vector;
    GDL::Lexer::Token token = d->lexer->token(node->x);
    vector.setX(d->textForToken(token).toFloat());
    token = d->lexer->token(node->y);
    vector.setY(d->textForToken(token).toFloat());
    token = d->lexer->token(node->z);
    vector.setZ(d->textForToken(token).toFloat());
    token = d->lexer->token(node->w);
    vector.setW(d->textForToken(token).toFloat());

    d->currentPropertyValue = QVariant::fromValue<QVector4D>(vector);
}

void ObjectTreeBuilder::visitQuaternion_type(GDL::Quaternion_typeAst* node)
{
    QQuaternion quat;
    GDL::Lexer::Token token = d->lexer->token(node->x);
    quat.setX(d->textForToken(token).toFloat());
    token = d->lexer->token(node->y);
    quat.setY(d->textForToken(token).toFloat());
    token = d->lexer->token(node->z);
    quat.setZ(d->textForToken(token).toFloat());
    token = d->lexer->token(node->w);
    quat.setScalar(d->textForToken(token).toFloat());

    d->currentPropertyValue = QVariant::fromValue<QQuaternion>(quat);
}

void ObjectTreeBuilder::visitSize2d_type(GDL::Size2d_typeAst* node)
{
    QSizeF size;
    GDL::Lexer::Token token = d->lexer->token(node->width);
    size.setWidth(d->textForToken(token).toFloat());
    token = d->lexer->token(node->height);
    size.setHeight(d->textForToken(token).toFloat());

    d->currentPropertyValue = QVariant::fromValue<QSizeF>(size);
}

void ObjectTreeBuilder::visitObject_type(GDL::Object_typeAst* node)
{
    
}

void ObjectTreeBuilder::visitList_type(GDL::List_typeAst* node)
{

}

QString ObjectTreeBuilder::Private::textForToken(KDevPG::Token token)
{
    return content.mid(token.begin, token.end - token.begin + 1);
}

QString ObjectTreeBuilder::Private::stripQuotes(const QString& input)
{
    QString retval = input;
    if(retval.at(0) == '"')
        retval = retval.remove(0, 1);
    if(retval.at(retval.size() - 1) == '"')
        retval = retval.remove(retval.size() - 1, 1);
    return retval;
}


