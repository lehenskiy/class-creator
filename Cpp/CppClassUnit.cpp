#pragma once

#include "../Base/ClassUnit.cpp"

class CppClassUnit : public ClassUnit {
public:
    explicit CppClassUnit(const std::string &name) : ClassUnit(name) {} // explicit constructor declaration

    std::string compile(unsigned int level = 0) const override {
        std::string result = generateShift(level) + "class " + className + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            if (methods[i].empty()) {
                continue;
            }

            result += ACCESS_MODIFIERS[i] + ":\n";
            for (const auto &method: methods[i]) {
                result += method->compile(level + 1) + "\n";
            }
        }

        result += generateShift(level) + "};\n";

        return result;
    }
};
