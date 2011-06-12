/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#ifndef GLUONPLAYER_OCSGAMEUPLOADPROVIDER_H
#define GLUONPLAYER_OCSGAMEUPLOADPROVIDER_H

#include <QObject>

namespace Attica
{
class Provider;
class BaseJob;
}

namespace GluonPlayer
{

class OcsGameUploadProvider : public QObject
{

    Q_OBJECT
public:
    OcsGameUploadProvider (Attica::Provider* provider, const QString& id, const QString& fileName,
                             QObject* parent = 0);
    virtual ~OcsGameUploadProvider();
private:
    class Private;
    Private* const d;
signals:
    void started();
    void finished();
    void failed();
private slots:
    void startUpload();
    void uploadComplete (Attica::BaseJob* baseJob);

    friend class OcsProvider;
};

}

#endif // GLUONPLAYER_OCSGAMEUPLOADPROVIDER_H
