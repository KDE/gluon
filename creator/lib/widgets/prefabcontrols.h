#ifndef GLUONCREATOR_PREFABCONTROLS_H
#define GLUONCREATOR_PREFABCONTROLS_H

#include <QWidget>

namespace GluonCreator
{
    class PrefabControls : public QWidget
    {
        Q_OBJECT
        public:
            explicit PrefabControls(QWidget* parent = 0, Qt::WindowFlags f = 0);
            virtual ~PrefabControls();
    };
}

#endif // GLUONCREATOR_PREFABCONTROLS_H
