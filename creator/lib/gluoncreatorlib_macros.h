#ifndef GLUON_CREATOR_MACROS
#define GLUON_CREATOR_MACROS

#include <kdemacros.h>
#include <KPluginFactory>
#include <KPluginLoader>
#include <QtCore/qglobal.h>

#ifndef GLUONCREATORLIB_EXPORT
#if defined(MAKE_GLUONCREATOR_LIB)
#  define GLUONCREATORLIB_EXPORT Q_DECL_EXPORT
#else
#  define GLUONCREATORLIB_EXPORT Q_DECL_IMPORT
#endif
#endif

# ifndef GLUONCREATORLIB_EXPORT_DEPRECATED
#  define GLUONCREATORLIB_EXPORT_DEPRECATED Q_DECL_DEPRECATED GLUONCREATORLIB_EXPORT
# endif

#ifndef GLUON_CREATOR_PLUGIN_EXPORT
#   define GLUON_CREATOR_PLUGIN_EXPORT( c ) \
           K_PLUGIN_FACTORY( GluonCreatorPluginFactory, registerPlugin< c >(); ) \
           K_EXPORT_PLUGIN( GluonCreatorPluginFactory("c") )
#endif

#endif