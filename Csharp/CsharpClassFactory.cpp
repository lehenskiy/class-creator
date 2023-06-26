#pragma once
#include "../BaseFactories/BaseLazyClassFactory.cpp"
#include "CsharpMethodFactory.cpp"

class CsharpClassFactory: public BaseLazyClassFactory
{
public:
    CsharpClassFactory()
    {
        this->methodFactory = new CsharpMethodFactory();
    }
};
