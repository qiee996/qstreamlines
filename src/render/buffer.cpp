#include "render/buffer.h"

namespace qst {

Buffer::Buffer() : mBytes(0), mDepth(0), mHeight(0), mWidth(0)
{
}

Buffer::~Buffer()
{
    destroy();
}

void Buffer::adjust(int depth, int w, int h)
{
    if (w != mWidth || h != mHeight || depth != mDepth) {
        mDepth = depth;
        mWidth = w;
        mHeight = h;
        init();
    }
}

unsigned char* Buffer::bytes() const
{
    return mBytes;
}

int Buffer::depth()
{
    return mDepth;
}

void Buffer::destroy()
{
    if (mBytes) {
        delete [] mBytes;
        mBytes = 0;
    }
}

int Buffer::height()
{
    return mHeight;
}

void Buffer::init()
{
    destroy();

    if (mHeight && mWidth) {
        mBytes = new unsigned char[mDepth*mHeight*mWidth];
    }
}

int Buffer::width()
{
    return mWidth;
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