/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef KGLRESOLUTIONDIALOG_H
#define KGLRESOLUTIONDIALOG_H

#include <QtGui/QDialog>

#include "kgl/kglresolution.h"

class QComboBox;
struct KGLResolution;
class KGLView;

class KGLResolutionDialog : public QDialog
{
  public:
    KGLResolutionDialog(QWidget* parent = 0);

    KGLResolution selectedResolution() const;

  private:
    QList<KGLResolution> m_resolutions;
    QComboBox* m_resolutionComboBox;
    KGLView* m_parent;
};

#endif // KGLRESOLUTIONDIALOG_H
