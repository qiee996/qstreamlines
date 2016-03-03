#include "stopwatch.h"

namespace qst {

StopWatch::StopWatch()
{
    mStart.tv_nsec = 0;
    mStart.tv_sec = 0;
}

double StopWatch::secondsElapsed()
{
    return mSecondsElapsed;
}

void StopWatch::start()
{
    clock_gettime(CLOCK_REALTIME, & mStart);
}

void StopWatch::stop()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, & now);

    mSecondsElapsed = now.tv_sec - mStart.tv_sec;
    if (mSecondsElapsed) {
        if (mStart.tv_nsec) {
            mSecondsElapsed += (1e9 - mStart.tv_nsec + now.tv_nsec) / 1.0e9;
        } else {
            mSecondsElapsed += now.tv_nsec / 1.0e9;
        }
    } else {
        mSecondsElapsed = (now.tv_nsec - mStart.tv_nsec) / 1.0e9;
    }
}

std::string StopWatch::str()
{
    char tmp[32];

    if (mSecondsElapsed < .000001) {
        sprintf(tmp, "%gns", mSecondsElapsed*1.e9);
    } else if (mSecondsElapsed < .001) {
        sprintf(tmp, "%gus", mSecondsElapsed*1.e6);
    } else if (mSecondsElapsed < 1.0) {
        sprintf(tmp, "%gms", mSecondsElapsed*1.e3);
    } else {
        sprintf(tmp, "%gs", mSecondsElapsed);
    }

    return std::string(tmp);
}
}
/*
    LICENSE BEGIN

    qstreamlines - Realtime streamlines animator.
    Copyright (C) 2016  Remik Ziemlinski

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    LICENSE END
*/