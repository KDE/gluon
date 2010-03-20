#include "pluginmanager.h"
#include "plugin.h"

#include <KDebug>
#include <KServiceTypeTrader>

#include <core/debughelper.h>

using namespace GluonCreator;

template<> GLUONCREATOR_EXPORT PluginManager* GluonCore::Singleton<PluginManager>::m_instance = 0;

QList< KPluginInfo > PluginManager::pluginInfos() const
{
    return KPluginInfo::fromServices(KServiceTypeTrader::self()->query("GluonCreator/Plugin"));
}

void PluginManager::setMainWindow(KXmlGuiWindow* window)
{
    m_mainWindow = window;
}

void PluginManager::loadPlugins()
{
    DEBUG_FUNC_NAME
    KConfigGroup group = KGlobal::config()->group("Plugins");
    KService::List offers = KServiceTypeTrader::self()->query("GluonCreator/Plugin");

    KService::List::const_iterator iter;
    for (iter = offers.begin(); iter < offers.end(); ++iter)
    {
        QString error;
        KService::Ptr service = *iter;

        QString serviceName = service->desktopEntryName();
        bool loadPlugin = group.readEntry<bool>(QString("%1Enabled").arg(serviceName), true);

        if (!m_loadedPlugins.contains(serviceName) && loadPlugin)
        {
            KPluginFactory *factory = KPluginLoader(service->library()).factory();

            if (!factory)
            {
                DEBUG_TEXT(QString("KPluginFactory could not load the plugin: %1").arg(service->library()));
                continue;
            }

            Plugin *plugin = factory->create<Plugin>(this);

            if (plugin)
            {
                DEBUG_TEXT(QString("Load plugin: %1").arg(service->name()));
                plugin->load(m_mainWindow);
                m_loadedPlugins.insert(serviceName, plugin);
            }
            else
            {
                DEBUG_TEXT(error);
            }
        }
        else if (!loadPlugin && m_loadedPlugins.contains(serviceName))
        {
            Plugin* plugin = m_loadedPlugins.value(serviceName);
            plugin->unload(m_mainWindow);
            delete plugin;
            m_loadedPlugins.remove(serviceName);
        }
    }
}

#include "pluginmanager.moc"