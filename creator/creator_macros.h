#include <kdemacros.h>
#include <KPluginFactory>
#include <KPluginLoader>

namespace Gluon {

    namespace Creator
    {
        #define GLUON_CREATOR_PLUGIN_EXPORT( c ) \
            K_PLUGIN_FACTORY( PluginFactory, registerPlugin< c >(); ) \
            K_EXPORT_PLUGIN( PluginFactory("c") )
    }
}
