#include "textrenderercomponent.h"
#include <graphics/textitem.h>
#include <QMessageBox>
#include <gameobject.h>
#include <graphics/meshes/polygonmesh.h>
REGISTER_OBJECTTYPE(GluonEngine, TextRendererComponent)

        Q_DECLARE_METATYPE(GluonCore::GluonObject*);

namespace GluonEngine
{

    class TextRendererComponent::TextRendererComponentPrivate
    {
    public:
        TextRendererComponentPrivate()
        {
            text = "empty";

        }

        QString text;
        GluonGraphics::TextItem * textItem;

    };


    TextRendererComponent::TextRendererComponent(QObject * parent)
        :Component(parent)
    {
        d = new TextRendererComponentPrivate;

    }

    QString TextRendererComponent::text()
    {
        return d->text;
    }

    void TextRendererComponent::setText(const QString &text)
    {
        if ( d->textItem)
        {
            d->text = text;
            d->textItem->setText(text);
        }

    }

    void TextRendererComponent::start()
    {


        d->textItem = new GluonGraphics::TextItem("Bonjour");
        d->textItem->setColor(Qt::white);
        d->textItem->scale(10,10);
        d->textItem->updateTransform();

    }

    void TextRendererComponent::draw ( int timeLapse )
    {

        if(d->textItem) {
            d->textItem->setMatrix(gameObject()->transform());
        }


    }

}

Q_EXPORT_PLUGIN2(gluon_component_textrenderer, GluonEngine::TextRendererComponent);

#include "textrenderercomponent.moc"
