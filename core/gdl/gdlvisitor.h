// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GDL_VISITOR_H_INCLUDED
#define GDL_VISITOR_H_INCLUDED

#include "gdlast.h"

namespace GDL
{

    class  Visitor
    {
        public:
            virtual ~Visitor() {}
            virtual void visitNode( AstNode* node );
            virtual void visitBoolean_type( Boolean_typeAst* ) {}
            virtual void visitFloat_type( Float_typeAst* ) {}
            virtual void visitInteger_type( Integer_typeAst* ) {}
            virtual void visitList_type( List_typeAst* ) {}
            virtual void visitLong_long_type( Long_long_typeAst* ) {}
            virtual void visitObject( ObjectAst* ) {}
            virtual void visitObject_type( Object_typeAst* ) {}
            virtual void visitProperty( PropertyAst* ) {}
            virtual void visitQuaternion_type( Quaternion_typeAst* ) {}
            virtual void visitRgba_type( Rgba_typeAst* ) {}
            virtual void visitSize2d_type( Size2d_typeAst* ) {}
            virtual void visitStart( StartAst* ) {}
            virtual void visitString_type( String_typeAst* ) {}
            virtual void visitUnsigned_int_type( Unsigned_int_typeAst* ) {}
            virtual void visitUrl_type( Url_typeAst* ) {}
            virtual void visitVector2d_type( Vector2d_typeAst* ) {}
            virtual void visitVector3d_type( Vector3d_typeAst* ) {}
            virtual void visitVector4d_type( Vector4d_typeAst* ) {}
    };

} // end of namespace GDL

#endif

