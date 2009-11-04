#include <kdemacros.h>
#include <KPluginFactory>
#include <KPluginLoader>

#define GLUON_CREATOR_DOCKPLUGIN_EXPORT( c ) \
        K_PLUGIN_FACTORY( GluonCreatorDockPluginFactory, registerPlugin< c >(); ) \
        K_EXPORT_PLUGIN( GluonCreatorDockPluginFactory("c") )

