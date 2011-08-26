#include "colorgen.h"

ColorGen::ColorGen(int hue, int sat, int step)
{
    qsrand(13);
    this->sat = sat;
    this->hue = hue;
    this->hueorig = hue;
    this->satorig = sat;
    this->step = step;
    this->v = 0;
}

QColor ColorGen::nextColor()
{
    QColor color(0,0,0,0);

    if(hue >= 255){
        sat += step;
        if(sat >= 255){
            sat = 0;
        }
        hue = 0;
    }
    hue += step;

    color.setHsv(hue,sat,255,255);
    return color;
}

QColor ColorGen::randomColor()
{
    v = 255 * qrand();

    QColor color(0,0,0,0);
    color.setHsv(v,sat,255,255);
    return color;
}

void ColorGen::reset()
{
    hue = hueorig;
    sat = satorig;
}
