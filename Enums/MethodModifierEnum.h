#pragma once
#include <QObject>

class MethodModifier : public QObject // construction to convert Enum to string
{
Q_OBJECT
public:
    enum MethodModifierEnum {
        STATIC,
        CONST,
        FINAL,
        VIRTUAL,    // C++
        ABSTRACT,   // Java
    };
    Q_ENUM(MethodModifierEnum)
};
