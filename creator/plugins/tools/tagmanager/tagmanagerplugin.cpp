#include "tagmanagerplugin.h"
#include "tagmanagerwindow.h"

#include <KDE/KAction>
#include <KDE/KActionCollection>
#include <KDE/KLocalizedString>

using namespace GluonCreator;

TagManagerPlugin::TagManagerPlugin(QObject* parent, const QList< QVariant >& params)
    : ToolPlugin(parent, params)
{
    setComponentData( KGlobal::mainComponent() );
    setXMLFile( "gluon_creator_toolplugin_projectinspectorui.rc", true );
}

TagManagerPlugin::~TagManagerPlugin()
{
    TagManagerWindow window;
    window.exec();
}

void TagManagerPlugin::showWindow()
{
}

void TagManagerPlugin::initialize()
{
    KAction* showAction = new KAction( i18nc( "Show the Tag Manager Window", "Tag Manager..." ), this );
    connect( showAction, SIGNAL(triggered(bool)), SLOT(showWindow()) );
    actionCollection()->addAction( "show_tagmanager", showAction );
}

GLUON_CREATOR_PLUGIN_EXPORT( TagManagerPlugin )