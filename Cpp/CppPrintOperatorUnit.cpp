#pragma once

#include "../Base/PrintOperatorUnit.cpp"

class CppPrintOperatorUnit : public PrintOperatorUnit {
public:
    explicit CppPrintOperatorUnit(const std::string &text) : textToPrint(text) {}

    std::string compile(unsigned int level = 0) const override {
        return generateShift(level+1) + "printf(\"" + textToPrint + "\");\n";
    }

private:
    std::string textToPrint;
};
