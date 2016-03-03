#ifndef SIM_H
#define SIM_H

namespace qst {

class Sim
{
public:
    virtual void advance() = 0;
    virtual void reset() = 0;
};

}
#endif
