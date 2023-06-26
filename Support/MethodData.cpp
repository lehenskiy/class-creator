#include "../Enums/AccessModifierEnum.h"
#include "../Enums/ResultType.h"
#include "../Enums/MethodModifierEnum.h"

struct MethodData
{
public:
    MethodData(
        AccessModifier::AccessModifierEnum accessModifier = AccessModifier::PUBLIC,
        ResultType::ResultTypeEnum resultType = ResultType::VOID,
        QString text = "",
        QList<MethodModifier::MethodModifierEnum> params = {}
        )
    {
        this->accessModifier = accessModifier;
        this->resultType = resultType;
        this->text = text;
        this->params = params;
    }

    AccessModifier::AccessModifierEnum getAccessModifier()
    {
        return this->accessModifier;
    }

    ResultType::ResultTypeEnum getResultType() const
    {
        return this->resultType;
    }

    QString getText() const
    {
        return this->text;
    }

    QList<MethodModifier::MethodModifierEnum> getParams() const
    {
        return this->params;
    }

private:
    AccessModifier::AccessModifierEnum accessModifier;
    ResultType::ResultTypeEnum resultType;
    QString text;
    QList<MethodModifier::MethodModifierEnum> params;
};
