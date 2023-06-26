#pragma once

#include "Base/Unit.cpp"

class PrintOperatorUnit : public Unit {
public:
    virtual std::string compile(unsigned int level = 0) const override {
        return generateShift(level) + "printf( \"" + textToPrint + "\" );\n";
    }

private:
    std::string textToPrint;
};
