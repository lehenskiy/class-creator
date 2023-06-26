# class-creator
Лабораторная работа #2 по предмету "Технология разработки программного обеспечения"

## ТЗ
Легенда: Реализована некоторая система, которая способна генерировать код на языке С++, причем, программы только определенного вида (пример кода прилагается) lab2.pdf.

Требуется реализовать подобную генерацию программ на С# и Java, путем  расширения возможностей предложенной реализации используя фабричные подходы (абстрактная фабрика). При реализации требуется добавить модификаторы классов и методов, которых нет в C++, но есть в C# (https://metanit.com/sharp/tutorial/3.2.php ) и Java (http://proglang.su/java/modifiers - до п.3.4, synchronized, transient, volatile можно не включать).

## Решение
1) Определяем абстрактные продукты(`ClassUnit`, `MethodUnit`, `PrintOperatorUnit`)
2) Наследуем от них конкретные продукты(`CppClassUnit`, `CppClassUnit`, `CppMethodUnit`, `CppPrintOperatorUnit`, `CsharpClassUnit`, `CsharpPrintOperatorUnit`, `JavaMethodUnit`, `JavaPrintOperatorUnit`)
3) Создаём интерфейс абстрактной фабрики для генерации программ `ProgrammFactory` и конкретные фабрики `ProgrammFactoryCpp`, `ProgrammFactoryCsharp` и `ProgrammFactoryJava`. Здесь можно заметить идею абстрактной фабрики - `ProgrammFactory` определяет интерфейс, следуя которому, мы можем создать семейство связанных объектов
4) Завязываем генерацию кода для различных реализаций на общий интерфейс(`ProgrammFactory` из прошлого пункта) - теперь мы можем полиморфно работать с ними, создавая одни и те же продукты(по своей сути, т.е. методы/классы/операторы вывода) из разных семейств.

## UML
![image](https://github.com/lehenskiy/class-creator/assets/50871152/e5c276d3-2434-4432-bff0-6784f5e47ba5)
