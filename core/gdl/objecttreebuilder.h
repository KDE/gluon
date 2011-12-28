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



#ifndef GDL_OBJECTTREEBUILDER_H
#define GDL_OBJECTTREEBUILDER_H

#include <core/gdl/gdldefaultvisitor.h>

#include <QtCore/QScopedPointer>

namespace GluonCore
{
    class GluonObject;
}

namespace GDL
{
    class Lexer;
    class Parser;

    /**
     * \brief Create a tree of objects from a GDL AST
     *
     * This class is a visitor for a GDL AST that will create
     * objects and set the properties of those objects based on
     * the information in the AST.
     */
    class ObjectTreeBuilder : public DefaultVisitor
    {
        public:
            /**
             * Constructor.
             *
             * \param lexer The lexer that was used to create the AST.
             */
            ObjectTreeBuilder( GDL::Lexer* lexer, const QString& content, GluonCore::GluonObject* project = 0, GluonCore::GluonObject* parent = 0 );
            virtual ~ObjectTreeBuilder();

            QList<GluonCore::GluonObject*> objects();

            virtual void visitStart( StartAst* node );
            virtual void visitObject( ObjectAst* node );
            virtual void visitList_type( List_typeAst* node );
            virtual void visitBoolean_type( Boolean_typeAst* node );
            virtual void visitFloat_type( Float_typeAst* node );
            virtual void visitInteger_type( Integer_typeAst* node );
            virtual void visitProperty( PropertyAst* node );
            virtual void visitProperty_type( Property_typeAst* node );
            virtual void visitLong_long_type( Long_long_typeAst* node );
            virtual void visitObject_type( Object_typeAst* node );
            virtual void visitQuaternion_type( Quaternion_typeAst* node );
            virtual void visitRgba_type( Rgba_typeAst* node );
            virtual void visitSize2d_type( Size2d_typeAst* node );
            virtual void visitString_type( String_typeAst* node );
            virtual void visitUnsigned_int_type( Unsigned_int_typeAst* node );
            virtual void visitVector2d_type( Vector2d_typeAst* node );
            virtual void visitUrl_type( Url_typeAst* node );
            virtual void visitVector3d_type( Vector3d_typeAst* node );
            virtual void visitVector4d_type( Vector4d_typeAst* node );

        private:
            class Private;
            const QScopedPointer<Private> d;
    };

}

#endif // OBJECTTREEBUILDER_H
