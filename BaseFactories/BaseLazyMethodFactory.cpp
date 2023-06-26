#pragma once
#include <QString>
#include <QList>
#include <QVariant>
#include "../Support/MethodData.cpp"
#include <algorithm>

class BaseLazyMethodFactory
{
public:
    virtual void create(
        QString name,
        AccessModifier::AccessModifierEnum accessModifier,
        ResultType::ResultTypeEnum resultType,
        QString text,
        QList<MethodModifier::MethodModifierEnum> params
    )
    {
        if (!this->preparedMethods.contains(name) && !this->unpreparedMethods.contains(name)) {
            this->unpreparedMethods.insert(name, MethodData(accessModifier, resultType, text, params));
            }
        else { // should throw ExistingMethodAdditionException
            QString exceptionText = "Trying to add method with already existing name `" + name + "`!";
            throw std::exception(exceptionText.toUtf8());
        }
    }

    virtual QList<QString> getAll()
    {
        this->prepareUnpreparedMethods();

        return this->preparedMethods.values();
    }

    void remove(QString name)
    {
        if (this->preparedMethods.contains(name)) {
            this->preparedMethods.remove(name);
        }
        else if (this->unpreparedMethods.contains(name)) {
            this->unpreparedMethods.remove(name);
        }
    }

    void clear()
    {
        this->preparedMethods.clear();
        this->unpreparedMethods.clear();
    }

protected:
    QMap<QString, MethodData> unpreparedMethods;
    QMap<QString, QString> preparedMethods;

    virtual void prepareUnpreparedMethods()
    {
        foreach (QString name, this->unpreparedMethods.keys()) {
            this->prepareMethod(name, this->unpreparedMethods.value(name));
        }
    }

    virtual void prepareMethod(QString name, MethodData methodData)
    {
        QString result;

        result += this->composeDeclaration(
            name,
            methodData.getAccessModifier(),
            methodData.getResultType(),
            methodData.getParams()
        );
        result += this->composeBody(methodData.getText());
        result += this->composePostfix();

        this->preparedMethods.insert(name, result);
        this->unpreparedMethods.remove(name);
    }

    virtual QString composeDeclaration(
        QString name,
        AccessModifier::AccessModifierEnum accessModifier,
        ResultType::ResultTypeEnum resultType,
        QList<MethodModifier::MethodModifierEnum> params
    )
    {
        QString result;

        result += this->composeAccessModifier(accessModifier);
        result += this->composeResultType(resultType);
        result += this->composeModifiers(params);
        result = result.toLower().replace('_', ' ');

        result += name + "()\n{\n";

        return result;
    }

    virtual QString composeAccessModifier(AccessModifier::AccessModifierEnum accessModifier)
    {
        return QVariant::fromValue(accessModifier).toString() + " ";
    }

    virtual QString composeResultType(ResultType::ResultTypeEnum resultType)
    {
        return QVariant::fromValue(resultType).toString() + " ";
    }

    virtual QString composeModifiers(QList<MethodModifier::MethodModifierEnum> params)
    {
        QString result;

        foreach (MethodModifier::MethodModifierEnum param, params) {
            result += QVariant::fromValue(param).toString() + " ";
        }

        return result;
    }

    virtual QString composeBody(QString text)
    {
        QTextStream stream(&text);
        QString result;

        while (!stream.atEnd()) {
            result += stream.readLine().prepend("    ") + "\n"; // not \t because its 8 spaces
        }
        result.chop(1); // trim last \n
        result += (text == "" ? "" : "\n");

        return result;
    }

    virtual QString composePostfix()
    {
        return QString{"}"};
    }

    static void throwNoSuchEnumElement()
    {
        throw std::exception("No such element in enum!");
    }
};
