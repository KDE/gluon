/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUONPLAYER_GAMEDETAILLISTJOB_H
#define GLUONPLAYER_GAMEDETAILLISTJOB_H

#include "abstractjob.h"

#include <QtCore/QList>

namespace Attica
{
    class Provider;
    class BaseJob;
}

namespace GluonPlayer
{
class GameDetailItem : public QObject
{
    Q_OBJECT
    Q_ENUMS (Status)
public:
    enum Status {
        Downloadable,
        Installed,
        Upgradable
    };

    GameDetailItem(const QString& gameName, const QString& gameDescription,
                    const QString& projectDirName, const QString& projectFileName,
                    const QStringList& screenshotUrls, GluonPlayer::GameDetailItem::Status status,
                    const QString id, QObject* parent = 0);
    virtual ~GameDetailItem();

    QString gameName() const;
    QString gameDescription() const;
    QString projectDirName() const;
    QString projectFileName() const;
    QStringList screenshotUrls() const;
    Status status() const;
    QString id() const;

private:
    class Private;
    Private* const d;
};

class GameDetailListJob : public AbstractJob
{
    Q_OBJECT
public:
    explicit GameDetailListJob(Attica::Provider* provider, QObject* parent = 0);
    virtual ~GameDetailListJob();

    virtual void start();

    QList<GameDetailItem*> gameDetailList() const;

Q_SIGNALS:
    void gameDetailListFetchStarting();
    void gameDetailListFetchFinished(QList<GameDetailItem*> comments);
    void gameDetailListFetchFailed();

private Q_SLOTS:
    void fetchGameList();
    void processFetchedGameList(Attica::BaseJob* job);

private:
    class Private;
    Private* const d;
};

}

#endif // GLUONPLAYER_GAMEDETAILLISTJOB_H

