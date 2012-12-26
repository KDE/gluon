/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (C) 2012 Felix Rohrbach <fxrh@gmx.de>
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

#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <QtCore/QMetaType>

#include <QVariant>
#include <qdatastream.h>
#include <qpoint.h>

#include <core/gluonvarianttypes.h>

#include <Eigen/Core>

using namespace Eigen;

static const char* const qtscript_Vector2f_function_names[] =
{
    "Vector2f"
    // static
    , "dotProduct"
    // prototype
    , "isNull"
    , "length"
    , "lengthSquared"
    , "normalize"
    , "normalized"
    , "addOther"
    , "divideBy"
    , "equals"
    , "multiplyBy"
    , "subtractOther"
    , "setX"
    , "setY"
    , "toPoint"
    , "toPointF"
    , "toVector3f"
    , "toVector4f"
    , "x"
    , "y"
    , "toString"

    , "add"
    , "subtract"
    , "multiply"
    , "divide"
    , "multiplyComponents"
};

static const char* const qtscript_Vector2f_function_signatures[] =
{
    "\nfloat pos1, float pos2"
    // static
    , "Vector2f v1, Vector2f v2" // dotProduct
    // prototype
    , "" // isNull
    , "" // length
    , "" // lengthSquared
    , "" // normalize
    , "" // normalized
    , "Vector2f vector" // addOther
    , "float divisor" // divideBy
    , "Vector2f v2" // equals
    , "Vector2f vector\nfloat factor" // multiplyBy
    , "Vector2f vector" // subtractOther
    , "float x" // setX
    , "float y" // setY
    , "" // toPoint
    , "" // toPointF
    , "" // toVector3f
    , "" // toVector4f
    , "" // x
    , "" // y
    , "" // toString

    , "Vector2f other" // add
    , "Vector2f other" // subtract
    , "float factor" // multiply
    , "float factor" // divide
    , "Vector2f other" // multiplyComponents
};

static const int qtscript_Vector2f_function_lengths[] =
{
    2
    // static
    , 2 // dotProduct
    // prototype
    , 0 // isNull
    , 0 // length
    , 0 // lengthSquared
    , 0 // normalize
    , 0 // normalized
    , 1 // addOther
    , 1 // divideBy
    , 1 // equals
    , 1 // multiplyBy
    , 1 // subtractOther
    , 1 // setX
    , 1 // setY
    , 0 // toPoint
    , 0 // toPointF
    , 0 // toVector3f
    , 0 // toVector4f
    , 0 // x
    , 0 // y
    , 0 // toString

    , 1 // add
    , 1 // subtract
    , 1 // multiply
    , 1 // divide
    , 1 // multiplyComponents
};

static QScriptValue qtscript_Vector2f_throw_ambiguity_error_helper(
    QScriptContext* context, const char* functionName, const char* signatures )
{
    QStringList lines = QString::fromLatin1( signatures ).split( QLatin1Char( '\n' ) );
    QStringList fullSignatures;
    for( int i = 0; i < lines.size(); ++i )
        fullSignatures.append( QString::fromLatin1( "%0(%1)" ).arg( functionName ).arg( lines.at( i ) ) );
    return context->throwError( QString::fromLatin1( "Vector2f::%0(): could not find a function match; candidates are:\n%1" )
                                .arg( functionName ).arg( fullSignatures.join( QLatin1String( "\n" ) ) ) );
}
// Q_DECLARE_METATYPE( QDataStream* )

static QScriptValue qtscript_Vector2f_prototype_call( QScriptContext* context, QScriptEngine* )
{
#if QT_VERSION > 0x040400
    Q_ASSERT( context->callee().isFunction() );
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if( context->callee().isFunction() )
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 24;
#endif
    Q_ASSERT( ( _id & 0xFFFF0000 ) == 0xBABE0000 );
    _id &= 0x0000FFFF;
    Vector2f* _q_self = qscriptvalue_cast<Vector2f*>( context->thisObject() );
    if( !_q_self )
    {
        return context->throwError( QScriptContext::TypeError,
                                    QString::fromLatin1( "Vector2f.%0(): this object is not a Vector2f" )
                                    .arg( qtscript_Vector2f_function_names[_id + 2] ) );
    }

    switch( _id )
    {
        case 1: // isNull
            if( context->argumentCount() == 0 )
            {
                bool _q_result = ( _q_self->x() == 0 && _q_self->y() == 0 );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;
        case 2: // length
            if( context->argumentCount() == 0 )
            {
                float _q_result = _q_self->norm();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 3: // lengthSquared
            if( context->argumentCount() == 0 )
            {
                float _q_result = _q_self->squaredNorm();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 4: // normalize
            if( context->argumentCount() == 0 )
            {
                _q_self->normalize();
                return context->engine()->undefinedValue();
            }
            break;

        case 5: // normalized
            if( context->argumentCount() == 0 )
            {
                Vector2f _q_result = _q_self->normalized();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 6: // addOther
            if( context->argumentCount() == 1 )
            {
                Vector2f _q_arg0 = qscriptvalue_cast<Vector2f>( context->argument( 0 ) );
                Vector2f _q_result = _q_self->operator+=( _q_arg0 );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 7: // divideBy
            if( context->argumentCount() == 1 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                Vector2f _q_result = _q_self->operator/=( _q_arg0 );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 8: // equals
            if( context->argumentCount() == 1 )
            {
                Vector2f _q_arg0 = qscriptvalue_cast<Vector2f>( context->argument( 0 ) );
                bool _q_result = *_q_self == _q_arg0;
                return QScriptValue( context->engine(), _q_result );
            }
            break;

        case 9: // multiplyBy
            if( context->argumentCount() == 1 )
            {
                if( ( qMetaTypeId<Vector2f>() == context->argument( 0 ).toVariant().userType() ) )
                {
                    Vector2f _q_arg0 = qscriptvalue_cast<Vector2f>( context->argument( 0 ) );
                    *_q_self = _q_self->cwiseProduct( _q_arg0 );
                    return qScriptValueFromValue( context->engine(),* _q_self );
                }
                else if( ( qMetaTypeId<float>() == context->argument( 0 ).toVariant().userType() ) )
                {
                    float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                    Vector2f _q_result = _q_self->operator*=( _q_arg0 );
                    return qScriptValueFromValue( context->engine(), _q_result );
                }
            }
            break;

        case 10: // subtractOther
            if( context->argumentCount() == 1 )
            {
                Vector2f _q_arg0 = qscriptvalue_cast<Vector2f>( context->argument( 0 ) );
                Vector2f _q_result = _q_self->operator-=( _q_arg0 );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 11: // setX
            if( context->argumentCount() == 1 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                _q_self->x() = _q_arg0;
                return context->engine()->undefinedValue();
            }
            break;

        case 12: // setY
            if( context->argumentCount() == 1 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                _q_self->y() = _q_arg0;
                return context->engine()->undefinedValue();
            }
            break;

        case 13: // toPoint
            if( context->argumentCount() == 0 )
            {
                QPoint _q_result( _q_self->x(), _q_self->y() );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 14: // toPointF
            if( context->argumentCount() == 0 )
            {
                QPointF _q_result( _q_self->x(), _q_self->y() );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 15: // toVector3D
            if( context->argumentCount() == 0 )
            {
                Vector3f _q_result( _q_self->x(), _q_self->y(), 0 );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 16: // toVector4D
            if( context->argumentCount() == 0 )
            {
                Vector4f _q_result( _q_self->x(), _q_self->y(), 0, 0 );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 17: // x
            if( context->argumentCount() == 0 )
            {
                float _q_result = _q_self->x();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 18: // y
            if( context->argumentCount() == 0 )
            {
                float _q_result = _q_self->y();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 19: // toString
        {
            QString result;
            QDebug d( &result );
            d << "Vector2f(" << _q_self->x() << _q_self->y() << ")";
            return QScriptValue( context->engine(), result );
            break;
        }

        case 20: // add
        {
            if( ( qMetaTypeId<Vector2f>() == context->argument( 0 ).toVariant().userType() ) )
            {
                Vector2f _q_arg0 = qscriptvalue_cast<Vector2f>( context->argument( 0 ) );
                Vector2f _q_result = *_q_self + _q_arg0;
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;
        }
        case 21: // subtract
        {
            if( ( qMetaTypeId<Vector2f>() == context->argument( 0 ).toVariant().userType() ) )
            {
                Vector2f _q_arg0 = qscriptvalue_cast<Vector2f>( context->argument( 0 ) );
                Vector2f _q_result = *_q_self - _q_arg0;
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;
        }
        case 22: // multiply
        {
            float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
            Vector2f _q_result = *_q_self * _q_arg0;
            return qScriptValueFromValue( context->engine(), _q_result );
            break;
        }
        case 23: // divide
        {
            float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
            Vector2f _q_result = *_q_self / _q_arg0;
            return qScriptValueFromValue( context->engine(), _q_result );
            break;
        }
        case 24: // multiplyComponents
        {
            if( ( qMetaTypeId<Vector2f>() == context->argument( 0 ).toVariant().userType() ) )
            {
                Vector2f _q_arg0 = qscriptvalue_cast<Vector2f>( context->argument( 0 ) );
                Vector2f _q_result = _q_self->cwiseProduct( _q_arg0 );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;
        }

        default:
            Q_ASSERT( false );
    }
    return qtscript_Vector2f_throw_ambiguity_error_helper( context,
            qtscript_Vector2f_function_names[_id + 2],
            qtscript_Vector2f_function_signatures[_id + 2] );
}

static QScriptValue qtscript_Vector2f_static_call( QScriptContext* context, QScriptEngine* )
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT( ( _id & 0xFFFF0000 ) == 0xBABE0000 );
    _id &= 0x0000FFFF;
    switch( _id )
    {
        case 0:
            if( context->thisObject().strictlyEquals( context->engine()->globalObject() ) )
            {
                return context->throwError( QString::fromLatin1( "Vector2f(): Did you forget to construct with 'new'?" ) );
            }
            if( context->argumentCount() == 0 )
            {
                Vector2f _q_cpp_result;
                QScriptValue _q_result = context->engine()->newVariant( context->thisObject(), qVariantFromValue( _q_cpp_result ) );
                return _q_result;
            }
            else if( context->argumentCount() == 1 )
            {
                if( ( qMetaTypeId<QPoint>() == context->argument( 0 ).toVariant().userType() ) )
                {
                    QPoint _q_arg0 = qscriptvalue_cast<QPoint>( context->argument( 0 ) );
                    Vector2f _q_cpp_result( _q_arg0.x(), _q_arg0.y() );
                    QScriptValue _q_result = context->engine()->newVariant( context->thisObject(), qVariantFromValue( _q_cpp_result ) );
                    return _q_result;
                }
                else if( ( qMetaTypeId<QPointF>() == context->argument( 0 ).toVariant().userType() ) )
                {
                    QPointF _q_arg0 = qscriptvalue_cast<QPointF>( context->argument( 0 ) );
                    Vector2f _q_cpp_result( _q_arg0.x(), _q_arg0.y() );
                    QScriptValue _q_result = context->engine()->newVariant( context->thisObject(), qVariantFromValue( _q_cpp_result ) );
                    return _q_result;
                }
                else if( ( qMetaTypeId<Vector3f>() == context->argument( 0 ).toVariant().userType() ) )
                {
                    Vector3f _q_arg0 = qscriptvalue_cast<Vector3f>( context->argument( 0 ) );
                    Vector2f _q_cpp_result( _q_arg0(1), _q_arg0(2) );
                    QScriptValue _q_result = context->engine()->newVariant( context->thisObject(), qVariantFromValue( _q_cpp_result ) );
                    return _q_result;
                }
                else if( ( qMetaTypeId<Vector4f>() == context->argument( 0 ).toVariant().userType() ) )
                {
                    Vector4f _q_arg0 = qscriptvalue_cast<Vector4f>( context->argument( 0 ) );
                    Vector2f _q_cpp_result( _q_arg0.x(), _q_arg0.y() );
                    QScriptValue _q_result = context->engine()->newVariant( context->thisObject(), qVariantFromValue( _q_cpp_result ) );
                    return _q_result;
                }
            }
            else if( context->argumentCount() == 2 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                float _q_arg1 = qscriptvalue_cast<float>( context->argument( 1 ) );
                Vector2f _q_cpp_result( _q_arg0, _q_arg1 );
                QScriptValue _q_result = context->engine()->newVariant( context->thisObject(), qVariantFromValue( _q_cpp_result ) );
                return _q_result;
            }
            break;

        case 1:
            if( context->argumentCount() == 2 )
            {
                Vector2f _q_arg0 = qscriptvalue_cast<Vector2f>( context->argument( 0 ) );
                Vector2f _q_arg1 = qscriptvalue_cast<Vector2f>( context->argument( 1 ) );
                float _q_result = _q_arg0.transpose() * _q_arg1;
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        default:
            Q_ASSERT( false );
    }
    return qtscript_Vector2f_throw_ambiguity_error_helper( context,
            qtscript_Vector2f_function_names[_id],
            qtscript_Vector2f_function_signatures[_id] );
}

QScriptValue qtscript_create_Vector2f_class( QScriptEngine* engine )
{
    engine->setDefaultPrototype( qMetaTypeId<Vector2f*>(), QScriptValue() );
    QScriptValue proto = engine->newVariant( qVariantFromValue( ( Vector2f* )0 ) );
    for( int i = 0; i < 26; ++i )
    {
        QScriptValue fun = engine->newFunction( qtscript_Vector2f_prototype_call, qtscript_Vector2f_function_lengths[i + 2] );
        fun.setData( QScriptValue( engine, uint( 0xBABE0000 + i ) ) );
        proto.setProperty( QString::fromLatin1( qtscript_Vector2f_function_names[i + 2] ),
                           fun, QScriptValue::SkipInEnumeration );
    }

    engine->setDefaultPrototype( qMetaTypeId<Vector2f>(), proto );
    engine->setDefaultPrototype( qMetaTypeId<Vector2f*>(), proto );

    QScriptValue ctor = engine->newFunction( qtscript_Vector2f_static_call, proto, qtscript_Vector2f_function_lengths[0] );
    ctor.setData( QScriptValue( engine, uint( 0xBABE0000 + 0 ) ) );
    for( int i = 0; i < 1; ++i )
    {
        QScriptValue fun = engine->newFunction( qtscript_Vector2f_static_call,
                                                qtscript_Vector2f_function_lengths[i + 1] );
        fun.setData( QScriptValue( engine, uint( 0xBABE0000 + i + 1 ) ) );
        ctor.setProperty( QString::fromLatin1( qtscript_Vector2f_function_names[i + 1] ),
                          fun, QScriptValue::SkipInEnumeration );
    }

    return ctor;
}
