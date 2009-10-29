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

#ifndef GLUON_CREATOR_PLUGIN_H
#define GLUON_CREATOR_PLUGIN_H

#include <QtCore/QObject>
#include <QSharedData>

class QDialog;
class QDockWidget;

namespace Gluon {

namespace Creator {

class Plugin : public QObject
{
    Q_OBJECT
    public:
        enum PluginCapability
        {
            PC_NONE = 0x0,
            PC_WIDGET = 0x1,
            PC_DOCK = 0x2,
            PC_DIALOG = 0x4
        };
        Q_DECLARE_FLAGS(PluginCapabilities, PluginCapability)
        
        Plugin(QObject * parent = 0);
        virtual ~Plugin();

        QString name();
        QString description();
        PluginCapabilities capabilities();

    public slots:
        /**
        * Instantiate an arbitrary QWidget.
        */
        virtual QWidget* instantiate(QObject * parent = 0) = 0;
        /**
        * Instantiate a dock widget.
        */
        virtual QDockWidget* instantiateDock(QObject * parent = 0) = 0;
        /**
        * Instantiate a tool dialog.
        */
        virtual QDialog* instantiateDialog(QObject * parent = 0) = 0;

    protected slots:
        void setName(const QString& name);
        void setDescription(const QString& description);
        void setCapabilities(const PluginCapabilities& capabilities);

    private:
        class PluginPrivate;
        QSharedDataPointer<PluginPrivate> d;
};

}

}

#endif // GLUON_CREATOR_PLUGIN_H
