#pragma once
#include <QMap>
#include <QString>
#include "BaseLazyMethodFactory.cpp"

class BaseLazyClassFactory
{
public:
    BaseLazyClassFactory()
    {
        this->methodFactory = new BaseLazyMethodFactory();
    }

    ~BaseLazyClassFactory()
    {
        delete this->methodFactory;
    }

    void setName(QString name)
    {
        this->className = name;
    };

    void addMethod(
        QString name,
        AccessModifier::AccessModifierEnum accessModifier = AccessModifier::PUBLIC,
        ResultType::ResultTypeEnum resultType = ResultType::VOID,
        QString text = "",
        QList<MethodModifier::MethodModifierEnum> params = {}
    )
    {
        this->methodFactory->create(name, accessModifier, resultType, text, params);
    };

    void removeMethod(QString name)
    {
        this->methodFactory->remove(name);
    }

    void clear()
    {
        this->className = "TestClass";
        this->methodFactory->clear();
    }

    void clearMethods()
    {
        this->methodFactory->clear();
    }

    virtual QString create()
    {
        QString result;
        result += this->composeClassStart() + "\n";
        result += this->composeMethods();
        result += this->composeClassEnd();

        return result;
    }

protected:
    QString className = "TestClass";
    BaseLazyMethodFactory *methodFactory;

    virtual QString composeClassStart()
    {
        QString result;
        result += "class " + this->className + "\n{";

        return result;
    }

    virtual QString composeMethods()
    {
        return addTabsForMethods(this->methodFactory->getAll());
    }

    virtual QString addTabsForMethods(QList<QString> methods) // should return QList<QString>
    {
        QString result;

        foreach (QString method, methods) {
            QTextStream stream(&method);

            while (!stream.atEnd()) {
                result += stream.readLine().prepend("    ") + "\n";
            }
            result += "\n";
        }
        result.chop(1);

        return result;
    }

    virtual QString composeClassEnd()
    {
        return QString("}\n");
    }
};
