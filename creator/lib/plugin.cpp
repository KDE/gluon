#include "plugin.h"

using namespace Gluon::Creator;

Plugin::Plugin(QObject* parent, const QList< QVariant >& params) : QObject(parent)
{
    Q_UNUSED(params)
}


Plugin::~Plugin()
{
    
}

#include "plugin.moc"