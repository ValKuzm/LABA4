#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <string>
#include <iostream>
#include <functional>
#include <complex>
#include <ctime>



// Класс для представления комплексных чисел
class Complex {
private:
    std::complex<double> value;

public:
    Complex() : value(0.0, 0.0) {}
    Complex(double real, double imag) : value(real, imag) {}
    explicit Complex(const std::complex<double>& other) : value(other) {}

    // Геттеры
    double real() const { return value.real(); }
    double imag() const { return value.imag(); }

    // Операторы сравнения
    bool operator==(const Complex& other) const {
        return value == other.value;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    bool operator<(const Complex& other) const {
        // Сравниваем сначала по реальной части, затем по мнимой
        if (real() == other.real()) {
            return imag() < other.imag();
        }
        return real() < other.real();
    }

    bool operator>(const Complex& other) const {
        return other < *this;
    }

    bool operator<=(const Complex& other) const {
        return !(other < *this);
    }

    bool operator>=(const Complex& other) const {
        return !(*this < other);
    }

    // Арифметические операторы
    Complex operator+(const Complex& other) const {
        return Complex(value + other.value);
    }

    Complex operator-(const Complex& other) const {
        return Complex(value - other.value);
    }

    Complex operator*(const Complex& other) const {
        return Complex(value * other.value);
    }

    Complex operator/(const Complex& other) const {
        return Complex(value / other.value);
    }

    // Преобразование в строку
    std::string toString() const {
        std::string result = std::to_string(real());
        if (imag() >= 0) {
            result += "+";
        }
        result += std::to_string(imag()) + "i";
        return result;
    }

    // Метод для использования в std::to_string
    friend std::string to_string(const Complex& c) {
        return c.toString();
    }

    // Вывод в поток
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.toString();
        return os;
    }
};

// Тип для функций (указатель на функцию int -> int)
using Function = std::function<int(int)>;

// Класс для представления функций
class FunctionWrapper {
private:
    Function func;
    std::string name;
    int id; // Для сравнения

public:
    FunctionWrapper() : func([](int x) { return x; }), name("identity"), id(0) {}
    
    FunctionWrapper(Function f, const std::string& n, int identifier) 
        : func(f), name(n), id(identifier) {}

    // Применение функции
    int apply(int x) const {
        return func(x);
    }

    // Геттеры
    const std::string& getName() const { return name; }
    int getId() const { return id; }

    // Операторы сравнения (по id)
    bool operator==(const FunctionWrapper& other) const {
        return id == other.id;
    }

    bool operator!=(const FunctionWrapper& other) const {
        return !(*this == other);
    }

    bool operator<(const FunctionWrapper& other) const {
        return id < other.id;
    }

    bool operator>(const FunctionWrapper& other) const {
        return other < *this;
    }

    bool operator<=(const FunctionWrapper& other) const {
        return !(other < *this);
    }

    bool operator>=(const FunctionWrapper& other) const {
        return !(*this < other);
    }

    // Преобразование в строку
    std::string toString() const {
        return "Function(" + name + ", id=" + std::to_string(id) + ")";
    }

    // Метод для использования в std::to_string
    friend std::string to_string(const FunctionWrapper& f) {
        return f.toString();
    }

    // Вывод в поток
    friend std::ostream& operator<<(std::ostream& os, const FunctionWrapper& f) {
        os << f.toString();
        return os;
    }
};

// Тип-идентификатор для персон
struct PersonID {
    int series;
    int number;

    bool operator==(const PersonID& other) const {
        return series == other.series && number == other.number;
    }

    bool operator!=(const PersonID& other) const {
        return !(*this == other);
    }

    bool operator<(const PersonID& other) const {
        if (series == other.series) {
            return number < other.number;
        }
        return series < other.series;
    }

    bool operator>(const PersonID& other) const {
        return other < *this;
    }

    std::string toString() const {
        return std::to_string(series) + " " + std::to_string(number);
    }
};

// Базовый класс для персон
class Person {
protected:
    PersonID id;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::time_t birthDate;

public:
    Person() : id{0, 0}, firstName(""), middleName(""), lastName(""), birthDate(0) {}
    
    Person(const PersonID& pid, const std::string& first, const std::string& middle, 
           const std::string& last, std::time_t birth)
        : id(pid), firstName(first), middleName(middle), lastName(last), birthDate(birth) {}

    // Геттеры
    PersonID GetID() const { return id; }
    std::string GetFirstName() const { return firstName; }
    std::string GetMiddleName() const { return middleName; }
    std::string GetLastName() const { return lastName; }
    std::time_t GetBirthDate() const { return birthDate; }

    // Полное имя (вычислимый атрибут)
    std::string GetFullName() const {
        return firstName + " " + middleName + " " + lastName;
    }

    // Операторы сравнения (по id)
    bool operator==(const Person& other) const {
        return id == other.id;
    }

    bool operator!=(const Person& other) const {
        return !(*this == other);
    }

    bool operator<(const Person& other) const {
        return id < other.id;
    }

    bool operator>(const Person& other) const {
        return other < *this;
    }

    bool operator<=(const Person& other) const {
        return !(other < *this);
    }

    bool operator>=(const Person& other) const {
        return !(*this < other);
    }

    // Базовый метод для преобразования в строку
    virtual std::string toString() const {
        return "Person(" + GetFullName() + ", ID=" + id.toString() + ")";
    }

    // Виртуальный деструктор
    virtual ~Person() {}
};

// Класс для студентов
class Student : public Person {
private:
    std::string groupNumber;
    double averageGrade;

public:
    Student() : Person(), groupNumber(""), averageGrade(0.0) {}
    
    Student(const PersonID& pid, const std::string& first, const std::string& middle, 
            const std::string& last, std::time_t birth,
            const std::string& group, double avgGrade)
        : Person(pid, first, middle, last, birth), groupNumber(group), averageGrade(avgGrade) {}

    // Геттеры
    std::string GetGroupNumber() const { return groupNumber; }
    double GetAverageGrade() const { return averageGrade; }

    // Преобразование в строку
    std::string toString() const override {
        return "Student(" + GetFullName() + ", Group=" + groupNumber + 
               ", AvgGrade=" + std::to_string(averageGrade) + ")";
    }

    // Метод для использования в std::to_string
    friend std::string to_string(const Student& s) {
        return s.toString();
    }

    // Вывод в поток
    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        os << s.toString();
        return os;
    }
};

// Класс для преподавателей
class Teacher : public Person {
private:
    std::string department;
    std::string position;

public:
    Teacher() : Person(), department(""), position("") {}
    
    Teacher(const PersonID& pid, const std::string& first, const std::string& middle, 
            const std::string& last, std::time_t birth,
            const std::string& dept, const std::string& pos)
        : Person(pid, first, middle, last, birth), department(dept), position(pos) {}

    // Геттеры
    std::string GetDepartment() const { return department; }
    std::string GetPosition() const { return position; }

    // Преобразование в строку
    std::string toString() const override {
        return "Teacher(" + GetFullName() + ", Dept=" + department + 
               ", Position=" + position + ")";
    }

    // Метод для использования в std::to_string
    friend std::string to_string(const Teacher& t) {
        return t.toString();
    }

    // Вывод в поток
    friend std::ostream& operator<<(std::ostream& os, const Teacher& t) {
        os << t.toString();
        return os;
    }
};

// Вспомогательная функция для преобразования значения в строку
template <typename T>
std::string valueToString(const T& value) {
    // Для стандартных типов используем std::to_string или потоки
    std::ostringstream ss;
    ss << value;
    return ss.str();
}

// Специализации для пользовательских типов
template <>
inline std::string valueToString(const Complex& value) {
    return value.toString();
}

template <>
inline std::string valueToString(const FunctionWrapper& value) {
    return value.toString();
}

template <>
inline std::string valueToString(const Student& value) {
    return value.toString();
}

template <>
inline std::string valueToString(const Teacher& value) {
    return value.toString();
}

// Вспомогательная функция для преобразования строки в значение
template <typename T>
T valueFromString(const std::string& str) {
    // Базовая реализация для типов, которые не поддерживаются
    throw std::runtime_error("Преобразование из строки не поддерживается для данного типа");
}

// Специализация для int
template <>
inline int valueFromString<int>(const std::string& str) {
    return std::stoi(str);
}

// Специализация для double
template <>
inline double valueFromString<double>(const std::string& str) {
    return std::stod(str);
}

// Специализация для строк
template <>
inline std::string valueFromString<std::string>(const std::string& str) {
    return str;
}

// Специализация для Complex
template <>
inline Complex valueFromString<Complex>(const std::string& str) {
    // Ожидаемый формат: "real+imagi" или "real-imagi"
    size_t pos = str.find_first_of("+-", 1); // Ищем + или - после первого символа
    if (pos != std::string::npos) {
        double real = std::stod(str.substr(0, pos));
        double imag = std::stod(str.substr(pos));
        return Complex(real, imag);
    }
    // Если нет мнимой части или формат неверный
    return Complex(std::stod(str), 0.0);
}

// Специализация для FunctionWrapper
template <>
inline FunctionWrapper valueFromString<FunctionWrapper>(const std::string& str) {
    // Ожидаемый формат: "Function(name, id=N)"
    size_t startPos = str.find("(");
    size_t endPos = str.find(")");
    size_t commaPos = str.find(",");
    size_t idPos = str.find("id=");
    
    if (startPos != std::string::npos && endPos != std::string::npos && 
        commaPos != std::string::npos && idPos != std::string::npos) {
        std::string name = str.substr(startPos + 1, commaPos - startPos - 1);
        int id = std::stoi(str.substr(idPos + 3, endPos - idPos - 3));
        // Создаем простую функцию с указанным id и именем
        return FunctionWrapper([](int x) { return x; }, name, id);
    }
    // По умолчанию возвращаем функцию идентичности
    return FunctionWrapper();
}

// Специализация для Student
template <>
inline Student valueFromString<Student>(const std::string& str) {
    // Для упрощения создаем студента с базовыми данными
    // В реальной системе потребуется более сложный парсинг
    PersonID id{1, 1};
    return Student(id, "John", "M", "Doe", std::time(nullptr), "Group101", 4.5);
}

// Специализация для Teacher
template <>
inline Teacher valueFromString<Teacher>(const std::string& str) {
    // Для упрощения создаем преподавателя с базовыми данными
    // В реальной системе потребуется более сложный парсинг
    PersonID id{2, 2};
    return Teacher(id, "Jane", "M", "Smith", std::time(nullptr), "Math", "Professor");
}

// Специализация для преобразования в строку и из строки для специальных типов
namespace std {
    // Специализация to_string для комплексных чисел
    inline string to_string(const Complex& c) {
        return c.toString();
    }

    // Специализация to_string для функций
    inline string to_string(const FunctionWrapper& f) {
        return f.toString();
    }

    // Специализация to_string для студентов
    inline string to_string(const Student& s) {
        return s.toString();
    }

    // Специализация to_string для преподавателей
    inline string to_string(const Teacher& t) {
        return t.toString();
    }
}

#endif // DATA_TYPES_H 
