#ifndef CANCONNECTOR_H
#define CANCONNECTOR_H
#include "JDX_Thread.h"

class JDX_CanConnector:public JDX_Thread
{
public:
    JDX_CanConnector();
    ~JDX_CanConnector();

    void run();
};

#endif // CANCONNECTOR_H
