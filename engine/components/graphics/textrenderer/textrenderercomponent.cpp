#include "textrenderercomponent.h"
#include <graphics/textitem.h>
#include <QMessageBox>
#include <gameobject.h>
#include <graphics/meshes/polygonmesh.h>
REGISTER_OBJECTTYPE(GluonEngine, TextRendererComponent)

using namespace GluonEngine;

class TextRendererComponent::TextRendererComponentPrivate
{
    public:
        TextRendererComponentPrivate()
        {
            textItem = 0;
            text = "empty";
        }

        QString text;
        QFont font;
        QColor color;
        GluonGraphics::TextItem * textItem;
};


TextRendererComponent::TextRendererComponent(QObject * parent)
        : Component(parent)
{
    d = new TextRendererComponentPrivate;

}

QString
TextRendererComponent::text() const
{
    return d->text;
}

void
TextRendererComponent::setText(const QString &text)
{
    d->text = text;
    if (d->textItem)
        d->textItem->setText(text);
}

QFont
TextRendererComponent::font() const
{
    return d->font;
}

void
TextRendererComponent::setFont(const QFont& font)
{
    d->font = font;
    if (d->textItem)
        d->textItem->setFont(font);
}

QColor
TextRendererComponent::color() const
{
    return d->color;
}

void
TextRendererComponent::setColor(const QColor& color)
{
    d->color = color;
    if (d->textItem)
        d->textItem->setColor(color);
}

void
TextRendererComponent::start()
{


    d->textItem = new GluonGraphics::TextItem(d->text, d->font);
    d->textItem->setColor(d->color);

    d->textItem->updateTransform();

}

void
TextRendererComponent::draw(int timeLapse)
{
    if (d->textItem)
        d->textItem->setMatrix(gameObject()->transform());
}

Q_EXPORT_PLUGIN2(gluon_component_textrenderer, GluonEngine::TextRendererComponent);

#include "textrenderercomponent.moc"
