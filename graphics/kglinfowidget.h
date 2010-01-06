#ifndef KGLINFOWIDGET_H
#define KGLINFOWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QTabWidget>

#include "kgl_export.h"
#include "kglengine.h"
#include "kglview.h"

/**
 * \defgroup KGL KGL
 */
//@{

class KGL_EXPORT KGLInfoWidget : public QWidget
{
public:
    KGLInfoWidget(QWidget * parent=0);

    void setupInformation();
private:
    QWidget * m_information;
    QWidget * m_preview;
    KGLView * m_view;


};

//@}
#endif // KCLINFOWIDGET_H
