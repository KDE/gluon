#ifndef GLUON_CREATOR_MACROS
#define GLUON_CREATOR_MACROS

#include <kdemacros.h>
#include <KPluginFactory>
#include <KPluginLoader>
#include <QtCore/qglobal.h>

#ifndef GLUONCREATOR_EXPORT
#if defined(MAKE_GLUONCREATOR)
#  define GLUONCREATOR_EXPORT Q_DECL_EXPORT
#else
#  define GLUONCREATOR_EXPORT Q_DECL_IMPORT
#endif
#endif

#ifndef GLUONCREATOR_EXPORT_DEPRECATED
#  define GLUONCREATOR_EXPORT_DEPRECATED Q_DECL_DEPRECATED GLUONCREATOR_EXPORT
#endif

#ifndef GLUON_CREATOR_PLUGIN_EXPORT
#   define GLUON_CREATOR_PLUGIN_EXPORT( c ) \
    K_PLUGIN_FACTORY( GluonCreatorPluginFactory, registerPlugin< c >(); ) \
    K_EXPORT_PLUGIN( GluonCreatorPluginFactory("c") )
#endif

#endif // GLUON_CREATOR_MACROS
