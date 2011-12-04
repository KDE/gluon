/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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


#ifndef GAMEDETAILSMODEL_H
#define GAMEDETAILSMODEL_H

#include <QSortFilterProxyModel>

class GameDetailsModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)

public:
    GameDetailsModel( QObject* parent = 0 );
    QString id() const;
    void setId(const QString &id);

Q_SIGNALS:
    void idChanged();

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;

private:
    QString m_id;
};

#endif // GAMEDETAILSMODEL_H
