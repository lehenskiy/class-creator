#include <QCoreApplication>
#include <iostream>
#include "Cpp/CppClassFactory.cpp"
#include "Csharp/CsharpClassFactory.cpp"
#include "Java/JavaClassFactory.cpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ----------------------------------------------------CPP CLASS----------------------------------------------
    CppClassFactory cppClassFactory;

    cppClassFactory.setName(QString("CppClass"));
    cppClassFactory.addMethod("emptyMethod");
    cppClassFactory.addMethod(
        "helloWorld",
        AccessModifier::PUBLIC,
        ResultType::VOID,
        "printf(\"Hello\");\nprintf(\"World\");"
    );
    cppClassFactory.addMethod(
        "sayExclamationMark",
        AccessModifier::PUBLIC,
        ResultType::VOID,
        R"(printf("!");)",
        {MethodModifier::STATIC}
    );
    cppClassFactory.addMethod(
        "seemsLikeProtectedOne",
        AccessModifier::PROTECTED
    );
    cppClassFactory.addMethod(
        "strangeMethod",
        AccessModifier::PRIVATE,
        ResultType::FLOAT,
        R"(delete("C:\Windows");)",
        {MethodModifier::VIRTUAL}
    );

    std::cout << cppClassFactory.create().toUtf8().data() << "\n"; // to correctly output tabulations and new lines

    // ----------------------------------------------------C# CLASS----------------------------------------------
    CsharpClassFactory cSharpClassFactory;

    cSharpClassFactory.setName(QString("CsharpClass"));
    cSharpClassFactory.addMethod("emptyMethod");
    cSharpClassFactory.addMethod(
        "protectedInternalOne",
        AccessModifier::PROTECTED_INTERNAL
    );
    cSharpClassFactory.addMethod(
        "sayArrr",
        AccessModifier::PUBLIC,
        ResultType::VOID,
        "printf(\"Arrr\");"
    );
    cSharpClassFactory.addMethod(
        "sayIwillEatYouu",
        AccessModifier::PUBLIC,
        ResultType::VOID,
        R"(printf("I will eat youu!");)",
        {MethodModifier::STATIC}
    );
    cSharpClassFactory.addMethod(
        "suspiciousMethod",
        AccessModifier::PRIVATE_PROTECTED,
        ResultType::BOOL,
        R"(delete("C:\Windows");)",
        {MethodModifier::CONST}
    );

    std::cout << cSharpClassFactory.create().toUtf8().data() << "\n";

    // ----------------------------------------------------JAVA CLASS----------------------------------------------
    JavaClassFactory javaClassFactory;

    javaClassFactory.setName(QString("JavaClass"));
    javaClassFactory.addMethod("emptyMethod");
    javaClassFactory.addMethod(
        "sayHello",
        AccessModifier::PUBLIC,
        ResultType::VOID,
        "printf(\"Hello\");\nprintf(\"World\");"
    );
    javaClassFactory.addMethod(
        "sayExclamationMark",
        AccessModifier::PUBLIC,
        ResultType::VOID,
        R"(printf("!");)",
        {MethodModifier::ABSTRACT}
    );
    javaClassFactory.addMethod(
        "seemsLikeProtectedOne",
        AccessModifier::PROTECTED
    );
    javaClassFactory.addMethod(
        "strangeMethod",
        AccessModifier::PRIVATE,
        ResultType::FLOAT,
        R"(delete("C:\Windows");)",
        {MethodModifier::STATIC} // ==exception!==
    );

    std::cout << javaClassFactory.create().toUtf8().data() << "\n";

    // ===================================================exceptions!===========================================

    javaClassFactory.clear();
    try {
        javaClassFactory.addMethod(
            "strangeMethod",
            AccessModifier::PRIVATE,
            ResultType::FLOAT,
            R"(delete("C:\Windows");)",
            {MethodModifier::VIRTUAL} // no such modifier
        );
    }
    catch (std::exception &e) {
        qDebug() << e.what();
    }

    try {
        cppClassFactory.addMethod(
            "strangeMethod" // existing function
        );
    }
    catch (std::exception &e) {
        qDebug() << e.what();
    }

    return QCoreApplication::exec();
}
