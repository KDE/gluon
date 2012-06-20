#include "tagmanagerwindow.h"

#include <QHBoxLayout>
#include <QtGui/QDesktopWidget>
#include <QtGui/QApplication>

#include <engine/game.h>

using namespace GluonEngine;

TagManagerWindow::TagManagerWindow( QWidget* parent, Qt::WindowFlags f )
    : QWidget( parent, f )
{
    QHBoxLayout* layout = new QHBoxLayout( this );
    setLayout(layout);
    setWindowTitle( "Manage Tags" );
    setGeometry( QRect( 500, 500, 500, 500) );
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

#include "tagmanagerwindow.moc"