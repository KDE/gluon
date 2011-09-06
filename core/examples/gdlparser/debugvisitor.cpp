#include "debugvisitor.h"

#include <QtCore/QDebug>
#include <gdllexer.h>
#include <gdlparser.h>
#include <QColor>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QSizeF>

char const * const DebugVisitor::names[] = {
    "Object",
    "Object List",
    "Property",
    "Start"
};

DebugVisitor::DebugVisitor(GDL::Lexer* lexer, const QString& content)
{
    m_content = content;
    m_lexer = lexer;
}

void DebugVisitor::visitNode(GDL::AstNode* node)
{
    GDL::Visitor::visitNode(node);
}

void DebugVisitor::visitObject(GDL::ObjectAst* node)
{
    GDL::Lexer::Token nameToken = m_lexer->token(node->name);
    GDL::Lexer::Token typeToken = m_lexer->token(node->type);
    
    QString name = m_content.mid(nameToken.begin + 1, nameToken.end - nameToken.begin - 1);
    QString type = m_content.mid(typeToken.begin, typeToken.end - typeToken.begin + 1);
    
    qDebug() << QString("%1Object %2 of type %3").arg(m_indent, name, type);
    
    m_indent = m_indent + "    ";
    GDL::DefaultVisitor::visitObject(node);
    m_indent = m_indent.left(m_indent.size() - 4);
}

void DebugVisitor::visitProperty(GDL::PropertyAst* node)
{
    GDL::Lexer::Token propertyToken = m_lexer->token(node->propertyName);
    
    QString property = m_content.mid(propertyToken.begin, propertyToken.end - propertyToken.begin + 1);

    qDebug() << QString("%1Property %2").arg(m_indent, property);

    m_indent = m_indent + "    ";
    GDL::DefaultVisitor::visitProperty(node);
    m_indent = m_indent.left(m_indent.size() - 4);
}

void DebugVisitor::visitBoolean_type(GDL::Boolean_typeAst* node)
{
    GDL::Lexer::Token boolToken = m_lexer->token(node->value);
    qDebug() << QString("%1Boolean: %2").arg(m_indent).arg(boolToken.kind == GDL::Parser::Token_TRUE_VALUE ? "True" : "False");
}

void DebugVisitor::visitInteger_type(GDL::Integer_typeAst* node)
{
    GDL::Lexer::Token intValue = m_lexer->token(node->value);
    qDebug() << QString("%1Integer: %2").arg(m_indent).arg(textForToken(intValue).toInt());
}

void DebugVisitor::visitFloat_type(GDL::Float_typeAst* node)
{
    GDL::Lexer::Token floatValue = m_lexer->token(node->value);
    qDebug() << QString("%1Float: %2").arg(m_indent).arg(textForToken(floatValue).toFloat());
}

void DebugVisitor::visitUnsigned_int_type(GDL::Unsigned_int_typeAst* node)
{
    GDL::Lexer::Token uintValue = m_lexer->token(node->value);
    qDebug() << QString("%1Unsigned Int: %2").arg(m_indent).arg(textForToken(uintValue).toUInt());
}

void DebugVisitor::visitLong_long_type(GDL::Long_long_typeAst* node)
{
    GDL::Lexer::Token longValue = m_lexer->token(node->value);
    qDebug() << QString("%1Long long: %2").arg(m_indent).arg(textForToken(longValue).toLongLong());
}

void DebugVisitor::visitString_type(GDL::String_typeAst* node)
{
    GDL::Lexer::Token stringValue = m_lexer->token(node->value);
    qDebug() << QString("%1String: %2").arg(m_indent, stripQuotes(textForToken(stringValue)));
}

void DebugVisitor::visitUrl_type(GDL::Url_typeAst* node)
{
    GDL::Lexer::Token urlValue = m_lexer->token(node->path);
    qDebug() << QString("%1URL: %2").arg(m_indent, stripQuotes(textForToken(urlValue)));
}

void DebugVisitor::visitRgba_type(GDL::Rgba_typeAst* node)
{
    QColor color;
    GDL::Lexer::Token token = m_lexer->token(node->r);
    color.setRed(textForToken(token).toInt());
    token = m_lexer->token(node->g);
    color.setGreen(textForToken(token).toInt());
    token = m_lexer->token(node->b);
    color.setBlue(textForToken(token).toInt());
    token = m_lexer->token(node->a);
    color.setAlpha(textForToken(token).toInt());

    qDebug() << QString("%1Colour:").arg(m_indent) << color;
}

void DebugVisitor::visitVector2d_type(GDL::Vector2d_typeAst* node)
{
    QVector2D vector;
    GDL::Lexer::Token token = m_lexer->token(node->x);
    vector.setX(textForToken(token).toFloat());
    token = m_lexer->token(node->y);
    vector.setY(textForToken(token).toFloat());

    qDebug() << QString("%1Vector2D:").arg(m_indent) << vector;
}

void DebugVisitor::visitVector3d_type(GDL::Vector3d_typeAst* node)
{
    QVector3D vector;
    GDL::Lexer::Token token = m_lexer->token(node->x);
    vector.setX(textForToken(token).toFloat());
    token = m_lexer->token(node->y);
    vector.setY(textForToken(token).toFloat());
    token = m_lexer->token(node->z);
    vector.setZ(textForToken(token).toFloat());

    qDebug() << QString("%1Vector3D:").arg(m_indent) << vector;
}

void DebugVisitor::visitVector4d_type(GDL::Vector4d_typeAst* node)
{
    QVector4D vector;
    GDL::Lexer::Token token = m_lexer->token(node->x);
    vector.setX(textForToken(token).toFloat());
    token = m_lexer->token(node->y);
    vector.setY(textForToken(token).toFloat());
    token = m_lexer->token(node->z);
    vector.setZ(textForToken(token).toFloat());
    token = m_lexer->token(node->w);
    vector.setW(textForToken(token).toFloat());

    qDebug() << QString("%1Vector4D:").arg(m_indent) << vector;
}

void DebugVisitor::visitQuaternion_type(GDL::Quaternion_typeAst* node)
{
    QQuaternion quat;
    GDL::Lexer::Token token = m_lexer->token(node->x);
    quat.setX(textForToken(token).toFloat());
    token = m_lexer->token(node->y);
    quat.setY(textForToken(token).toFloat());
    token = m_lexer->token(node->z);
    quat.setZ(textForToken(token).toFloat());
    token = m_lexer->token(node->w);
    quat.setScalar(textForToken(token).toFloat());

    qDebug() << QString("%1Quaternion:").arg(m_indent) << quat;
}

void DebugVisitor::visitSize2d_type(GDL::Size2d_typeAst* node)
{
    QSizeF size;
    GDL::Lexer::Token token = m_lexer->token(node->width);
    size.setWidth(textForToken(token).toFloat());
    token = m_lexer->token(node->height);
    size.setHeight(textForToken(token).toFloat());

    qDebug() << QString("%1Size2D:").arg(m_indent) << size;
}

void DebugVisitor::visitObject_type(GDL::Object_typeAst* node)
{
    GDL::Lexer::Token type = m_lexer->token(node->type);
    GDL::Lexer::Token path = m_lexer->token(node->value);

    qDebug() << QString("%1Object Reference of type %2 located at %3").arg(m_indent, textForToken(type), stripQuotes(textForToken(path)));
}

void DebugVisitor::visitList_type(GDL::List_typeAst* node)
{
    qDebug() << QString("%1List").arg(m_indent);
}

QString DebugVisitor::textForToken(KDevPG::Token token)
{
    return m_content.mid(token.begin, token.end - token.begin + 1);
}

QString DebugVisitor::stripQuotes(const QString& string)
{
    QString retval = string;
    if(retval.at(0) == '"')
        retval = retval.remove(0, 1);
    if(retval.at(retval.size() - 1) == '"')
        retval = retval.remove(retval.size() - 1, 1);
    return retval;
}


