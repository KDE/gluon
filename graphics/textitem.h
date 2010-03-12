#ifndef TEXTITEM_H
#define TEXTITEM_H
#include "item.h"
#include <QFont>
namespace GluonGraphics
{
    class TextItem : public Item
    {
    public:
        explicit TextItem(const QString& txt,const QFont& fnt= QFont(),QObject *parent = 0);
void setText(const QString& txt);
void setFont(const QFont& fnt);
const QString& text();
const QFont& font();

    protected:
bool initTexture();
    private:
        QFont mFont;
        QString mText;



    };
}
#endif // TEXTITEM_H
