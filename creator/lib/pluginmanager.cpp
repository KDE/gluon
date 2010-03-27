#include "pluginmanager.h"
#include "plugin.h"

#include <KDebug>
#include <KServiceTypeTrader>

#include <core/debughelper.h>

using namespace GluonCreator;

template<> GLUONCREATOR_EXPORT PluginManager* GluonCore::Singleton<PluginManager>::m_instance = 0;

class PluginManager::PluginManagerPrivate
{
    public:
        PluginManagerPrivate() { mainWindow = 0; }
        QHash<QString, Plugin*> loadedPlugins;
        KXmlGuiWindow* mainWindow;
};

QList< KPluginInfo > PluginManager::pluginInfos() const
{
    return KPluginInfo::fromServices(KServiceTypeTrader::self()->query("GluonCreator/Plugin"));
}

void PluginManager::setMainWindow(KXmlGuiWindow* window)
{
    d->mainWindow = window;
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

        if (!d->loadedPlugins.contains(serviceName) && loadPlugin)
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
                plugin->load(d->mainWindow);
                d->loadedPlugins.insert(serviceName, plugin);
            }
            else
            {
                DEBUG_TEXT(error);
            }
        }
        else if (!loadPlugin && d->loadedPlugins.contains(serviceName))
        {
            Plugin* plugin = d->loadedPlugins.value(serviceName);
            plugin->unload(d->mainWindow);
            delete plugin;
            d->loadedPlugins.remove(serviceName);
        }
    }
}

PluginManager::PluginManager() : d(new PluginManagerPrivate)
{
}

PluginManager::~PluginManager()
{
    delete d;
}

#include "pluginmanager.moc"
