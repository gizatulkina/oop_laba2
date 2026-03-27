#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

// Класс Point
class Point
{
private:
    int x;
    int y;

public:
    // Конструктор без параметров
    Point()
    {
        x = 0;
        y = 0;
        cout << "Конструктор без параметров вызван" << endl;
    }

    // Конструктор с параметрами
    Point(int x1, int y2)
    {
        x = x1;
        y = y2;
        cout << "Конструктор с параметрами вызван: (" << x << ", " << y << ")" << endl;
    }

    // Конструктор копирования
    Point(const Point &other)
    {
        x = other.x;
        y = other.y;
        cout << "Конструктор копирования вызван: (" << x << ", " << y << ")" << endl;
    }

    // Деструктор
    ~Point()
    {
        cout << "Деструктор вызван для точки (" << x << ", " << y << ")" << endl;
    }

    // Методы доступа
    void setX(int x1)
    {
        x = x1;
        cout << "Установлен x = " << x << endl;
    }

    void setY(int y2)
    {
        y = y2;
        cout << "Установлен y = " << y << endl;
    }

    int getX() const { return x; }
    int getY() const { return y; }

    // Метод для вывода информации
    void print() const
    {
        cout << "Точка: (" << x << ", " << y << ")" << endl;
    }
};

// Класс ColoredPoint (Наследник)
class ColoredPoint : public Point
{
private:
    string color;

public:
    // Конструктор без параметров
    ColoredPoint() : Point()
    {
        color = "черный";
        cout << "Конструктор без параметров вызван, цвет: " << color << endl;
    }

    // Конструктор с параметрами
    ColoredPoint(int x, int y, string col) : Point(x, y)
    {
        color = col;
        cout << "Конструктор с параметрами вызван, цвет: " << color << endl;
    }

    // Конструктор копирования
    ColoredPoint(const ColoredPoint &other) : Point(other)
    {
        color = other.color;
        cout << "Конструктор копирования вызван, цвет: " << color << endl;
    }

    // Деструктор
    ~ColoredPoint()
    {
        cout << "Деструктор вызван для точки цвета " << color << endl;
    }

    // Метод для установки цвета
    void setColor(string col)
    {
        color = col;
        cout << "Установлен цвет: " << color << endl;
    }

    string getColor() const
    {
        return color;
    }

    // Переопределение метода print
    void print() const
    {
        cout << "Цветная точка: (" << getX() << ", " << getY() << ") цвет: " << color << endl;
    }
};

// Класс для демонстрации композиции
class Line
{
private:
    Point start; // Объект класса Point
    Point *end;  // Указатель на объект класса Point

public:
    // Конструктор с параметрами (использует список инициализации)
    Line(int x1, int y1, int x2, int y2) : start(x1, y1)
    {
        end = new Point(x2, y2);
        cout << "Конструктор с параметрами вызван" << endl;
    }

    // Конструктор копирования
    Line(const Line &other) : start(other.start)
    {
        end = new Point(*(other.end));
        cout << "Конструктор копирования вызван" << endl;
    }

    // Деструктор
    ~Line()
    {
        delete end;
        cout << "Деструктор вызван" << endl;
    }

    void moveStart(int dx, int dy)
    {
        start.setX(start.getX() + dx);
        start.setY(start.getY() + dy);
        cout << "Начальная точка перемещена" << endl;
    }

    void moveEnd(int dx, int dy)
    {
        end->setX(end->getX() + dx);
        end->setY(end->getY() + dy);
        cout << "Конечная точка перемещена" << endl;
    }
};

//  Функции для демонстрации передачи объектов
void funcByValue(Point obj)
{
    cout << "Внутри funcByValue" << endl;
    obj.print();
    cout << "Выход из funcByValue" << endl;
}

void funcByPointer(Point *obj)
{
    cout << "Внутри funcByPointer" << endl;
    obj->print();
    cout << "Выход из funcByPointer" << endl;
}

void funcByReference(Point &obj)
{
    cout << "Внутри funcByReference" << endl;
    obj.print();
    cout << "Выход из funcByReference" << endl;
}

//  Функции для возврата объектов
Point createStaticPoint()
{
    cout << "Внутри createStaticPoint" << endl;
    Point p(10, 20);
    cout << "Возврат из createStaticPoint" << endl;
    return p;
}

Point *createDynamicPoint()
{
    cout << "Внутри createDynamicPoint" << endl;
    Point *p = new Point(30, 40);
    cout << "Возврат из createDynamicPoint" << endl;
    return p;
}

//  Главная функция
int main()
{
    // Установка кодировки для русского языка в Windows
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "1. Создание статических объектов" << endl;
    Point p1;       // Конструктор без параметров
    Point p2(5, 7); // Конструктор с параметрами
    Point p3 = p2;  // Конструктор копирования

    cout << endl
         << "p1: ";
    p1.print();
    cout << "p2: ";
    p2.print();
    cout << "p3 (копия p2): ";
    p3.print();
    cout << endl;

    cout << "2. Создание динамических объектов" << endl;
    Point *p4 = new Point(); // Динамическое создание
    Point *p5 = new Point(15, 25);

    cout << "p4: ";
    p4->print();
    cout << "p5: ";
    p5->print();

    delete p4;
    delete p5;
    cout << endl;

    cout << "3. Работа с классами-наследниками" << endl;
    ColoredPoint cp1;
    ColoredPoint cp2(10, 20, "красный");
    ColoredPoint cp3 = cp2;

    cout << endl;
    cp1.print();
    cp2.print();
    cp3.print();
    cout << endl;

    cout << "4. Переопределение методов" << endl;
    Point *basePtr = &cp2; // Указатель на предка
    ColoredPoint *derivedPtr = &cp2;

    cout << "Вызов print() через указатель на Point: ";
    basePtr->print(); // Вызов метода Point
    cout << "Вызов print() через указатель на ColoredPoint: ";
    derivedPtr->print(); // Вызов переопределенного метода
    cout << endl;

    // 5. Композиция объектов
    cout << "5. Композиция объектов" << endl;
    Line line1(0, 0, 100, 100);
    line1.moveStart(10, 10);
    ;
    cout << endl;

    // 6. Присваивание и копирование
    cout << "6. Присваивание объектов" << endl;
    Point pointA(1, 1);
    Point pointB(2, 2);

    cout << "До присваивания:" << endl;
    cout << "pointA: ";
    pointA.print();
    cout << "pointB: ";
    pointB.print();

    pointB = pointA; // Присваивание

    cout << "После присваивания pointB = pointA:" << endl;
    cout << "pointA: ";
    pointA.print();
    cout << "pointB: ";
    pointB.print();

    pointA.setX(100); // Изменяем pointA
    cout << "После изменения pointA:" << endl;
    cout << "pointA: ";
    pointA.print();
    cout << "pointB: ";
    pointB.print();
    cout << endl;

    cout << "7. Копирование указателей " << endl;
    Point *ptrA = new Point(50, 60);
    Point *ptrB = ptrA; // Копирование указателя

    cout << "ptrA указывает на: ";
    ptrA->print();
    cout << "ptrB указывает на: ";
    ptrB->print();

    ptrA->setX(999);
    cout << "После изменения через ptrA:" << endl;
    cout << "ptrA указывает на: ";
    ptrA->print();
    cout << "ptrB указывает на: ";
    ptrB->print();

    delete ptrA; // Удаляем один раз
    ptrB = nullptr;
    cout << endl;

    cout << "8. Передача объектов в функции" << endl;
    Point testPoint(100, 200);

    cout << "Вызов funcByValue:" << endl;
    funcByValue(testPoint);

    cout << "Вызов funcByPointer:" << endl;
    funcByPointer(&testPoint);

    cout << "Вызов funcByReference:" << endl;
    funcByReference(testPoint);
    cout << endl;

    cout << "9. Возврат объектов из функций" << endl;

    cout << "Получение статического объекта:" << endl;
    Point returnedPoint = createStaticPoint();
    returnedPoint.print();

    cout << endl
         << "Получение динамического объекта:" << endl;
    Point *dynamicPoint = createDynamicPoint();
    dynamicPoint->print();
    delete dynamicPoint;
    cout << endl;

    cout << "10. Уничтожение объектов" << endl;
    cout << "Статические объекты удаляются автоматически при выходе из main" << endl;

    return 0;
}