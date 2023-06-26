#include <iostream>
#include "AbstractFactory.cpp"

void createAndCompileClass(const std::shared_ptr<ProgFactory>& factory) {
    std::shared_ptr<ClassUnit> classUnit = factory->createClassUnit("testClass");
    std::shared_ptr<MethodUnit> methodUnit1 = factory->createMethodUnit("function1", "void", 1);
    std::shared_ptr<MethodUnit> methodUnit2 = factory->createMethodUnit("function2", "void", 0);
    std::shared_ptr<MethodUnit> methodUnit3 = factory->createMethodUnit("function3", "void", 0);
    std::shared_ptr<PrintOperatorUnit> printOperatorUnit = factory->createPrintOperatorUnit(R"(Hello, world!\n)");

    methodUnit2->add(printOperatorUnit);

    classUnit->add(methodUnit1, ClassUnit::AccessModifier::PUBLIC);
    classUnit->add(methodUnit2, ClassUnit::AccessModifier::PROTECTED);
    classUnit->add(methodUnit3, ClassUnit::AccessModifier::PRIVATE);

    std::cout << classUnit->compile() << std::endl;
}

int main() {

    std::shared_ptr<ProgFactory> factoryCpp = std::make_shared<ProgFactoryCpp>();
    std::shared_ptr<ProgFactory> factoryCsharp = std::make_shared<ProgFactoryCsharp>();
    std::shared_ptr<ProgFactory> factoryJava = std::make_shared<ProgFactoryJava>();

    std::cout << "C++ class:" << std::endl << std::endl;
    createAndCompileClass(factoryCpp);

    std::cout << "C# class:" << std::endl << std::endl;
    createAndCompileClass(factoryCsharp);

    std::cout << "Java class:" << std::endl << std::endl;
    createAndCompileClass(factoryJava);

    return 0;
}
