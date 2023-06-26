#pragma once

#include "../Base/PrintOperatorUnit.cpp"

class CsharpPrintOperatorUnit : public PrintOperatorUnit {
public:
    explicit CsharpPrintOperatorUnit(const std::string &text) : textToPrint(text) {}

    std::string compile(unsigned int level = 0) const override {
        return generateShift(level + 1) + "Console.WriteLine(\"" + textToPrint + "\");\n";
    }

private:
    std::string textToPrint;
};
