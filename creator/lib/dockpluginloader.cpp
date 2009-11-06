#include "dockpluginloader.h"
#include "dockplugin.h"

#include <KDebug>
#include <KServiceTypeTrader>

using namespace Gluon::Creator;

DockPluginLoader::DockPluginLoader(QObject* parent) : QObject(parent)
{

}

DockPluginLoader::~DockPluginLoader()
{

}

DockPlugin* DockPluginLoader::loadPlugin(const QString& name)
{
  Q_UNUSED(name)
  return 0;
}

QList< DockPlugin* > DockPluginLoader::loadAllPlugins()
{
  kDebug(3344) << "Load all plugins";
  KService::List offers = KServiceTypeTrader::self()->query("GluonCreator/Dock");
  kDebug(3344) << "Found" << offers.size() << "plugins.";

  QList<DockPlugin*> plugins;

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
    
    DockPlugin *plugin = factory->create<DockPlugin>(this);
    
    if (plugin) {
      kDebug(3344) << "Load plugin:" << service->name();
      emit pluginLoaded(plugin);
      plugins.append(plugin);
    } else {
      kDebug() << error;
    }
  }

  return plugins;
}

#include "dockpluginloader.moc"