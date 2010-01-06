/*
* This file is part of the Gluon project.
* Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING.  If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301, USA.
*/

#ifndef KALINFOWIDGET_H
#define KALINFOWIDGET_H

#include "../kal_export.h"

#include <QtGui/QWidget>

class KALInfoWidgetPrivate;
class KAL_EXPORT KALInfoWidget : public QWidget
{
    Q_OBJECT

public:
    KALInfoWidget(QWidget * parent = 0);
    void setupComboBox();
    void setupPreview();
    void setupInformation();

public Q_SLOTS:
    void setDevice(const QString& device);

private:
    Q_DISABLE_COPY(KALInfoWidget)
    KALInfoWidgetPrivate * d;
};

#endif // KALINFOWIDGET_H
