/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "fpscounter.h"


namespace GluonGraphics
{

    FPSCounter::FPSCounter()
    {
        mFPS = 0;
        mFrames = -1;
        resetTimeElapsed();
        mTotalTimeElapsed = 0;
    }

    void FPSCounter::resetTimeElapsed()
    {
        mTimeElapsed = 0;
        mTotalTimeElapsed += mLastTime.elapsed() / 1000.0f;
        mLastTime.restart();
    }

    void FPSCounter::nextFrame()
    {
        mFrames++;
        mTimeElapsed = mLastTime.restart() / 1000.0f;
        mTotalTimeElapsed += mTimeElapsed;
        if (mFrames == 0)
        {
            mTime.start();
        }
        else if (mTime.elapsed() > 1000)
        {
            mFPS = mFrames / (mTime.elapsed() / 1000.0f);
            mTime.restart();
            mFrames = 0;
        }
    }

    QString FPSCounter::fpsString() const
    {
        if (fps() > 100)
        {
            return QString("%1").arg((int)fps());
        }
        else
        {
            return QString("%1").arg(fps(), 0, 'g', 3);
        }
    }

}
