/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef GLUONCREATOR_COMPONENTSLISTMODELSORTPROXY_H
#define GLUONCREATOR_COMPONENTSLISTMODELSORTPROXY_H

#include <kcategorizedsortfilterproxymodel.h>

namespace GluonCreator
{
    class ComponentsListModelSortProxy : public KCategorizedSortFilterProxyModel
    {
        Q_OBJECT
        public:
            ComponentsListModelSortProxy(QObject *parent = 0);
            virtual ~ComponentsListModelSortProxy();
            
            virtual bool lessThan( const QModelIndex &left, const QModelIndex &right ) const;
        protected:
            virtual bool subSortLessThan(const QModelIndex& left, const QModelIndex& right) const;
            virtual int compareCategories(const QModelIndex& left, const QModelIndex& right) const;
    };
}

#endif // GLUONCREATOR_COMPONENTSLISTMODELSORTPROXY_H
