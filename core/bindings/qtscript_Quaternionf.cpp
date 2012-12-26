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
#include <QtCore/qmath.h>
#include <qmetaobject.h>

#include <QVariant>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <core/gluonvarianttypes.h>

using namespace Eigen;

static const char* const qtscript_Quaternionf_function_names[] =
{
    "Quaternionf"
    // static
    , "fromAxisAndAngle"
    , "nlerp"
    , "slerp"
    // prototype
    , "conjugate"
    , "isIdentity"
    , "isNull"
    , "length"
    , "lengthSquared"
    , "normalize"
    , "normalized"
    , "operator_add_assign"
    , "operator_divide_assign"
    , "equals"
    , "operator_multiply_assign"
    , "operator_subtract_assign"
    , "rotatedVector"
    , "scalar"
    , "setScalar"
    , "setVector"
    , "setX"
    , "setY"
    , "setZ"
    , "toVector4D"
    , "vector"
    , "x"
    , "y"
    , "z"
    , "toString"
};

static const char* const qtscript_Quaternionf_function_signatures[] =
{
    "\nVector4f vector\nfloat scalar, Vector3f vector\nfloat scalar, float xpos, float ypos, float zpos"
    // static
    , "Vector3f axis, float angle\nfloat x, float y, float z, float angle" // fromAxisAndAngle
    , "Quaternionf q1, Quaternionf q2, float t" // nlerp
    , "Quaternionf q1, Quaternionf q2, float t" // slerp
    // prototype
    , "" //conjugate
    , "" // isIdentity
    , "" // isNull
    , "" // length
    , "" // lengthSquared
    , "" // normalize
    , "" // normalized
    , "Quaternionf quaternion" // operator_add_assign
    , "float divisor" // operayor_divide_assign
    , "Quaternionf q2" // equals
    , "Quaternionf quaternion\nfloat factor" // operator_multiply_assign
    , "Quaternionf quaternion" // operator_divide_assign
    , "Vector3f vector" // rotatedVector
    , "" // scalar
    , "float scalar" // setScalar
    , "Vector3f vector\nfloat x, float y, float z" // setVector
    , "float x" // setX
    , "float y" // setY
    , "float z" // setZ
    , "" // toVector4D
    , "" // vector
    , "" // x
    , "" // y
    , "" // z
    , "" // toString
};

static const int qtscript_Quaternionf_function_lengths[] =
{
    4
    // static
    , 4 // fromAxisAndAngle
    , 3 // nlerp
    , 3 // slerp
    // prototype
    , 0 // conjugate
    , 0 // isIdentity
    , 0 // isNull
    , 0 // length
    , 0 // lengthSquared
    , 0 // normalize
    , 0 // normalized
    , 1 // operator_add_assign
    , 1 // operator_divide_assign
    , 1 // equals
    , 1 // operayor_multiply_assign
    , 1 // operayor_divide_assign
    , 1 // rotatedVector
    , 0 // scalar
    , 1 // setScalar
    , 3 // getVector
    , 1 // setX
    , 1 // setY
    , 1 // setZ
    , 0 // toVector4D
    , 0 // vector
    , 0 // x
    , 0 // y
    , 0 // z
    , 0 // toString
};

static QScriptValue qtscript_Quaternionf_throw_ambiguity_error_helper(
    QScriptContext* context, const char* functionName, const char* signatures )
{
    QStringList lines = QString::fromLatin1( signatures ).split( QLatin1Char( '\n' ) );
    QStringList fullSignatures;
    for( int i = 0; i < lines.size(); ++i )
        fullSignatures.append( QString::fromLatin1( "%0(%1)" ).arg( functionName ).arg( lines.at( i ) ) );
    return context->throwError( QString::fromLatin1( "Quaternionf::%0(): could not find a function match; candidates are:\n%1" )
                                .arg( functionName ).arg( fullSignatures.join( QLatin1String( "\n" ) ) ) );
}

// Q_DECLARE_METATYPE( Quaternionf* )
// Q_DECLARE_METATYPE( QDataStream* )

//
// Quaternionf
//

static QScriptValue qtscript_Quaternionf_prototype_call( QScriptContext* context, QScriptEngine* )
{
#if QT_VERSION > 0x040400
    Q_ASSERT( context->callee().isFunction() );
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if( context->callee().isFunction() )
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 26;
#endif
    Q_ASSERT( ( _id & 0xFFFF0000 ) == 0xBABE0000 );
    _id &= 0x0000FFFF;
    Quaternionf* _q_self = qscriptvalue_cast<Quaternionf*>( context->thisObject() );
    if( !_q_self )
    {
        return context->throwError( QScriptContext::TypeError,
                                    QString::fromLatin1( "Quaternionf.%0(): this object is not a Quaternionf" )
                                    .arg( qtscript_Quaternionf_function_names[_id + 4] ) );
    }

    switch( _id )
    {
        case 0: // conjugate
            if( context->argumentCount() == 0 )
            {
                Quaternionf _q_result = _q_self->conjugate();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 1: // isIdentity
            if( context->argumentCount() == 0 )
            {
                bool _q_result = ( _q_self->x() == 0 && _q_self->y() == 0 && _q_self->z() == 0 && _q_self->w() == 1 );
                return QScriptValue( context->engine(), _q_result );
            }
            break;

        case 2: // isNull
            if( context->argumentCount() == 0 )
            {
                bool _q_result = ( _q_self->x() == 0 && _q_self->y() == 0 && _q_self->z() == 0 && _q_self->w() == 0 );
                return QScriptValue( context->engine(), _q_result );
            }
            break;

        case 3: // length
            if( context->argumentCount() == 0 )
            {
                float _q_result = _q_self->norm();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 4: // lengthSquared
            if( context->argumentCount() == 0 )
            {
                float _q_result = _q_self->squaredNorm();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 5: // normalize
            if( context->argumentCount() == 0 )
            {
                _q_self->normalize();
                return context->engine()->undefinedValue();
            }
            break;

        case 6: // normalized
            if( context->argumentCount() == 0 )
            {
                Quaternionf _q_result = _q_self->normalized();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 7: // operator_add_assign
            if( context->argumentCount() == 1 )
            {
                Quaternionf _q_arg0 = qscriptvalue_cast<Quaternionf>( context->argument( 0 ) );
                _q_self->x() += _q_arg0.x();
                _q_self->y() += _q_arg0.y();
                _q_self->z() += _q_arg0.z();
                _q_self->w() += _q_arg0.w();
                return qScriptValueFromValue( context->engine(), *_q_self );
            }
            break;

        case 8: // operator_divide_assign
            if( context->argumentCount() == 1 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                _q_self->x() /= _q_arg0;
                _q_self->y() /= _q_arg0;
                _q_self->z() /= _q_arg0;
                _q_self->w() /= _q_arg0;
                return qScriptValueFromValue( context->engine(), *_q_self );
            }
            break;

        case 9: // equals
            if (context->argumentCount() == 1) {
                Quaternionf _q_arg0 = qscriptvalue_cast<Quaternionf>(context->argument(0));
                bool _q_result = _q_self->isApprox( _q_arg0, 0 );
                return QScriptValue(context->engine(), _q_result);
            }
            break;

        case 10: // operator_multiply_assign
            if( context->argumentCount() == 1 )
            {
                if( ( qMetaTypeId<Quaternionf>() == context->argument( 0 ).toVariant().userType() ) )
                {
                    Quaternionf _q_arg0 = qscriptvalue_cast<Quaternionf>( context->argument( 0 ) );
                    _q_self->x() *= _q_arg0.x();
                    _q_self->y() *= _q_arg0.y();
                    _q_self->z() *= _q_arg0.z();
                    _q_self->w() *= _q_arg0.w();
                    return qScriptValueFromValue( context->engine(), *_q_self );
                }
                else if( ( qMetaTypeId<float>() == context->argument( 0 ).toVariant().userType() ) )
                {
                    float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                    _q_self->x() *= _q_arg0;
                    _q_self->y() *= _q_arg0;
                    _q_self->z() *= _q_arg0;
                    _q_self->w() *= _q_arg0;
                    return qScriptValueFromValue( context->engine(), *_q_self );
                }
            }
            break;

        case 11: // operator_subtract_assign
            if( context->argumentCount() == 1 )
            {
                Quaternionf _q_arg0 = qscriptvalue_cast<Quaternionf>( context->argument( 0 ) );
                _q_self->x() -= _q_arg0.x();
                _q_self->y() -= _q_arg0.y();
                _q_self->z() -= _q_arg0.z();
                _q_self->w() -= _q_arg0.w();
                return qScriptValueFromValue( context->engine(), *_q_self );
            }
            break;

        case 12: // rotatedVector
            if( context->argumentCount() == 1 )
            {
                Vector3f _q_arg0 = qscriptvalue_cast<Vector3f>( context->argument( 0 ) );
                Vector3f _q_result = _q_self->_transformVector( _q_arg0 );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 13: // scalar
            if( context->argumentCount() == 0 )
            {
                float _q_result = _q_self->w();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 14: // setScalar
            if( context->argumentCount() == 1 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                _q_self->w() = _q_arg0;
                return context->engine()->undefinedValue();
            }
            break;

        case 15: // setVector
            if( context->argumentCount() == 1 )
            {
                Vector3f _q_arg0 = qscriptvalue_cast<Vector3f>( context->argument( 0 ) );
                _q_self->x() = _q_arg0.x();
                _q_self->y() = _q_arg0.y();
                _q_self->z() = _q_arg0.z();
                return context->engine()->undefinedValue();
            }
            if( context->argumentCount() == 3 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                float _q_arg1 = qscriptvalue_cast<float>( context->argument( 1 ) );
                float _q_arg2 = qscriptvalue_cast<float>( context->argument( 2 ) );
                _q_self->x() = _q_arg0;
                _q_self->y() = _q_arg1;
                _q_self->z() = _q_arg2;
                return context->engine()->undefinedValue();
            }
            break;

        case 16: // setX
            if( context->argumentCount() == 1 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                _q_self->x() = _q_arg0;
                return context->engine()->undefinedValue();
            }
            break;

        case 17: // setY
            if( context->argumentCount() == 1 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                _q_self->y() = _q_arg0;
                return context->engine()->undefinedValue();
            }
            break;

        case 18: // setZ
            if( context->argumentCount() == 1 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                _q_self->z() = _q_arg0;
                return context->engine()->undefinedValue();
            }
            break;

        case 19: // toVector4D
            if( context->argumentCount() == 0 )
            {
                Vector4f _q_result( _q_self->x(), _q_self->y(), _q_self->z(), _q_self->w() );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 20: // vector
            if( context->argumentCount() == 0 )
            {
                Vector3f _q_result( _q_self->vec() );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 21: // x
            if( context->argumentCount() == 0 )
            {
                float _q_result = _q_self->x();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 22: // y
            if( context->argumentCount() == 0 )
            {
                float _q_result = _q_self->y();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 23: // z
            if( context->argumentCount() == 0 )
            {
                float _q_result = _q_self->z();
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 24: // toString
        {
            QString result;
            QDebug d( &result );
            d << "Quaternionf(" << _q_self->x() << _q_self->y() << _q_self->z() << _q_self->w() << ")\n";
            return QScriptValue( context->engine(), result );
        }

        default:
            Q_ASSERT( false );
    }
    return qtscript_Quaternionf_throw_ambiguity_error_helper( context,
            qtscript_Quaternionf_function_names[_id + 4],
            qtscript_Quaternionf_function_signatures[_id + 4] );
}

static QScriptValue qtscript_Quaternionf_static_call( QScriptContext* context, QScriptEngine* )
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT( ( _id & 0xFFFF0000 ) == 0xBABE0000 );
    _id &= 0x0000FFFF;
    switch( _id )
    {
        case 0:
            if( context->thisObject().strictlyEquals( context->engine()->globalObject() ) )
            {
                return context->throwError( QString::fromLatin1( "Quaternionf(): Did you forget to construct with 'new'?" ) );
            }
            if( context->argumentCount() == 0 )
            {
                Quaternionf _q_cpp_result;
                QScriptValue _q_result = context->engine()->newVariant( context->thisObject(), qVariantFromValue( _q_cpp_result ) );
                return _q_result;
            }
            else if( context->argumentCount() == 1 )
            {
                Vector4f _q_arg0 = qscriptvalue_cast<Vector4f>( context->argument( 0 ) );
                Quaternionf _q_cpp_result( _q_arg0 );
                QScriptValue _q_result = context->engine()->newVariant( context->thisObject(), qVariantFromValue( _q_cpp_result ) );
                return _q_result;
            }
            else if( context->argumentCount() == 2 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                Vector3f _q_arg1 = qscriptvalue_cast<Vector3f>( context->argument( 1 ) );
                Quaternionf _q_cpp_result( _q_arg1.x(), _q_arg1.y(), _q_arg1.z(), _q_arg0 );
                QScriptValue _q_result = context->engine()->newVariant( context->thisObject(), qVariantFromValue( _q_cpp_result ) );
                return _q_result;
            }
            else if( context->argumentCount() == 4 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                float _q_arg1 = qscriptvalue_cast<float>( context->argument( 1 ) );
                float _q_arg2 = qscriptvalue_cast<float>( context->argument( 2 ) );
                float _q_arg3 = qscriptvalue_cast<float>( context->argument( 3 ) );
                Quaternionf _q_cpp_result( _q_arg0, _q_arg1, _q_arg2, _q_arg3 );
                QScriptValue _q_result = context->engine()->newVariant( context->thisObject(), qVariantFromValue( _q_cpp_result ) );
                return _q_result;
            }
            break;

        case 1: // fromAxisAndAngle
            if( context->argumentCount() == 2 )
            {
                Vector3f _q_arg0 = qscriptvalue_cast<Vector3f>( context->argument( 0 ) );
                float _q_arg1 = qscriptvalue_cast<float>( context->argument( 1 ) );
                Quaternionf _q_result( AngleAxis<float>( (float) _q_arg1 * M_PI / 180., _q_arg0.normalized() ) );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            if( context->argumentCount() == 4 )
            {
                float _q_arg0 = qscriptvalue_cast<float>( context->argument( 0 ) );
                float _q_arg1 = qscriptvalue_cast<float>( context->argument( 1 ) );
                float _q_arg2 = qscriptvalue_cast<float>( context->argument( 2 ) );
                float _q_arg3 = qscriptvalue_cast<float>( context->argument( 3 ) );
                Quaternionf _q_result( AngleAxis<float>( (float) _q_arg3 * M_PI / 180., Vector3f(_q_arg0, _q_arg1, _q_arg2) ) );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 2: // nlerp
            if( context->argumentCount() == 3 )
            {
                Quaternionf _q_arg0 = qscriptvalue_cast<Quaternionf>( context->argument( 0 ) );
                Quaternionf _q_arg1 = qscriptvalue_cast<Quaternionf>( context->argument( 1 ) );
                float _q_arg2 = qscriptvalue_cast<float>( context->argument( 2 ) );
                Quaternionf _q_result = _q_arg0.slerp( _q_arg2, _q_arg1 );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        case 3: // slerp
            if( context->argumentCount() == 3 )
            {
                Quaternionf _q_arg0 = qscriptvalue_cast<Quaternionf>( context->argument( 0 ) );
                Quaternionf _q_arg1 = qscriptvalue_cast<Quaternionf>( context->argument( 1 ) );
                float _q_arg2 = qscriptvalue_cast<float>( context->argument( 2 ) );
                Quaternionf _q_result = _q_arg0.slerp( _q_arg2, _q_arg1 );
                return qScriptValueFromValue( context->engine(), _q_result );
            }
            break;

        default:
            Q_ASSERT( false );
    }
    return qtscript_Quaternionf_throw_ambiguity_error_helper( context,
            qtscript_Quaternionf_function_names[_id],
            qtscript_Quaternionf_function_signatures[_id] );
}

QScriptValue qtscript_create_Quaternionf_class( QScriptEngine* engine )
{
    engine->setDefaultPrototype( qMetaTypeId<Quaternionf*>(), QScriptValue() );
    QScriptValue proto = engine->newVariant( qVariantFromValue( ( Quaternionf* )0 ) );
    for( int i = 0; i < 27; ++i )
    {
        QScriptValue fun = engine->newFunction( qtscript_Quaternionf_prototype_call, qtscript_Quaternionf_function_lengths[i + 4] );
        fun.setData( QScriptValue( engine, uint( 0xBABE0000 + i ) ) );
        proto.setProperty( QString::fromLatin1( qtscript_Quaternionf_function_names[i + 4] ),
                           fun, QScriptValue::SkipInEnumeration );
    }

    engine->setDefaultPrototype( qMetaTypeId<Quaternionf>(), proto );
    engine->setDefaultPrototype( qMetaTypeId<Quaternionf*>(), proto );

    QScriptValue ctor = engine->newFunction( qtscript_Quaternionf_static_call, proto, qtscript_Quaternionf_function_lengths[0] );
    ctor.setData( QScriptValue( engine, uint( 0xBABE0000 + 0 ) ) );
    for( int i = 0; i < 3; ++i )
    {
        QScriptValue fun = engine->newFunction( qtscript_Quaternionf_static_call,
                                                qtscript_Quaternionf_function_lengths[i + 1] );
        fun.setData( QScriptValue( engine, uint( 0xBABE0000 + i + 1 ) ) );
        ctor.setProperty( QString::fromLatin1( qtscript_Quaternionf_function_names[i + 1] ),
                          fun, QScriptValue::SkipInEnumeration );
    }

    return ctor;
}
