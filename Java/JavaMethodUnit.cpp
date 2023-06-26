#include "../Base/MethodUnit.cpp"

class JavaMethodUnit : public MethodUnit {
public:
    enum Modifier {
        STATIC = 1,
        CONST = 1 << 1,
        FINAL = 1 << 2,
        ABSTRACT = 1 << 3,
    };

    explicit JavaMethodUnit(const std::string &name, const std::string &returnType, Flags flags)
            : MethodUnit(name, returnType, flags) {}

    std::string compile(unsigned int level = 0) const override {

        std::string result = generateShift(level);

        if (methodFlags & ABSTRACT) {
            result += "abstract ";
        }

        result += MethodUnit::compile(level);

        return result;
    }
};
