/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <>
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

#ifndef GLUON_GRAPHICS_FPSCOUNTER_H
#define GLUON_GRAPHICS_FPSCOUNTER_H

#include "gluon_graphics_export.h"

#include <QtCore/QTime>
#include <QtCore/QString>

namespace GluonGraphics
{

    /**
     * @brief Utility class that measures FPS.
     *
     * FPSCounter is a utility class that keeps track of FPS (frames per second) of
     *  your application. It can be a simple performance measurement tool.
     *
     * Using FPSCounter is simple: if you're using GLWidget then all you have to do
     *  is calling fps() or fpsString() method to find out the current FPS. You can
     *  also call timeElapsed() to find out how much time has elapsed since last
     *  frame was rendered. This could be useful e.g. in animations where an object
     *  has a fixed speed and you multiply it by the elapsed time every frame to
     *  find out how much the object should be moved.
     *
     * If you don't use GLWidget then you need to call nextFrame() every time that
     *  another frame is rendered.
     *
     * The fps value is recalculated once a second.
     *
     * You can also use totalTimeElapsed() to find out how much time has elapsed
     *  since nextFrame() was called the very first time.
     *
     * @see GLWidget
     **/
    class GLUON_GRAPHICS_EXPORT FPSCounter
    {
        public:
            /**
             * Creates new FPS counter. The counter isn't started until nextFrame()
             *  is called for the first time.
             **/
            FPSCounter();

            /**
             * This method should be called whenever a frame is rendered. It increases
             *  the internal counters and updates the calculated FPS value once a
             *  second.
             *
             * @see fps(), timeElapsed()
             **/
            void nextFrame();
            void resetTimeElapsed();

            /**
             * Returns the current FPS value.
             *
             * Note that the value is recalculated by nextFrame() about once a second.
             *
             * @see fpsString(), timeElapsed(), nextFrame()
             **/
            float fps() const
            {
                return mFPS;
            }
            /**
             * Returns the current FPS value as string.
             *
             * Number of significant digits in the string is kept at 3, so possible
             *  return values include "123", "42.7" and "3.84".
             *
             * @see fps()
             **/
            QString fpsString() const;
            /**
             * Returnes time elapsed between last two calls to nextFrame() method.
             * Usually that gives you the time elapsed since last frame and could be
             *  used e.g. for animation purposes.
             *
             * The return value is in seconds, thus a value of 0.075 would indicate
             *  that 75 milliseconds have elapsed.
             *
             * @see fps()
             **/
            // TODO: rename to timeSinceLastFrame()? change semantics?
            float timeElapsed()
            {
                return mTimeElapsed;
            }
            /**
             * Returns amount of time that has elapsed since the first call to
             *  nextFrame().
             *
             * @see timeElapsed(), nextFrame()
             **/
            float totalTimeElapsed()
            {
                return mTotalTimeElapsed;
            }

        protected:
            QTime mTime;
            int mFrames;
            float mFPS;

            float mTimeElapsed;  // in sec
            float mTotalTimeElapsed;  // in sec
            QTime mLastTime;
    };

}
#endif // GLUON_GRAPHICS_FPSCOUNTER_H
