#ifndef COLORGEN_H
#define COLORGEN_H

#include <QColor>

class ColorGen
{
public:
    ColorGen(){};
    ColorGen(int hue, int sat,int step);
    QColor nextColor();
    QColor randomColor();
    void reset();
private:
    int sat;
    int hue;
    int step;

    int satorig;
    int hueorig;
    int v;
};

#endif // COLORGEN_H
