#ifndef BUFFER_H
#define BUFFER_H

namespace qst {

class Buffer
{
public:
    Buffer();
    ~Buffer();

    void adjust(int depth, int w, int h);
    unsigned char* bytes() const;
    int depth();
    void destroy();
    int height();
    void init();
    int width();

private:
    unsigned char *mBytes;
    int mDepth;
    int mHeight;
    int mWidth;
};

}

#endif
