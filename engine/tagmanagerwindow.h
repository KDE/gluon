#ifndef GLUON_ENGINE_TAGMANAGERWINDOW_H
#define GLUON_ENGINE_TAGMANAGERWINDOW_H

#include <QWidget>
#include <QObject>
#include "gluon_engine_export.h"

namespace GluonEngine
{
    class GLUON_ENGINE_EXPORT TagManagerWindow : public QWidget
    {
            Q_OBJECT
        public:
            TagManagerWindow( QWidget* parent = 0, Qt::WindowFlags f = 0 );
            ~TagManagerWindow();

            virtual QSize sizeHint() const;
    };
}

#endif