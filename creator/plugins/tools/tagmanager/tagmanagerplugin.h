#ifndef GLUONCREATOR_TAGMANAGERPLUGIN_H
#define GLUONCREATOR_TAGMANAGERPLUGIN_H

#include <creator/lib/toolplugin.h>

namespace GluonCreator
{

    class TagManagerPlugin : public GluonCreator::ToolPlugin
    {
            Q_OBJECT
        public:
            TagManagerPlugin( QObject* parent, const QList<QVariant>& params );
            ~TagManagerPlugin();

        public Q_SLOTS:
            void showWindow();

        protected:
            void initialize();
    };
}

#endif // GLUON_CREATOR_TAGMANAGERPLUGIN_H
