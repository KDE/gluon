#include "textrenderercomponent.h"

REGISTER_OBJECTTYPE(GluonEngine, TextRendererComponent)

Q_DECLARE_METATYPE(GluonCore::GluonObject*);

namespace GluonEngine
{
    TextRendererComponent::TextRendererComponent(QObject * parent)
        :Component(parent)
    {
mText= "test";



    }

    QString TextRendererComponent::text()
    {
        return mText;
    }

    void TextRendererComponent::setText(const QString &text)
    {
        mText = text;
    }

}
