#include <QCoreApplication>
#include <iostream>
#include "Base/ClassUnit.cpp"
#include "Base/MethodUnit.cpp"
#include "Base/PrintOperatorUnit.cpp"
#include "Base/Unit.cpp"
#include "Csharp/CsharpClassUnit.cpp"
#include "Csharp/CsharpPrintOperatorUnit.cpp"
#include "Java/JavaMethodUnit.cpp"
#include "Java/JavaPrintOperatorUnit.cpp"
#include "Cpp/CppClassUnit.cpp"
#include "Cpp/CppMethodUnit.cpp"
#include "Cpp/CppPrintOperatorUnit.cpp"

class ProgFactory {
public:
    virtual ~ProgFactory() {}

    virtual std::shared_ptr<ClassUnit> createClassUnit(const std::string &name) = 0;
    virtual std::shared_ptr<MethodUnit> createMethodUnit(const std::string &name, const std::string &returnType, int flags) = 0;
    virtual std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(const std::string &text) = 0;
};

class ProgFactoryCpp : public ProgFactory {
public:
    std::shared_ptr<ClassUnit> createClassUnit(const std::string &name) override {
        return std::make_shared<CppClassUnit>(name);
    }

    std::shared_ptr<MethodUnit> createMethodUnit(const std::string &name, const std::string &returnType, int flags) override {
        return std::make_shared<CppMethodUnit>(name, returnType, flags);
    }

    std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(const std::string &text) override {
        return std::make_shared<CppPrintOperatorUnit>(text);
    }
};

class ProgFactoryCsharp : public ProgFactory {
public:
    std::shared_ptr<ClassUnit> createClassUnit(const std::string &name) override {
        return std::make_shared<CsharpClassUnit>(name);
    }

    std::shared_ptr<MethodUnit> createMethodUnit(const std::string &name, const std::string &returnType, int flags) override {
        return std::make_shared<MethodUnit>(name, returnType, flags);
    }

    std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(const std::string &text) override {
        return std::make_shared<CsharpPrintOperatorUnit>(text);
    }
};

class ProgFactoryJava : public ProgFactory {
public:
    std::shared_ptr<ClassUnit> createClassUnit(const std::string &name) override {
        return std::make_shared<ClassUnit>(name);
    }

    std::shared_ptr<MethodUnit> createMethodUnit(const std::string &name, const std::string &returnType, int flags) override {
        return std::make_shared<JavaMethodUnit>(name, returnType, flags);
    }

    std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(const std::string &text) override {
        return std::make_shared<JavaPrintOperatorUnit>(text);
    }
};
