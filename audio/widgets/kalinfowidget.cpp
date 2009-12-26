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

#include "kalinfowidget.h"
#include "kalplayerwidget.h"
#include "../kalengine.h"
#include "../kalsound.h"

#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>

#include <QtGui/QComboBox>
#include <QtGui/QIcon>
#include <QtGui/QTabWidget>

class KALInfoWidgetPrivate
{
public:
    QWidget *information;
    QWidget *preview;
    QComboBox *soundComboBox;
    KALSound *source;

};

KALInfoWidget::KALInfoWidget(QWidget * parent)
    : QWidget(parent),
    d(new KALInfoWidgetPrivate)
{
    KALEngine::instance();

    QVBoxLayout *layout = new QVBoxLayout;
    d->information = new QWidget;
    d->preview = new QWidget;
    QTabWidget *tab = new QTabWidget;

    tab->addTab(d->preview, QIcon("run-build-configure.png"), tr("Preview"));
    tab->addTab(d->information, QIcon("run-build-file.png"), tr("Information"));

    setupPreview();
    setupInformation();

    layout->addWidget(tab);
    setLayout(layout);
}


void KALInfoWidget::setupPreview()
{
    KALPlayerWidget *widget = new KALPlayerWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(widget);
    d->preview->setLayout(layout);

}
void KALInfoWidget::setupInformation()
{
    QComboBox * combo = new QComboBox;

    foreach(const QString &device, KALEngine::instance()->deviceList()) {
        combo->addItem(QIcon(), device);
    }

    connect(combo, SIGNAL(activated(QString)), this, SLOT(setDevice(QString)));

    QLabel *logo = new QLabel;
    logo->setPixmap(QIcon("media-flash").pixmap(128, 128));
    logo->setAlignment(Qt::AlignTop);

    QLabel *label = new QLabel;
    QString info = "";
    info += tr("<p>Vendor: %1</p>").arg(QString(alGetString(AL_VENDOR)));
    info += tr("<p>Version: %1</p>").arg(QString(alGetString(AL_VERSION)));
    info += tr("<p>Renderer: %1</p>").arg(QString(alGetString(AL_RENDERER)));

    //info+="<p>Vendor :"+QString(alcGetString(d->alEngine->AL_DEFAULT_DEVICE_SPECIFIER))+ "</p>";
    //info+="<p>Version :"+QString(alcGetString(AL_VERSION)) + "</p>";
    //info+="<p>Renderer :"+QString(alcGetString(AL_RENDERER)) + "</p>";

    label->setText(info);
    label->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    QHBoxLayout *h = new QHBoxLayout;
    h->addWidget(logo);
    h->addWidget(label);

    QVBoxLayout *lv = new QVBoxLayout;
    lv->addLayout(h);
    lv->addWidget(combo);
    lv->addStretch();

    d->information->setLayout(lv);
}


void KALInfoWidget::setDevice(const QString& device)
{
    KALEngine::instance()->setDevice(device);
}

#include "kalinfowidget.moc"
