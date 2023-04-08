#pragma once
#include <QObject>

class ResultType : public QObject // construction to convert Enum to string
{
Q_OBJECT
public:
    enum ResultTypeEnum {
        VOID,
        INT,
        BOOL,
        FLOAT,
        STRING,
    };
    Q_ENUM(ResultTypeEnum)
};
