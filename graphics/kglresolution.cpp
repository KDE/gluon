
#include "kglresolution.h"
#include "kglresolution_p.h"

KGLResolution::KGLResolution()
{
    d = NULL;
}

KGLResolution::KGLResolution(int id, int width, int height, short refreshRate)
{
    d = new KGLResolutionPrivate();
    d->id = id;
    d->width = width;
    d->height = height;
    d->refreshRate = refreshRate;
}

KGLResolution::KGLResolution(const KGLResolution &r)
{
    d = r.d;
}

KGLResolution &KGLResolution::operator=(const KGLResolution &r)
{
    d = r.d;
    return *this;
}

KGLResolution::~KGLResolution()
{
}

QString KGLResolution::name() const
{
    return QString("%1x%2@%3hz").arg(width()).arg(height()).arg(refreshRate());
}

int KGLResolution::id() const
{
    return d->id;
}

int KGLResolution::width() const
{
    return d->width;
}

int KGLResolution::height() const
{
    return d->height;
}

short KGLResolution::refreshRate() const
{
    return d->refreshRate;
}
           