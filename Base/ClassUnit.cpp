#pragma once

#include <vector>
#include "Unit.cpp"

class ClassUnit : public Unit {
public:
    enum AccessModifier {
        PUBLIC,
        PROTECTED,
        PRIVATE
    };
    const std::vector<std::string> ACCESS_MODIFIERS = {"public", "protected", "private"};

    explicit ClassUnit(const std::string &name) : className(name) {
        methods.resize(ACCESS_MODIFIERS.size());
    }

    void add(const std::shared_ptr<Unit> &unit, Flags flags) override {
        int accessModifier = PRIVATE;

        if (flags < ACCESS_MODIFIERS.size()) {
            accessModifier = flags;
        }

        methods[accessModifier].push_back(unit);
    }

    virtual std::string compile(unsigned int level = 0) const override {
        std::string result = "class " + className + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            if (methods[i].empty()) {
                continue;
            }

            for (const auto &method: methods[i]) {
                result += ACCESS_MODIFIERS[i] + method->compile(level + 1) + "\n";
            }
        }

        result += generateShift(level) + "};\n";

        return result;
    }

    using Method = std::vector<std::shared_ptr<Unit>>;

protected:
    std::string className;
    std::vector<Method> methods;
};
