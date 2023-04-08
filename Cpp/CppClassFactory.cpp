#pragma once
#include <QString>
#include <algorithm>
#include "../BaseFactories/BaseLazyClassFactory.cpp"
#include "CppMethodFactory.cpp"

class CppClassFactory: public BaseLazyClassFactory
{
public:
    CppClassFactory()
    {
        this->methodFactory = new CppMethodFactory();
    }

private:
    QString composeMethods() override
    {
        QString result;

        result = this->addTabsForMethods(this->methodFactory->getAll());
        result = this->removeExtraAccessModifiers(result);

        return result;
    }

    QString addTabsForMethods(QList<QString> methods) override
    {
        QString result;

        foreach (QString method, methods) {
            QTextStream stream(&method);

            bool isFirstString = true;
            while (!stream.atEnd()) {
                QString currentLine = stream.readLine();
                if (isFirstString) {    // access modifiers should not have tab
                    isFirstString = false;
                    result += currentLine + "\n";
                } else {
                    result += currentLine.prepend("    ") + "\n";
                }
            }
            result += "\n";
        }
        result.chop(1);

        return result;
    }

    QString removeExtraAccessModifiers(QString methods)
    {
        QVector<QString> modifiers = {"public", "protected", "private"};
        QString result;
        QTextStream stream(&methods);
        QString currentModifier;

        if(!stream.atEnd()) { // first modifier always satisfies condition is there are at least 1 method
            QString currentLine = stream.readLine();
            currentModifier = currentLine.left(currentLine.indexOf(':'));
            result += currentModifier + ":\n";
        }

        while(!stream.atEnd()) {
            QString currentLine = stream.readLine();
            int colonIndex = currentLine.indexOf(':');
            QString possibleModifier = currentLine.left(colonIndex);
            // check its modifier
            if (std::any_of(modifiers.begin(), modifiers.end(), [possibleModifier](const QString& modifier){
                return (possibleModifier == modifier);
            })) {
                if (currentModifier != possibleModifier) {
                    result += currentLine + "\n";
                    currentModifier = possibleModifier;
                }
                else {
                    continue;
                }
            }
            else {
                result += currentLine + "\n";
            }
        }

        return result;
    }
};
