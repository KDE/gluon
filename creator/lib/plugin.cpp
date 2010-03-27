#include "plugin.h"

using namespace GluonCreator;

Plugin::Plugin(QObject* parent, const QList< QVariant >& params) : QObject(parent)
{
    Q_UNUSED(params)
}


Plugin::~Plugin()
{

}

#include "plugin.moc"
