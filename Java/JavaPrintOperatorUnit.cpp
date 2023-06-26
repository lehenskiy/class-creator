#pragma once

#include "../Base/PrintOperatorUnit.cpp"

class JavaPrintOperatorUnit : public PrintOperatorUnit {
public:
    explicit JavaPrintOperatorUnit(const std::string &text) : textToPrint(text) {}

    std::string compile(unsigned int level = 0) const override {
        return generateShift(level + 1) + "System.out.println(\"" + textToPrint + "\");\n";
    }

private:
    std::string textToPrint;
};
