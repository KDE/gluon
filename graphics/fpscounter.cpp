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
