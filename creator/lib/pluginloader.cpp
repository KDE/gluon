#include "pluginloader.h"
#include "plugin.h"

#include <KDebug>
#include <KServiceTypeTrader>

using namespace Gluon::Creator;

template<> GLUONCREATORLIB_EXPORT PluginLoader* KSingleton<PluginLoader>::m_instance = 0;

void PluginLoader::loadAllPlugins()
{
  kDebug(3344) << "Load all plugins";
  KService::List offers = KServiceTypeTrader::self()->query("GluonCreator/Plugin");
  kDebug(3344) << "Found" << offers.size() << "plugins.";

  KService::List::const_iterator iter;
  for(iter = offers.begin(); iter < offers.end(); ++iter)
  {
    QString error;
    KService::Ptr service = *iter;
    
    KPluginFactory *factory = KPluginLoader(service->library()).factory();
    
    if (!factory)
    {
      //KMessageBox::error(0, i18n("<html><p>KPluginFactory could not load the plugin:<br/><i>%1</i></p></html>",
                                                            //                         service->library()));
      kError(5001) << "KPluginFactory could not load the plugin:" << service->library();
      continue;
    }
    
    Plugin *plugin = factory->create<Plugin>(this);
    
    if (plugin) {
      kDebug(3344) << "Load plugin:" << service->name();
      emit pluginLoaded(plugin);
    } else {
      kDebug() << error;
    }
  }
}

#include "pluginloader.moc"