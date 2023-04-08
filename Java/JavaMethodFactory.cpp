#pragma once
#include "../BaseFactories/BaseLazyMethodFactory.cpp"

class JavaMethodFactory: public BaseLazyMethodFactory
{
    void create(
        QString name,
        AccessModifier::AccessModifierEnum accessModifier,
        ResultType::ResultTypeEnum resultType,
        QString text,
        QList<MethodModifier::MethodModifierEnum> params
    ) override
    {
        if ((accessModifier == AccessModifier::AccessModifierEnum::PUBLIC
            || accessModifier == AccessModifier::AccessModifierEnum::PROTECTED
            || accessModifier == AccessModifier::AccessModifierEnum::PRIVATE)
            && !params.contains(MethodModifier::MethodModifierEnum::VIRTUAL)) {
            BaseLazyMethodFactory::create(name, accessModifier, resultType, text, params);
        }
        else {
            this->throwNoSuchEnumElement();
        }
    }
};
