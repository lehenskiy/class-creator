# class-creator
Лабораторная работа #2 по предмету "Технология разработки программного обеспечения"

## ТЗ
Легенда: Реализована некоторая система, которая способна генерировать код на языке С++, причем, программы только определенного вида (пример кода прилагается) lab2.pdf.

Требуется реализовать подобную генерацию программ на С# и Java, путем  расширения возможностей предложенной реализации используя фабричные подходы (абстрактная фабрика). При реализации требуется добавить модификаторы классов и методов, которых нет в C++, но есть в C# (https://metanit.com/sharp/tutorial/3.2.php ) и Java (http://proglang.su/java/modifiers - до п.3.4, synchronized, transient, volatile можно не включать).

## Решение
Есть базовые классы `BaseLazyClassFactory` и `BaseLazyMethodFactory`(о *ленивости* написано [здесь](https://github.com/lehenskiy/class-creator/pull/1)), предоставляющие базовый функционал для расширения(все функции, которые может понадобиться переопределить дочерним классам, объявлены `virtual`). Так как соблюдается LSP мы можем работать с производными классами через интерфейс родительского класса. 
Перечисления(`Enums`) содержат все доступные опции(для языков C++, C#, Java) для модификаторов доступа, возвращаемых типов и дополнительных модификаторов методов.
Так как сравнивнение значений из разных Enum'ов было объявлено устаревшим(`Deprecated`), то дополнительные Enum'ы вводить не стал — проверяются конкретные модификаторы для классов.

### Отличия от примера реализации
Отличия от примера реализации(ссылка на которую была выложена в описании к лабораторной работе):
1) **Композиция**. Вместо того, чтобы предоставлять в фабрике классов возможность положить сущность, используем композицию, создаём фабрику методов внутри фабрики классов и предоставляем интерфейс для работы с первой. Зачем? В представленной реализации возможно создание методов вне классов, что, очевидно, не является использованием класса по его предназначению. Из минусов — теряется гибкость — нельзя создать класс внутри класса или класс внутри метода(не уверен, что есть во всех представленных языках), что однако можно легко решить, но так как задание не предусматривает такого рода конструкций, то было решено не делать этого.
2) Отказ от наследования класса `Unit` классами фабрик классов и методов. Я так понимаю, решение было спроектировано отчасти по паттерну `Composite`, но я посчитал это излишним(в силу предыдущего пункта), также это решение имеет свои недостатки. Во-первых, названия классов `ClassUnit`, `MethodUnit` и `PrintOperatorUnit`, наследующие `Unit` не отражают их сути. Во-вторых, последний класс должен по логике наследоваться от `MethodUnit`(если это метод для генерации методов, внутри которых вызов функции `printf()`, хотя гибкость здесь отсутствует - всё, что мы можем, - передать текст, который будет внутри printf(). Не самое лучшее решение), тогда и передача последнего `PrintOperatorUnit` в `MethodUnit` не будет нужна. Если же это класс для генерации текстов внутри функции, то смысла от наследования `Unit`'a ещё меньше - зачем ему методы `add()` и `generateShift()`? Всё, что он должен делать - добавлять текст в вызов `printf()`. В последнем случае смысл класса как такового не понятен - мы можем передать текст вида `printf("neededText")` в `method->add()` и избежать вызова дополнительного метода, который усложняет систему и не делает ничего особенного.

## Реализация паттернов
1) Abstract Factory — имеем классы `CppClassFactory`, `CsharpClassFactory`, `JavaClassFactory`, наследующие базовый класс `BaseLazyClassFactory` и предоставляющие общий интерфейс для генерации семейства связанных сущностей (класса и методов).
2) Lazy Load(был реализован по собственному желанию) — выносим генерацию строчек методов из `create()` в `get()`. Таким образом, на методы, которые не нужно будет получать(например, мы их добавили и удалили, или же добавили методы в класс, но сам класс так и не сгенерировали), не будет потрачено процессорное время. Звучит как over engineering, но это было сделано не в рамках оптимизации, а в образовательных целях. 
