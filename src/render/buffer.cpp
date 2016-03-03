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
