#ifndef GLUONCREATOR_TAGMANAGERWINDOW_H
#define GLUONCREATOR_TAGMANAGERWINDOW_H

#include <QtGui/QDialog>

namespace GluonCreator
{
    class TagManagerWindow : public QDialog
    {
            Q_OBJECT
        public:
            explicit TagManagerWindow( QWidget* parent = 0, Qt::WindowFlags f = 0 );
            virtual ~TagManagerWindow();

            virtual QSize sizeHint() const;
    };
}

#endif // GLUONCREATOR_TAGMANAGERWINDOW_H