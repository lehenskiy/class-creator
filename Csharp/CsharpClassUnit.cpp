#pragma once

#include "../Base/ClassUnit.cpp"

class CsharpClassUnit : public ClassUnit {
public:
    enum AccessModifier {
        PUBLIC,
        PROTECTED,
        PRIVATE,
        PRIVATE_PROTECTED,
        FILE,
        INTERNAL,
        PROTECTED_INTERNAL
    };
    const std::vector<std::string> ACCESS_MODIFIERS = {"public", "protected", "private", "private protected", "file",
                                                       "internal", "protected_internal"};

    explicit CsharpClassUnit(const std::string &name) : ClassUnit(name) {
        methods.resize(ACCESS_MODIFIERS.size());
    }

    void add(const std::shared_ptr<Unit> &unit, Flags flags) override {

        int accessModifier = PRIVATE;

        if (flags < ACCESS_MODIFIERS.size()) {
            accessModifier = flags;
        }

        methods[accessModifier].push_back(unit);
    }

    std::string compile(unsigned int level = 0) const override {
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
};
