#include "tagmanagerwindow.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QTreeView>
#include <QtGui/QDesktopWidget>
#include <QtGui/QApplication>

#include <engine/game.h>

using namespace GluonCreator;

TagManagerWindow::TagManagerWindow( QWidget* parent, Qt::WindowFlags f )
    : QDialog( parent, f )
{
    QHBoxLayout* layout = new QHBoxLayout( this );
    setLayout(layout);
}

TagManagerWindow::~TagManagerWindow()
{

}

QSize TagManagerWindow::sizeHint() const
{
    int width = QApplication::desktop()->screenGeometry().width() / 2;
    int height = QApplication::desktop()->screenGeometry().height();

    return QSize( width, height );
}
