#include "pluginmanager.h"
#include "plugin.h"

#include <KDebug>
#include <KServiceTypeTrader>

using namespace Gluon::Creator;

template<> GLUONCREATORLIB_EXPORT PluginManager* KSingleton<PluginManager>::m_instance = 0;

QList< KPluginInfo > Gluon::Creator::PluginManager::pluginInfos() const
{
    return KPluginInfo::fromServices(KServiceTypeTrader::self()->query("GluonCreator/Plugin"));
}

void Gluon::Creator::PluginManager::setMainWindow(KXmlGuiWindow* window)
{
    m_mainWindow = window;
}

void PluginManager::loadPlugins()
{
    KConfigGroup group = KGlobal::config()->group("Plugins");
    KService::List offers = KServiceTypeTrader::self()->query("GluonCreator/Plugin");

    KService::List::const_iterator iter;
    for(iter = offers.begin(); iter < offers.end(); ++iter)
    {
        QString error;
        KService::Ptr service = *iter;

        QString serviceName = service->desktopEntryName();
        bool loadPlugin = group.readEntry<bool>(QString("%1Enabled").arg(serviceName), true);

        if(!m_loadedPlugins.contains(serviceName) && loadPlugin)
        {
            KPluginFactory *factory = KPluginLoader(service->library()).factory();

            if (!factory)
            {
                kError(5001) << "KPluginFactory could not load the plugin:" << service->library();
                continue;
            }

            Plugin *plugin = factory->create<Plugin>(this);

            if (plugin) {
                kDebug(3344) << "Load plugin:" << service->name();
                plugin->load(m_mainWindow);
                m_loadedPlugins.insert(serviceName, plugin);
            } else {
                kDebug() << error;
            }
        }
        else if(!loadPlugin && m_loadedPlugins.contains(serviceName))
        {
            Plugin* plugin = m_loadedPlugins.value(serviceName);
            plugin->unload(m_mainWindow);
            delete plugin;
            m_loadedPlugins.remove(serviceName);
        }
    }
}

#include "pluginmanager.moc"