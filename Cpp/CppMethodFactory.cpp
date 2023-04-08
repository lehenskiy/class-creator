#pragma once
#include "../BaseFactories/BaseLazyMethodFactory.cpp"

class CppMethodFactory: public BaseLazyMethodFactory
{
    void create(
        QString name,
        AccessModifier::AccessModifierEnum accessModifier,
        ResultType::ResultTypeEnum resultType,
        QString text,
        QList<MethodModifier::MethodModifierEnum> params
    )
    {
        if ((accessModifier == AccessModifier::AccessModifierEnum::PUBLIC // should be implemented through any_of
            || accessModifier == AccessModifier::AccessModifierEnum::PROTECTED
            || accessModifier == AccessModifier::AccessModifierEnum::PRIVATE)
            && !params.contains(MethodModifier::MethodModifierEnum::ABSTRACT)) {
            BaseLazyMethodFactory::create(name, accessModifier, resultType, text, params);
        }
        else {
            this->throwNoSuchEnumElement();
        }
    }

    QString composeAccessModifier(AccessModifier::AccessModifierEnum accessModifier) override
    {
        return QVariant::fromValue(accessModifier).toString() + ":\n";
    }
};
