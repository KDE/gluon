#ifndef TEXTRENDERERCOMPONENT_H
#define TEXTRENDERERCOMPONENT_H
#include <engine/gluon_engine_export.h>
#include <engine/component.h>
#include <QtGui/QFont>
#include <QtGui/QColor>

namespace GluonEngine
{
    class GLUON_ENGINE_EXPORT TextRendererComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT(GluonEngine::TextRendererComponent)
            Q_PROPERTY(QString text READ text WRITE setText)
            Q_PROPERTY(QFont font READ font WRITE setFont)
            Q_PROPERTY(QColor color READ color WRITE setColor)
            Q_INTERFACES(GluonEngine::Component)

        public:
            TextRendererComponent(QObject* parent = 0);
            virtual QString text() const;
            virtual QFont font() const;
            virtual QColor color() const;

            virtual void start();
            virtual void draw(int timeLapse);
        public slots:
            virtual void setText(const QString& text);
            virtual void setFont(const QFont& font);
            virtual void setColor(const QColor& color);

        private:
            class TextRendererComponentPrivate;
            TextRendererComponentPrivate *d;

    };
}

Q_DECLARE_METATYPE(GluonEngine::TextRendererComponent)
Q_DECLARE_METATYPE(GluonEngine::TextRendererComponent*)

#endif // TEXTRENDERERCOMPONENT_H
