/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <QDebug>
#include <iostream>

#include <gluon/audio/sound.h>
#include <gluon/audio/engine.h>


int main(int argc, char *argv[])
{
    GluonAudio::Engine::instance();

    GluonAudio::Sound *sound = new GluonAudio::Sound;
    sound->load("/usr/share/sounds/KDE-Sys-Log-In-Long.ogg");
    sound->setVolume(0.9);    //between 0 and 1

    qDebug() << "Playing sound.";
    sound->play();

    qDebug() << "Press enter to continue.";
    std::cin.get();

    sound->stop();

    delete sound;
    GluonAudio::Engine::close(); // This line is unnecessary if you use KApplication. In this case KALEngine will be destroy automatically.
}

