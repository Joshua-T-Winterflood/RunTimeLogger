#ifndef SQUARE_H
#define SQUARE_H

#include <math.h>
#include <thread>
#include "RunTimeLogger.h"

class Square
{
    private:
        float m_side_lenght;

    public:
        Square(float sidelength);
        float GetArea();
        void ExpensiveFunctionSimulator();
};


#endif