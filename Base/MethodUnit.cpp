#pragma once

#include <vector>
#include "Unit.cpp"

class MethodUnit : public Unit {
public:
    enum Modifier {
        STATIC,
        CONST,
        FINAL
    };

    MethodUnit(const std::string &name, const std::string &returnType, Flags flags) : methodName(name),
                                                                                      methodReturnType(returnType),
                                                                                      methodFlags(flags) {}

    void add(const std::shared_ptr<Unit> &unit, Flags /* methodFlags */ = 0) override {
        methodBody.push_back(unit);
    }

    virtual std::string compile(unsigned int level = 0) const override {

        std::string result = generateShift(level);

        if (methodFlags & STATIC) { // pre definition modifiers
            result += "static ";
        }
        if (methodFlags & FINAL) {
            result += "final ";
        }
        result += methodReturnType + " ";

        result += methodName + "()";

        if (methodFlags & CONST) { // post definition modifier
            result += " const";
        }

        result += " {\n";

        for (const std::shared_ptr<Unit> &b: methodBody) {
            result += b->compile(level + 1);
        }

        result += generateShift(level) + "}\n";

        return result;
    }

protected:
    Flags methodFlags;

private:
    std::string methodName;
    std::string methodReturnType;
    std::vector<std::shared_ptr<Unit>> methodBody;
};
