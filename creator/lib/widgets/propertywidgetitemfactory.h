/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef GLUON_CREATOR_PROPERTYWIDGETITEMFACTORY_H
#define GLUON_CREATOR_PROPERTYWIDGETITEMFACTORY_H

#include "gluoncreator_macros.h"

#include <core/singleton.h>
#include <QtCore/QHash>


namespace GluonCreator {

class PropertyWidgetItem;

class GLUONCREATOR_EXPORT PropertyWidgetItemFactory : public GluonCore::Singleton<PropertyWidgetItemFactory>
{
    public:
        PropertyWidgetItem* create(const QObject *object, const QString& type, QWidget* parent);
        void registerNewPIW(PropertyWidgetItem* newPIW);

    private:
        friend class GluonCore::Singleton<PropertyWidgetItemFactory>;
        QHash<QString, PropertyWidgetItem*> piwTypes;

        PropertyWidgetItemFactory() { }
        ~PropertyWidgetItemFactory() { }
        Q_DISABLE_COPY(PropertyWidgetItemFactory)
};

}

template<class T>
class GLUONCREATOR_EXPORT PropertyWidgetItemRegistration
{
    public:
        PropertyWidgetItemRegistration(T* newPIW)
        {
            if(newPIW->metaObject())
            {
                GluonCreator::PropertyWidgetItemFactory::instance()->registerNewPIW(newPIW);
            }
        }
};

#define REGISTER_PROPERTYWIDGETITEM(NAMESPACE,NEWPIW) \
namespace NAMESPACE { PropertyWidgetItemRegistration<NEWPIW> NEWPIW ## _PropertyWidgetItemRegistration_(new NEWPIW()); }

#endif // GLUON_CREATOR_PROPERTYWIDGETITEMFACTORY_H
