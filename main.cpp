#include <iostream>
#include <string>
#include <functional>
#include <limits>
#include <random>
#include <memory>
#include <ctime>
#include "../include/binary_search_tree.h"
#include "../include/binary_heap.h"
#include "../include/binary_heap_wrapper.h"
#include "../include/data_types.h"
#include <io.h>
#include <fcntl.h>
#include <Windows.h>

// Тип для хранения указателя на любое из поддерживаемых деревьев/куч
enum class DataType {
    Integer
};

enum class DataStructure {
    BinarySearchTree,
    BinaryHeap
};

// Абстрактный класс для унифицированного доступа к дереву
class AbstractTreeWrapper {
public:
    virtual ~AbstractTreeWrapper() {}
    
    virtual void insert(const std::string& valueStr) = 0;
    virtual bool remove(const std::string& valueStr) = 0;
    virtual bool search(const std::string& valueStr) = 0;
    virtual void printTree() const = 0;
    virtual size_t getSize() const = 0;
    virtual void clear() = 0;
    virtual void balance() = 0;
    virtual std::string toString() const = 0;
    virtual std::shared_ptr<AbstractTreeWrapper> map(const std::string& multiplierStr) const = 0;
    virtual std::string reduce(const std::string& initialValueStr) const = 0;
    virtual std::shared_ptr<AbstractTreeWrapper> where(int filterType, const std::string& valueStr) const = 0;
    virtual std::vector<std::string> getValuesByTraversal(TraversalType type) const = 0;
    virtual std::shared_ptr<AbstractTreeWrapper> extractSubtree(const std::string& valueStr) = 0;
    virtual bool containsSubtree(const AbstractTreeWrapper& subtree) const = 0;
    virtual void fillWithRandomValues(int count, const std::string& minStr, const std::string& maxStr) = 0;
};

// Шаблонный класс обертки для конкретного дерева
template <typename T>
class TreeWrapper : public AbstractTreeWrapper {
private:
    BinarySearchTree<T> tree;
    
    // Преобразование строки в значение типа T
    T parseValue(const std::string& valueStr) const {
        return valueFromString<T>(valueStr);
    }
    
public:
    TreeWrapper() : tree() {}
    
    void insert(const std::string& valueStr) override {
        try {
            T value = parseValue(valueStr);
            tree.insert(value);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при вставке: " << e.what() << std::endl;
        }
    }
    
    bool remove(const std::string& valueStr) override {
        try {
            T value = parseValue(valueStr);
            return tree.remove(value);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при удалении: " << e.what() << std::endl;
            return false;
        }
    }
    
    bool search(const std::string& valueStr) override {
        try {
            T value = parseValue(valueStr);
            return tree.search(value);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при поиске: " << e.what() << std::endl;
            return false;
        }
    }
    
    void printTree() const override {
        tree.printTree();
    }
    
    size_t getSize() const override {
        return tree.getSize();
    }
    
    void clear() override {
        tree.clear();
    }
    
    void balance() override {
        tree.balance();
    }
    
    std::string toString() const override {
        return tree.toString();
    }
    
    std::shared_ptr<AbstractTreeWrapper> map(const std::string& multiplierStr) const override {
        try {
            // По умолчанию просто возвращаем копию дерева
            auto result = std::make_shared<TreeWrapper<T>>();
            result->tree = tree;
            return result;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при выполнении map: " << e.what() << std::endl;
            return std::make_shared<TreeWrapper<T>>();
        }
    }
    
    std::string reduce(const std::string& initialValueStr) const override {
        try {
            // По умолчанию возвращаем "не поддерживается"
            return "Операция reduce не поддерживается для данного типа";
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при выполнении reduce: " << e.what() << std::endl;
            return "Ошибка при выполнении reduce";
        }
    }
    
    std::shared_ptr<AbstractTreeWrapper> where(int filterType, const std::string& valueStr) const override {
        try {
            // По умолчанию просто возвращаем копию дерева
            auto result = std::make_shared<TreeWrapper<T>>();
            result->tree = tree;
            return result;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при выполнении where: " << e.what() << std::endl;
            return std::make_shared<TreeWrapper<T>>();
        }
    }
    
    std::vector<std::string> getValuesByTraversal(TraversalType type) const override {
        std::vector<std::string> result;
        auto values = tree.getValuesByTraversal(type);
        for (const auto& value : values) {
            result.push_back(valueToString(value));
        }
        return result;
    }
    
    std::shared_ptr<AbstractTreeWrapper> extractSubtree(const std::string& valueStr) override {
        try {
            T value = parseValue(valueStr);
            auto subtree = tree.extractSubtree(value);
            
            auto result = std::make_shared<TreeWrapper<T>>();
            result->tree = subtree;
            return result;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при извлечении поддерева: " << e.what() << std::endl;
            return std::make_shared<TreeWrapper<T>>();
        }
    }
    
    bool containsSubtree(const AbstractTreeWrapper& subtree) const override {
        try {
            // Проверяем, что subtree имеет тот же тип
            const TreeWrapper<T>* castedSubtree = dynamic_cast<const TreeWrapper<T>*>(&subtree);
            if (castedSubtree == nullptr) {
                return false; // Разные типы, не может быть поддеревом
            }
            
            return tree.containsSubtree(castedSubtree->tree);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при проверке поддерева: " << e.what() << std::endl;
            return false;
        }
    }
    
    void fillWithRandomValues(int count, const std::string& minStr, const std::string& maxStr) override {
        // По умолчанию ничего не делаем, реализуется в специализациях
        std::cerr << "Заполнение случайными значениями не поддерживается для данного типа" << std::endl;
    }
    
    // Получить само дерево
    BinarySearchTree<T>& getTree() {
        return tree;
    }
};

// Специализация для целых чисел
template<>
std::shared_ptr<AbstractTreeWrapper> TreeWrapper<int>::map(const std::string& multiplierStr) const {
    try {
        int multiplier = std::stoi(multiplierStr);
        auto result = std::make_shared<TreeWrapper<int>>();
        
        result->tree = tree.map([multiplier](const int& value) {
            return value * multiplier;
        });
        
        return result;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при выполнении map: " << e.what() << std::endl;
        return std::make_shared<TreeWrapper<int>>();
    }
}

template<>
std::string TreeWrapper<int>::reduce(const std::string& initialValueStr) const {
    try {
        int initialValue = std::stoi(initialValueStr);
        int result = tree.reduce([](const int& value, const int& acc) {
            return value + acc;
        }, initialValue);
        
        return std::to_string(result);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при выполнении reduce: " << e.what() << std::endl;
        return "Ошибка при выполнении reduce";
    }
}

template<>
std::shared_ptr<AbstractTreeWrapper> TreeWrapper<int>::where(int filterType, const std::string& valueStr) const {
    try {
        auto result = std::make_shared<TreeWrapper<int>>();
        
        switch(filterType) {
            case 1: // Четные
                result->tree = tree.where([](const int& value) {
                    return value % 2 == 0;
                });
                break;
                
            case 2: // Нечетные
                result->tree = tree.where([](const int& value) {
                    return value % 2 != 0;
                });
                break;
                
            case 3: // Больше значения
            {
                int threshold = std::stoi(valueStr);
                result->tree = tree.where([threshold](const int& value) {
                    return value > threshold;
                });
                break;
            }
                
            case 4: // Меньше значения
            {
                int threshold = std::stoi(valueStr);
                result->tree = tree.where([threshold](const int& value) {
                    return value < threshold;
                });
                break;
            }
                
            default:
                result->tree = tree; // Просто копируем
                break;
        }
        
        return result;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при выполнении where: " << e.what() << std::endl;
        return std::make_shared<TreeWrapper<int>>();
    }
}

template<>
void TreeWrapper<int>::fillWithRandomValues(int count, const std::string& minStr, const std::string& maxStr) {
    try {
        int min = std::stoi(minStr);
        int max = std::stoi(maxStr);
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(min, max);
        
        clear(); // Очищаем дерево перед заполнением
        
        for (int i = 0; i < count; i++) {
            tree.insert(dist(gen));
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при заполнении случайными значениями: " << e.what() << std::endl;
    }
}

// Функция для очистки буфера ввода
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

// Функция для ожидания нажатия клавиши пользователем
void waitForKeyPress() {
    std::cout << "\nНажмите Enter для продолжения...";
    clearInputBuffer();
    std::cin.get();
}

// Меню выбора типа данных
DataType chooseDataType() {
    std::cout << "\n===== ТИП ДАННЫХ =====\n";
    std::cout << "Используются целые числа (int)\n";
    return DataType::Integer;
}

// Меню выбора структуры данных
DataStructure chooseDataStructure() {
    int choice;
    std::cout << "\n===== СТРУКТУРА ДАННЫХ =====\n";
    std::cout << "1. Бинарное дерево поиска\n";
    std::cout << "2. Бинарная куча\n";
    std::cout << "Выберите структуру данных: ";
    std::cin >> choice;
    
    switch (choice) {
        case 2: return DataStructure::BinaryHeap;
        case 1:
        default: return DataStructure::BinarySearchTree;
    }
}

// Создание обертки дерева нужного типа
std::shared_ptr<AbstractTreeWrapper> createTreeWrapper(DataType type) {
    return std::make_shared<TreeWrapper<int>>();
}

// Создание обертки кучи нужного типа
std::shared_ptr<AbstractHeapWrapper> createHeapWrapper(DataType type) {
    return std::make_shared<HeapWrapper<int>>();
}

// Главное меню
void showMenu(DataStructure structure) {
    if (structure == DataStructure::BinarySearchTree) {
        std::cout << "\n===== БИНАРНОЕ ДЕРЕВО ПОИСКА =====\n";
        std::cout << "1. Вставить элемент\n";
        std::cout << "2. Удалить элемент\n";
        std::cout << "3. Найти элемент\n";
        std::cout << "4. Вывести дерево\n";
        std::cout << "5. Получить размер дерева\n";
        std::cout << "6. Очистить дерево\n";
        std::cout << "7. Сбалансировать дерево\n";
        std::cout << "8. Дополнительные операции\n";
        std::cout << "9. Сменить структуру данных\n";
        std::cout << "0. Выход\n";
    } else {
        std::cout << "\n===== БИНАРНАЯ КУЧА =====\n";
        std::cout << "1. Вставить элемент\n";
        std::cout << "2. Удалить элемент\n";
        std::cout << "3. Найти элемент\n";
        std::cout << "4. Вывести кучу\n";
        std::cout << "5. Получить размер кучи\n";
        std::cout << "6. Очистить кучу\n";
        std::cout << "7. Извлечь максимальный элемент\n";
        std::cout << "8. Показать вершину кучи\n";
        std::cout << "9. Дополнительные операции\n";
        std::cout << "10. Сменить структуру данных\n";
        std::cout << "0. Выход\n";
    }
    std::cout << "Выберите пункт меню: ";
}

// Меню дополнительных операций для дерева
void showAdditionalMenuTree() {
    std::cout << "\n===== ДОПОЛНИТЕЛЬНЫЕ ОПЕРАЦИИ ДЛЯ ДЕРЕВА =====\n";
    std::cout << "1. Map (умножить все элементы на число)\n";
    std::cout << "2. Reduce (найти сумму элементов)\n";
    std::cout << "3. Where (отфильтровать дерево)\n";
    std::cout << "4. Вывести элементы в порядке обхода\n";
    std::cout << "5. Сохранить дерево в строку\n";
    std::cout << "6. Создать дерево из строки\n";
    std::cout << "7. Извлечь поддерево по значению корня\n";
    std::cout << "8. Проверить наличие поддерева\n";
    std::cout << "9. Заполнить дерево случайными числами\n";
    std::cout << "10. Сохранить дерево в отформатированной строке\n";
    std::cout << "11. Загрузить дерево из строки\n";
    std::cout << "12. Загрузить дерево из отформатированной строки\n";
    std::cout << "13. Загрузить дерево из списка пар 'узел-родитель'\n";
    std::cout << "0. Вернуться в главное меню\n";
    std::cout << "Выберите пункт меню: ";
}

// Меню дополнительных операций для кучи
void showAdditionalMenuHeap() {
    std::cout << "\n===== ДОПОЛНИТЕЛЬНЫЕ ОПЕРАЦИИ ДЛЯ КУЧИ =====\n";
    std::cout << "1. Извлечь поддерево по заданному элементу\n";
    std::cout << "2. Проверить наличие поддерева\n";
    std::cout << "3. Сохранить кучу в строку\n";
    std::cout << "4. Сохранить кучу в отформатированной строке\n";
    std::cout << "5. Сохранить кучу в формате списка пар 'узел-родитель'\n";
    std::cout << "6. Загрузить кучу из строки\n";
    std::cout << "7. Загрузить кучу из отформатированной строки\n";
    std::cout << "8. Загрузить кучу из списка пар 'узел-родитель'\n";
    std::cout << "9. Заполнить кучу случайными числами\n";
    std::cout << "0. Вернуться в главное меню\n";
    std::cout << "Выберите пункт меню: ";
}

// Меню выбора типа обхода
TraversalType chooseTraversalType() {
    int choice;
    
    std::cout << "\n===== ВЫБЕРИТЕ ТИП ОБХОДА =====\n";
    std::cout << "1. PreOrder (КЛП)\n";
    std::cout << "2. InOrder (ЛКП)\n";
    std::cout << "3. PostOrder (ЛПК)\n";
    std::cout << "4. ReversePreOrder (КПЛ)\n";
    std::cout << "5. ReverseInOrder (ПКЛ)\n";
    std::cout << "6. ReversePostOrder (ПЛК)\n";
    std::cout << "Выберите тип обхода: ";
    
    std::cin >> choice;
    
    switch (choice) {
        case 1: return TraversalType::PreOrder;
        case 2: return TraversalType::InOrder;
        case 3: return TraversalType::PostOrder;
        case 4: return TraversalType::ReversePreOrder;
        case 5: return TraversalType::ReverseInOrder;
        case 6: return TraversalType::ReversePostOrder;
        default: return TraversalType::InOrder; // По умолчанию
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    // Создаем дерево целых чисел
    DataType currentType = DataType::Integer;
    DataStructure currentStructure = DataStructure::BinarySearchTree;
    
    std::shared_ptr<AbstractTreeWrapper> tree = createTreeWrapper(currentType);
    std::shared_ptr<AbstractHeapWrapper> heap = createHeapWrapper(currentType);
    
    int choice;
    std::string valueStr, multiplierStr, minStr, maxStr, formatStr;
    bool running = true;
    
    while (running) {
        system("cls"); // Очистка экрана (для Windows)
        
        // Отображаем текущий тип данных и структуру
        std::cout << "Текущий тип данных: Целые числа (int)" << std::endl;
        std::cout << "Текущая структура данных: " 
                  << (currentStructure == DataStructure::BinarySearchTree ? 
                      "Бинарное дерево поиска" : "Бинарная куча") << std::endl;
        
        // Показываем соответствующее меню
        showMenu(currentStructure);
        std::cin >> choice;
        
        // Обработка выбора в зависимости от текущей структуры данных
        if (currentStructure == DataStructure::BinarySearchTree) {
            // Меню для бинарного дерева поиска
            switch (choice) {
                case 0: // Выход
                    running = false;
                    break;
                    
                case 1: // Вставка элемента
                    std::cout << "Введите значение для вставки: ";
                    clearInputBuffer();
                    std::getline(std::cin, valueStr);
                    tree->insert(valueStr);
                    std::cout << "Элемент добавлен в дерево.\n";
                    waitForKeyPress();
                    break;
                    
                case 2: // Удаление элемента
                    std::cout << "Введите значение для удаления: ";
                    clearInputBuffer();
                    std::getline(std::cin, valueStr);
                    if (tree->remove(valueStr)) {
                        std::cout << "Элемент удален из дерева.\n";
                    } else {
                        std::cout << "Элемент не найден в дереве.\n";
                    }
                    waitForKeyPress();
                    break;
                    
                case 3: // Поиск элемента
                    std::cout << "Введите значение для поиска: ";
                    clearInputBuffer();
                    std::getline(std::cin, valueStr);
                    if (tree->search(valueStr)) {
                        std::cout << "Элемент найден в дереве.\n";
                    } else {
                        std::cout << "Элемент не найден в дереве.\n";
                    }
                    waitForKeyPress();
                    break;
                    
                case 4: // Вывод дерева
                    std::cout << "Структура дерева:\n";
                    tree->printTree();
                    waitForKeyPress();
                    break;
                    
                case 5: // Получение размера дерева
                    std::cout << "Размер дерева: " << tree->getSize() << " элементов.\n";
                    waitForKeyPress();
                    break;
                    
                case 6: // Очистка дерева
                    tree->clear();
                    std::cout << "Дерево очищено.\n";
                    waitForKeyPress();
                    break;
                    
                case 7: // Балансировка дерева
                    tree->balance();
                    std::cout << "Дерево сбалансировано.\n";
                    waitForKeyPress();
                    break;
                    
                case 8: { // Дополнительные операции для дерева
                    int subChoice;
                    bool subRunning = true;
                    
                    while (subRunning) {
                        system("cls"); // Очистка экрана
                        
                        showAdditionalMenuTree();
                        std::cin >> subChoice;
                        
                        switch (subChoice) {
                            case 0: // Возврат в главное меню
                                subRunning = false;
                                break;
                                
                            case 1: { // Map
                                std::cout << "Введите множитель: ";
                                clearInputBuffer();
                                std::getline(std::cin, multiplierStr);
                                
                                auto mappedTree = tree->map(multiplierStr);
                                
                                std::cout << "Результат применения map:\n";
                                mappedTree->printTree();
                                
                                std::cout << "Хотите заменить исходное дерево результатом? (1 - да, 0 - нет): ";
                                std::cin >> choice;
                                if (choice == 1) {
                                    tree = mappedTree;
                                    std::cout << "Дерево заменено результатом операции map.\n";
                                }
                                
                                waitForKeyPress();
                                break;
                            }
                                
                            case 2: { // Reduce
                                std::cout << "Введите начальное значение: ";
                                clearInputBuffer();
                                std::getline(std::cin, valueStr);
                                
                                std::string result = tree->reduce(valueStr);
                                
                                std::cout << "Результат операции reduce: " << result << "\n";
                                waitForKeyPress();
                                break;
                            }
                                
                            case 3: { // Where
                                int filterType = 0;
                                
                                std::cout << "Выберите фильтр:\n";
                                std::cout << "1. Только четные числа\n";
                                std::cout << "2. Только нечетные числа\n";
                                std::cout << "3. Числа, больше значения\n";
                                std::cout << "4. Числа, меньше значения\n";
                                std::cout << "Ваш выбор: ";
                                std::cin >> filterType;
                                
                                if (filterType >= 3) {
                                    std::cout << "Введите пороговое значение: ";
                                    clearInputBuffer();
                                    std::getline(std::cin, valueStr);
                                } else {
                                    valueStr = ""; // Не используется для фильтров 1 и 2
                                }
                                
                                auto filteredTree = tree->where(filterType, valueStr);
                                
                                std::cout << "Результат фильтрации:\n";
                                filteredTree->printTree();
                                
                                std::cout << "Хотите заменить исходное дерево результатом? (1 - да, 0 - нет): ";
                                std::cin >> choice;
                                if (choice == 1) {
                                    tree = filteredTree;
                                    std::cout << "Дерево заменено результатом операции where.\n";
                                }
                                
                                waitForKeyPress();
                                break;
                            }
                                
                            case 4: { // Вывод элементов в порядке обхода
                                TraversalType type = chooseTraversalType();
                                auto values = tree->getValuesByTraversal(type);
                                
                                std::cout << "Элементы в выбранном порядке обхода:\n";
                                for (const auto& value : values) {
                                    std::cout << value << " ";
                                }
                                std::cout << std::endl;
                                
                                waitForKeyPress();
                                break;
                            }
                                
                            case 5: { // Сохранение дерева в строку
                                std::string treeString = tree->toString();
                                std::cout << "Дерево в виде строки: " << treeString << std::endl;
                                waitForKeyPress();
                                break;
                            }
                                
                            case 6: { // Создание дерева из строки
                                std::cout << "Введите строку для создания дерева:\n";
                                clearInputBuffer();
                                std::getline(std::cin, valueStr);
                                
                                // Создаем новое дерево того же типа
                                auto newTree = createTreeWrapper(currentType);
                                
                                // Парсим строку и заполняем дерево
                                // Упрощенная версия: просто разбиваем строку по запятым
                                size_t pos = 0;
                                std::string token;
                                std::string data = valueStr;
                                
                                // Удаляем квадратные скобки, если они есть
                                if (data.size() >= 2 && data[0] == '[' && data[data.size() - 1] == ']') {
                                    data = data.substr(1, data.size() - 2);
                                }
                                
                                while ((pos = data.find(", ")) != std::string::npos) {
                                    token = data.substr(0, pos);
                                    newTree->insert(token);
                                    data.erase(0, pos + 2);
                                }
                                
                                // Добавляем последний элемент
                                if (!data.empty()) {
                                    newTree->insert(data);
                                }
                                
                                std::cout << "Создано дерево из строки:\n";
                                newTree->printTree();
                                
                                std::cout << "Хотите заменить текущее дерево новым? (1 - да, 0 - нет): ";
                                std::cin >> choice;
                                if (choice == 1) {
                                    tree = newTree;
                                    std::cout << "Дерево заменено.\n";
                                }
                                
                                waitForKeyPress();
                                break;
                            }
                                
                            case 7: { // Извлечение поддерева по значению корня
                                std::cout << "Введите значение корня поддерева: ";
                                clearInputBuffer();
                                std::getline(std::cin, valueStr);
                                
                                auto subtree = tree->extractSubtree(valueStr);
                                
                                std::cout << "Извлеченное поддерево:\n";
                                subtree->printTree();
                                
                                std::cout << "Хотите заменить текущее дерево поддеревом? (1 - да, 0 - нет): ";
                                std::cin >> choice;
                                if (choice == 1) {
                                    tree = subtree;
                                    std::cout << "Дерево заменено поддеревом.\n";
                                }
                                
                                waitForKeyPress();
                                break;
                            }
                                
                            case 8: { // Проверка наличия поддерева
                                // Создаем дерево для сравнения
                                std::cout << "Введите элементы для создания поддерева (через запятую): ";
                                clearInputBuffer();
                                std::getline(std::cin, valueStr);
                                
                                auto subtree = createTreeWrapper(currentType);
                                
                                // Парсим строку и заполняем дерево
                                size_t pos = 0;
                                std::string token;
                                std::string data = valueStr;
                                
                                while ((pos = data.find(",")) != std::string::npos) {
                                    token = data.substr(0, pos);
                                    subtree->insert(token);
                                    data.erase(0, pos + 1);
                                }
                                
                                // Добавляем последний элемент
                                if (!data.empty()) {
                                    subtree->insert(data);
                                }
                                
                                std::cout << "Созданное поддерево:\n";
                                subtree->printTree();
                                
                                if (tree->containsSubtree(*subtree)) {
                                    std::cout << "Данное поддерево содержится в основном дереве.\n";
                                } else {
                                    std::cout << "Данное поддерево НЕ содержится в основном дереве.\n";
                                }
                                
                                waitForKeyPress();
                                break;
                            }
                                
                            case 9: { // Заполнение дерева случайными значениями
                                int count;
                                std::cout << "Введите количество случайных элементов: ";
                                std::cin >> count;
                                
                                std::cout << "Введите минимальное значение: ";
                                clearInputBuffer();
                                std::getline(std::cin, minStr);
                                
                                std::cout << "Введите максимальное значение: ";
                                std::getline(std::cin, maxStr);
                                
                                tree->fillWithRandomValues(count, minStr, maxStr);
                                
                                std::cout << "Дерево заполнено " << count << " случайными значениями.\n";
                                waitForKeyPress();
                                break;
                            }
                                
                            case 10: {
                                clearInputBuffer();
                                std::cout << "Введите формат строкового представления: ";
                                std::string formatStr;
                                std::getline(std::cin, formatStr);
                                {
                                    auto wrapperInt = std::dynamic_pointer_cast<TreeWrapper<int>>(tree);
                                    if (wrapperInt) {
                                        std::string formatted = wrapperInt->getTree().toStringFormatted(formatStr);
                                        std::cout << "Дерево в отформатированной строке: " << formatted << std::endl;
                                    }
                                }
                                waitForKeyPress();
                                break;
                            }
                                
                            case 11: {
                                clearInputBuffer();
                                std::cout << "Введите строку для создания дерева (InOrder):\n";
                                std::string str;
                                std::getline(std::cin, str);
                                {
                                    auto loaded = BinarySearchTree<int>::fromString(str);
                                    auto wrapperInt = std::dynamic_pointer_cast<TreeWrapper<int>>(tree);
                                    if (wrapperInt) {
                                        wrapperInt->getTree() = loaded;
                                        std::cout << "Дерево создано из строки.\n";
                                    }
                                }
                                waitForKeyPress();
                                break;
                            }
                                
                            case 12: {
                                clearInputBuffer();
                                std::cout << "Введите формат строкового представления: ";
                                std::string formatStr;
                                std::getline(std::cin, formatStr);
                                std::cout << "Введите строку для создания дерева:\n";
                                std::string str;
                                std::getline(std::cin, str);
                                {
                                    auto loaded = BinarySearchTree<int>::fromStringFormatted(str, formatStr);
                                    auto wrapperInt = std::dynamic_pointer_cast<TreeWrapper<int>>(tree);
                                    if (wrapperInt) {
                                        wrapperInt->getTree() = loaded;
                                        std::cout << "Дерево создано из отформатированной строки.\n";
                                    }
                                }
                                waitForKeyPress();
                                break;
                            }
                                
                            case 13: {
                                clearInputBuffer();
                                std::cout << "Введите пары 'узел-родитель' через запятую (например 5-3,7-3,...): ";
                                std::string pairsStr;
                                std::getline(std::cin, pairsStr);
                                {
                                    std::vector<std::pair<int,int>> pairs;
                                    std::stringstream ss(pairsStr);
                                    std::string item;
                                    while (std::getline(ss, item, ',')) {
                                        size_t dashPos = item.find('-');
                                        if (dashPos != std::string::npos) {
                                            int node = std::stoi(item.substr(0, dashPos));
                                            int parent = std::stoi(item.substr(dashPos + 1));
                                            pairs.emplace_back(node, parent);
                                        }
                                    }
                                    auto loaded = BinarySearchTree<int>::fromNodeParentPairs(pairs);
                                    auto wrapperInt = std::dynamic_pointer_cast<TreeWrapper<int>>(tree);
                                    if (wrapperInt) {
                                        wrapperInt->getTree() = loaded;
                                        std::cout << "Дерево создано из списка пар.\n";
                                    }
                                }
                                waitForKeyPress();
                                break;
                            }
                                
                            default:
                                std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
                                waitForKeyPress();
                                break;
                        }
                    }
                    break;
                }
                    
                case 9: // Смена структуры данных
                    currentStructure = chooseDataStructure();
                    break;
                    
                default:
                    std::cout << "Неизвестная команда.\n";
                    waitForKeyPress();
                    break;
            }
        } else {
            // Меню для бинарной кучи
            switch (choice) {
                case 0: // Выход
                    running = false;
                    break;
                    
                case 1: // Вставка элемента
                    std::cout << "Введите значение для вставки: ";
                    clearInputBuffer();
                    std::getline(std::cin, valueStr);
                    heap->insert(valueStr);
                    std::cout << "Элемент добавлен в кучу.\n";
                    waitForKeyPress();
                    break;
                    
                case 2: // Удаление элемента
                    std::cout << "Введите значение для удаления: ";
                    clearInputBuffer();
                    std::getline(std::cin, valueStr);
                    if (heap->remove(valueStr)) {
                        std::cout << "Элемент удален из кучи.\n";
                    } else {
                        std::cout << "Элемент не найден в куче.\n";
                    }
                    waitForKeyPress();
                    break;
                    
                case 3: // Поиск элемента
                    std::cout << "Введите значение для поиска: ";
                    clearInputBuffer();
                    std::getline(std::cin, valueStr);
                    if (heap->search(valueStr)) {
                        std::cout << "Элемент найден в куче.\n";
                    } else {
                        std::cout << "Элемент не найден в куче.\n";
                    }
                    waitForKeyPress();
                    break;
                    
                case 4: // Вывод кучи
                    std::cout << "Структура кучи:\n";
                    heap->printHeap();
                    waitForKeyPress();
                    break;
                    
                case 5: // Получение размера кучи
                    std::cout << "Размер кучи: " << heap->getSize() << " элементов.\n";
                    waitForKeyPress();
                    break;
                    
                case 6: // Очистка кучи
                    heap->clear();
                    std::cout << "Куча очищена.\n";
                    waitForKeyPress();
                    break;
                    
                case 7: // Извлечение максимального элемента
                    if (heap->getSize() > 0) {
                        std::string maxValue = heap->extractMax();
                        std::cout << "Извлечен максимальный элемент: " << maxValue << std::endl;
                    } else {
                        std::cout << "Куча пуста.\n";
                    }
                    waitForKeyPress();
                    break;
                    
                case 8: // Показать вершину кучи
                    if (heap->getSize() > 0) {
                        std::string topValue = heap->top();
                        std::cout << "Вершина кучи: " << topValue << std::endl;
                    } else {
                        std::cout << "Куча пуста.\n";
                    }
                    waitForKeyPress();
                    break;
                    
                case 9: { // Дополнительные операции для кучи
                    int subChoice;
                    bool subRunning = true;
                    
                    while (subRunning) {
                        system("cls"); // Очистка экрана
                        
                        showAdditionalMenuHeap();
                        std::cin >> subChoice;
                        
                        switch (subChoice) {
                            case 0: // Возврат в главное меню
                                subRunning = false;
                                break;
                                
                            case 1: { // Извлечь поддерево
                                std::cout << "Введите значение корня поддерева: ";
                                clearInputBuffer();
                                std::getline(std::cin, valueStr);
                                
                                auto subheap = heap->extractSubHeap(valueStr);
                                
                                std::cout << "Результат извлечения поддерева:\n";
                                subheap->printHeap();
                                
                                std::cout << "Хотите заменить исходную кучу результатом? (1 - да, 0 - нет): ";
                                std::cin >> choice;
                                if (choice == 1) {
                                    heap = subheap;
                                    std::cout << "Куча заменена результатом операции.\n";
                                }
                                
                                waitForKeyPress();
                                break;
                            }
                                
                            case 2: { // Проверить наличие поддерева
                                std::cout << "Создайте поддерево для проверки:" << std::endl;
                                std::shared_ptr<AbstractHeapWrapper> checkHeap = createHeapWrapper(currentType);
                                
                                int count;
                                std::cout << "Введите количество элементов для добавления: ";
                                std::cin >> count;
                                
                                for (int i = 0; i < count; ++i) {
                                    std::cout << "Введите элемент " << (i + 1) << ": ";
                                    clearInputBuffer();
                                    std::getline(std::cin, valueStr);
                                    checkHeap->insert(valueStr);
                                }
                                
                                if (heap->containsSubHeap(*checkHeap)) {
                                    std::cout << "Поддерево найдено в куче." << std::endl;
                                } else {
                                    std::cout << "Поддерево не найдено в куче." << std::endl;
                                }
                                
                                waitForKeyPress();
                                break;
                            }
                                
                            case 3: { // Сохранить кучу в строку
                                std::string str = heap->toString();
                                std::cout << "Куча в строковом представлении: " << str << std::endl;
                                waitForKeyPress();
                                break;
                            }
                                
                            case 4: { // Сохранить кучу в отформатированной строке
                                std::cout << "Введите формат обхода (например, КЛП): ";
                                clearInputBuffer();
                                std::getline(std::cin, formatStr);
                                
                                std::string str = heap->toStringFormatted(formatStr);
                                std::cout << "Куча в отформатированном представлении: " << str << std::endl;
                                waitForKeyPress();
                                break;
                            }
                                
                            case 5: { // Сохранить кучу в формате узел-родитель
                                std::string str = heap->toNodeParentPairs();
                                std::cout << "Куча в формате узел-родитель: " << str << std::endl;
                                waitForKeyPress();
                                break;
                            }
                                
                            case 6: { // Загрузить кучу из строки
                                std::cout << "Введите строковое представление кучи: ";
                                clearInputBuffer();
                                std::getline(std::cin, valueStr);
                                
                                auto newHeap = heap->fromString(valueStr);
                                
                                std::cout << "Результат загрузки из строки:\n";
                                newHeap->printHeap();
                                
                                std::cout << "Хотите заменить исходную кучу результатом? (1 - да, 0 - нет): ";
                                std::cin >> choice;
                                if (choice == 1) {
                                    heap = newHeap;
                                    std::cout << "Куча заменена результатом операции.\n";
                                }
                                
                                waitForKeyPress();
                                break;
                            }
                                
                            case 7: { // Загрузить кучу из отформатированной строки
                                std::cout << "Введите строковое представление кучи: ";
                                clearInputBuffer();
                                std::getline(std::cin, valueStr);
                                
                                std::cout << "Введите формат обхода (например, КЛП): ";
                                std::getline(std::cin, formatStr);
                                
                                auto newHeap = heap->fromStringFormatted(valueStr, formatStr);
                                
                                std::cout << "Результат загрузки из отформатированной строки:\n";
                                newHeap->printHeap();
                                
                                std::cout << "Хотите заменить исходную кучу результатом? (1 - да, 0 - нет): ";
                                std::cin >> choice;
                                if (choice == 1) {
                                    heap = newHeap;
                                    std::cout << "Куча заменена результатом операции.\n";
                                }
                                
                                waitForKeyPress();
                                break;
                            }
                                
                            case 8: { // Загрузить кучу из списка пар узел-родитель
                                std::cout << "Введите список пар узел-родитель: ";
                                clearInputBuffer();
                                std::getline(std::cin, valueStr);
                                
                                auto newHeap = heap->fromNodeParentPairs(valueStr);
                                
                                std::cout << "Результат загрузки из списка пар:\n";
                                newHeap->printHeap();
                                
                                std::cout << "Хотите заменить исходную кучу результатом? (1 - да, 0 - нет): ";
                                std::cin >> choice;
                                if (choice == 1) {
                                    heap = newHeap;
                                    std::cout << "Куча заменена результатом операции.\n";
                                }
                                
                                waitForKeyPress();
                                break;
                            }
                                
                            case 9: { // Заполнить кучу случайными числами
                                int count;
                                std::cout << "Введите количество случайных элементов: ";
                                std::cin >> count;
                                
                                std::cout << "Введите минимальное значение: ";
                                clearInputBuffer();
                                std::getline(std::cin, minStr);
                                
                                std::cout << "Введите максимальное значение: ";
                                std::getline(std::cin, maxStr);
                                
                                heap->fillWithRandomValues(count, minStr, maxStr);
                                
                                waitForKeyPress();
                                break;
                            }
                                
                            default:
                                std::cout << "Неизвестная команда.\n";
                                waitForKeyPress();
                                break;
                        }
                    }
                    break;
                }
                    
                case 10: // Смена структуры данных
                    currentStructure = chooseDataStructure();
                    break;
                    
                default:
                    std::cout << "Неизвестная команда.\n";
                    waitForKeyPress();
                    break;
            }
        }
    }
    
    return 0;
} 