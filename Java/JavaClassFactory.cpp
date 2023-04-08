#pragma once
#include "../BaseFactories/BaseLazyClassFactory.cpp"
#include "JavaMethodFactory.cpp"

class JavaClassFactory: public BaseLazyClassFactory
{
public:
    JavaClassFactory()
    {
        this->methodFactory = new JavaMethodFactory();
    }
};
