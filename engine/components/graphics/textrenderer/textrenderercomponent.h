#ifndef TEXTRENDERERCOMPONENT_H
#define TEXTRENDERERCOMPONENT_H
#include <engine/gluon_engine_export.h>
#include <engine/component.h>

namespace GluonEngine
{
    class GLUON_ENGINE_EXPORT TextRendererComponent : public Component
    {
        Q_OBJECT
        GLUON_OBJECT(GluonEngine::TextRendererComponent)
        Q_PROPERTY(QString text READ text WRITE setText)
        Q_INTERFACES(GluonEngine::Component)

    public:
        TextRendererComponent(QObject* parent = 0 );
        virtual QString text();
    virtual void start();
    virtual void draw ( int timeLapse );
    public slots:
        virtual void setText(const QString& text);

    private:
        class TextRendererComponentPrivate;
        TextRendererComponentPrivate *d;

    };
}
#endif // TEXTRENDERERCOMPONENT_H
