#pragma once
#include "../BaseFactories/BaseLazyMethodFactory.cpp"

class CsharpMethodFactory: public BaseLazyMethodFactory
{
    void create(
        QString name,
        AccessModifier::AccessModifierEnum accessModifier,
        ResultType::ResultTypeEnum resultType,
        QString text,
        QList<MethodModifier::MethodModifierEnum> params
    )
    {
        if (!params.contains(MethodModifier::MethodModifierEnum::VIRTUAL) && !params.contains(MethodModifier::MethodModifierEnum::ABSTRACT)) {
            BaseLazyMethodFactory::create(name, accessModifier, resultType, text, params);
        } else {
            this->throwNoSuchEnumElement();
        }
    }
};
