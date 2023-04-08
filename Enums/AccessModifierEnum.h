#pragma once
#include <QObject>

class AccessModifier : public QObject // construction to convert Enum to string
{
Q_OBJECT
public:
    enum AccessModifierEnum {
        PUBLIC, // C++, Java
        PROTECTED,
        PRIVATE,
        PRIVATE_PROTECTED,  // C#
        FILE,
        INTERNAL,
        PROTECTED_INTERNAL,
    };
    Q_ENUM(AccessModifierEnum)
};
