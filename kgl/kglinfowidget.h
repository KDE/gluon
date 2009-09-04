#ifndef KGLINFOWIDGET_H
#define KGLINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <KTabWidget>
#include "kglengine.h"
#include "kglview.h"

class KGLInfoWidget : public QWidget
{
public:
    KGLInfoWidget(QWidget * parent=0);

    void setupInformation();
private:
    QWidget * m_information;
    QWidget * m_preview;
    KGLView * m_view;


};

#endif // KCLINFOWIDGET_H
