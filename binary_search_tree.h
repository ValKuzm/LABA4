#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include "data_types.h" // Включаем определения пользовательских типов



// Перечисление для различных типов обхода дерева
enum class TraversalType {
    PreOrder,   // КЛП - корень, левое поддерево, правое поддерево
    InOrder,    // ЛКП - левое поддерево, корень, правое поддерево
    PostOrder,  // ЛПК - левое поддерево, правое поддерево, корень
    ReversePreOrder,  // КПЛ - корень, правое поддерево, левое поддерево
    ReverseInOrder,   // ПКЛ - правое поддерево, корень, левое поддерево
    ReversePostOrder  // ПЛК - правое поддерево, левое поддерево, корень
};

// Шаблонный класс бинарного дерева поиска
template <typename T>
class BinarySearchTree {
private:
    // Структура узла дерева
    struct Node {
        T data;           // Данные узла
        Node* left;       // Указатель на левое поддерево
        Node* right;      // Указатель на правое поддерево
        Node* parent;     // Указатель на родительский узел (нужен для некоторых операций)
        
        // Конструктор узла
        Node(const T& value, Node* parent = nullptr) 
            : data(value), left(nullptr), right(nullptr), parent(parent) {}
    };
    
    Node* root;  // Корень дерева
    size_t size; // Размер дерева (количество узлов)

    // Вспомогательные методы
    // Рекурсивная вставка узла
    Node* insertNode(Node* node, const T& value, Node* parent);
    
    // Рекурсивный поиск узла
    Node* findNode(Node* node, const T& value) const;
    
    // Удаление узла
    Node* removeNode(Node* node, const T& value);
    
    // Нахождение минимального узла в поддереве
    Node* findMin(Node* node) const;
    
    // Нахождение максимального узла в поддереве
    Node* findMax(Node* node) const;
    
    // Рекурсивное удаление дерева
    void destroyTree(Node* node);
    
    // Клонирование дерева
    Node* cloneTree(Node* node, Node* parent = nullptr) const;
    
    // Метод для обхода дерева по заданному типу
    void traverseByType(Node* node, TraversalType type, std::function<void(const T&)> callback) const;
    
    // Проверка, является ли данный узел поддеревом другого дерева
    bool isSubtree(Node* tree, Node* subtree) const;
    
    // Сравнение двух деревьев на идентичность
    bool areIdentical(Node* node1, Node* node2) const;

public:
    // Конструкторы и деструкторы
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other);
    ~BinarySearchTree();
    
    // Присваивание
    BinarySearchTree& operator=(const BinarySearchTree& other);
    
    // Базовые операции
    void insert(const T& value);       // Вставка элемента
    bool search(const T& value) const; // Поиск элемента
    bool remove(const T& value);       // Удаление элемента
    
    // Дополнительные операции
    bool isEmpty() const;              // Проверка на пустоту
    size_t getSize() const;            // Получение размера дерева
    void clear();                      // Очистка дерева
    
    // 1.1 Балансировка дерева
    void balance();
    
    // 1.2 map, reduce, where
    BinarySearchTree<T> map(std::function<T(const T&)> func) const;
    T reduce(std::function<T(const T&, const T&)> func, const T& initialValue) const;
    BinarySearchTree<T> where(std::function<bool(const T&)> predicate) const;
    
    // 1.3 Прошивка дерева (получение значений в порядке обхода)
    // 1.3.1 по фиксированному обходу (InOrder)
    std::vector<T> getValuesInOrder() const;
    
    // 1.3.2 по обходу, задаваемому параметром метода
    std::vector<T> getValuesByTraversal(TraversalType type) const;
    
    // 1.4 Сохранение в строку
    // 1.4.1 по фиксированному обходу
    std::string toString() const;
    
    // 1.4.2 по обходу, задаваемому строкой форматирования
    std::string toStringFormatted(const std::string& format) const;
    
    // 1.5 Чтение из строки
    // 1.5.1 по фиксированному обходу
    static BinarySearchTree<T> fromString(const std::string& str);
    
    // 1.5.2 по обходу, задаваемому строкой форматирования
    static BinarySearchTree<T> fromStringFormatted(const std::string& str, const std::string& format);
    
    // 1.5.3 в формате списка пар «узел-родитель»
    static BinarySearchTree<T> fromNodeParentPairs(const std::vector<std::pair<T, T>>& pairs);
    
    // 1.6 Извлечение поддерева (по заданному корню)
    BinarySearchTree<T> extractSubtree(const T& value);
    
    // 1.7 Поиск на вхождение поддерева
    bool containsSubtree(const BinarySearchTree<T>& subtree) const;
    
    // Обход дерева с вызовом функции обратного вызова для каждого элемента
    void traverse(TraversalType type, std::function<void(const T&)> callback) const;
    
    // Вывод дерева в консоль (для отладки)
    void printTree() const;
};

// Реализация конструкторов и деструкторов

template <typename T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr), size(0) {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& other) : root(nullptr), size(0) {
    if (other.root != nullptr) {
        root = cloneTree(other.root);
        size = other.size;
    }
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    clear();
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& other) {
    if (this != &other) {
        clear();
        if (other.root != nullptr) {
            root = cloneTree(other.root);
            size = other.size;
        }
    }
    return *this;
}

// Реализация вспомогательных методов

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::cloneTree(Node* node, Node* parent) const {
    if (node == nullptr) {
        return nullptr;
    }
    
    Node* newNode = new Node(node->data, parent);
    newNode->left = cloneTree(node->left, newNode);
    newNode->right = cloneTree(node->right, newNode);
    
    return newNode;
}

template <typename T>
void BinarySearchTree<T>::destroyTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::insertNode(Node* node, const T& value, Node* parent) {
    if (node == nullptr) {
        size++;
        return new Node(value, parent);
    }
    
    if (value < node->data) {
        node->left = insertNode(node->left, value, node);
    } else if (value > node->data) {
        node->right = insertNode(node->right, value, node);
    }
    
    return node;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findNode(Node* node, const T& value) const {
    if (node == nullptr || node->data == value) {
        return node;
    }
    
    if (value < node->data) {
        return findNode(node->left, value);
    } else {
        return findNode(node->right, value);
    }
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findMin(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    
    while (node->left != nullptr) {
        node = node->left;
    }
    
    return node;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findMax(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    
    while (node->right != nullptr) {
        node = node->right;
    }
    
    return node;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::removeNode(Node* node, const T& value) {
    if (node == nullptr) {
        return nullptr;
    }
    
    if (value < node->data) {
        node->left = removeNode(node->left, value);
    } else if (value > node->data) {
        node->right = removeNode(node->right, value);
    } else {
        // Нашли узел для удаления
        
        // Случай 1: Узел является листом (не имеет потомков)
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            size--;
            return nullptr;
        }
        // Случай 2: Узел имеет только одного потомка
        else if (node->left == nullptr) {
            Node* temp = node->right;
            if (temp != nullptr) {
                temp->parent = node->parent;
            }
            delete node;
            size--;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            if (temp != nullptr) {
                temp->parent = node->parent;
            }
            delete node;
            size--;
            return temp;
        }
        // Случай 3: Узел имеет двух потомков
        else {
            // Находим узел-преемник (наименьший узел в правом поддереве)
            Node* successor = findMin(node->right);
            
            // Копируем данные преемника в текущий узел
            node->data = successor->data;
            
            // Удаляем преемник
            node->right = removeNode(node->right, successor->data);
        }
    }
    
    return node;
}

// Реализация базовых операций

template <typename T>
void BinarySearchTree<T>::insert(const T& value) {
    root = insertNode(root, value, nullptr);
}

template <typename T>
bool BinarySearchTree<T>::search(const T& value) const {
    return findNode(root, value) != nullptr;
}

template <typename T>
bool BinarySearchTree<T>::remove(const T& value) {
    size_t oldSize = size;
    root = removeNode(root, value);
    return size < oldSize;
}

template <typename T>
bool BinarySearchTree<T>::isEmpty() const {
    return root == nullptr;
}

template <typename T>
size_t BinarySearchTree<T>::getSize() const {
    return size;
}

template <typename T>
void BinarySearchTree<T>::clear() {
    destroyTree(root);
    root = nullptr;
    size = 0;
}

// Реализация метода обхода дерева
template <typename T>
void BinarySearchTree<T>::traverseByType(Node* node, TraversalType type, std::function<void(const T&)> callback) const {
    if (node == nullptr) {
        return;
    }
    
    switch (type) {
        case TraversalType::PreOrder: // КЛП
            callback(node->data);
            traverseByType(node->left, type, callback);
            traverseByType(node->right, type, callback);
            break;
            
        case TraversalType::InOrder: // ЛКП
            traverseByType(node->left, type, callback);
            callback(node->data);
            traverseByType(node->right, type, callback);
            break;
            
        case TraversalType::PostOrder: // ЛПК
            traverseByType(node->left, type, callback);
            traverseByType(node->right, type, callback);
            callback(node->data);
            break;
            
        case TraversalType::ReversePreOrder: // КПЛ
            callback(node->data);
            traverseByType(node->right, type, callback);
            traverseByType(node->left, type, callback);
            break;
            
        case TraversalType::ReverseInOrder: // ПКЛ
            traverseByType(node->right, type, callback);
            callback(node->data);
            traverseByType(node->left, type, callback);
            break;
            
        case TraversalType::ReversePostOrder: // ПЛК
            traverseByType(node->right, type, callback);
            traverseByType(node->left, type, callback);
            callback(node->data);
            break;
    }
}

template <typename T>
void BinarySearchTree<T>::traverse(TraversalType type, std::function<void(const T&)> callback) const {
    traverseByType(root, type, callback);
}

// 1.1 Балансировка дерева
template <typename T>
void BinarySearchTree<T>::balance() {
    // Собираем все элементы дерева в отсортированный массив
    std::vector<T> elements;
    traverse(TraversalType::InOrder, [&elements](const T& value) {
        elements.push_back(value);
    });
    
    // Очищаем текущее дерево
    clear();
    
    // Вспомогательная функция для построения сбалансированного дерева
    std::function<void(int, int)> buildBalanced = [&](int start, int end) {
        if (start > end) {
            return;
        }
        
        // Выбираем средний элемент как корень
        int mid = (start + end) / 2;
        insert(elements[mid]);
        
        // Рекурсивно строим левое и правое поддерево
        buildBalanced(start, mid - 1);
        buildBalanced(mid + 1, end);
    };
    
    // Строим сбалансированное дерево
    if (!elements.empty()) {
        buildBalanced(0, elements.size() - 1);
    }
}

// 1.2 map, reduce, where
template <typename T>
BinarySearchTree<T> BinarySearchTree<T>::map(std::function<T(const T&)> func) const {
    BinarySearchTree<T> result;
    
    // Обходим исходное дерево и применяем функцию к каждому элементу
    traverse(TraversalType::InOrder, [&result, &func](const T& value) {
        result.insert(func(value));
    });
    
    return result;
}

template <typename T>
T BinarySearchTree<T>::reduce(std::function<T(const T&, const T&)> func, const T& initialValue) const {
    T result = initialValue;
    
    // Обходим дерево и применяем функцию свертки
    traverse(TraversalType::InOrder, [&result, &func](const T& value) {
        result = func(value, result);
    });
    
    return result;
}

template <typename T>
BinarySearchTree<T> BinarySearchTree<T>::where(std::function<bool(const T&)> predicate) const {
    BinarySearchTree<T> result;
    
    // Обходим исходное дерево и фильтруем элементы по предикату
    traverse(TraversalType::InOrder, [&result, &predicate](const T& value) {
        if (predicate(value)) {
            result.insert(value);
        }
    });
    
    return result;
}

// 1.3.1 Получение значений в порядке InOrder
template <typename T>
std::vector<T> BinarySearchTree<T>::getValuesInOrder() const {
    std::vector<T> values;
    
    if (root == nullptr) {
        return values;
    }
    
    // Используем итеративный обход InOrder
    std::stack<Node*> stack;
    Node* current = root;
    
    while (current != nullptr || !stack.empty()) {
        // Идем до самого левого узла
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }
        
        current = stack.top();
        stack.pop();
        
        values.push_back(current->data);
        
        current = current->right;
    }
    
    return values;
}

// 1.3.2 Получение значений в порядке заданного обхода
template <typename T>
std::vector<T> BinarySearchTree<T>::getValuesByTraversal(TraversalType type) const {
    std::vector<T> values;
    
    // Используем общий метод обхода
    traverse(type, [&values](const T& value) {
        values.push_back(value);
    });
    
    return values;
}

// 1.4.1 Сохранение в строку по фиксированному обходу
template <typename T>
std::string BinarySearchTree<T>::toString() const {
    if (root == nullptr) {
        return "[]";
    }
    
    std::string result = "[";
    bool first = true;
    
    // Используем InOrder (ЛКП) обход по умолчанию
    traverse(TraversalType::InOrder, [&result, &first](const T& value) {
        if (!first) {
            result += ", ";
        }
        result += valueToString(value);
        first = false;
    });
    
    result += "]";
    return result;
}

// 1.4.2 Сохранение в строку по обходу, задаваемому строкой форматирования
template <typename T>
std::string BinarySearchTree<T>::toStringFormatted(const std::string& format) const {
    if (root == nullptr) {
        return "[]";
    }
    
    // Парсим строку форматирования и определяем тип обхода
    TraversalType type = TraversalType::InOrder; // По умолчанию
    
    if (format == "{К}(Л)[П]") {
        type = TraversalType::PreOrder;     // КЛП
    } else if (format == "(Л){К}[П]") {
        type = TraversalType::InOrder;      // ЛКП
    } else if (format == "(Л)[П]{К}") {
        type = TraversalType::PostOrder;    // ЛПК
    } else if (format == "{К}[П](Л)") {
        type = TraversalType::ReversePreOrder;  // КПЛ
    } else if (format == "[П]{К}(Л)") {
        type = TraversalType::ReverseInOrder;   // ПКЛ
    } else if (format == "[П](Л){К}") {
        type = TraversalType::ReversePostOrder; // ПЛК
    }
    
    std::string result = "[";
    bool first = true;
    
    traverse(type, [&result, &first](const T& value) {
        if (!first) {
            result += ", ";
        }
        result += valueToString(value);
        first = false;
    });
    
    result += "]";
    return result;
}

// 1.5.1 Чтение из строки по фиксированному обходу
template <typename T>
BinarySearchTree<T> BinarySearchTree<T>::fromString(const std::string& str) {
    BinarySearchTree<T> result;
    
    // Удаляем квадратные скобки и пробелы
    std::string data = str;
    if (data.size() >= 2) {
        data = data.substr(1, data.size() - 2);
    }
    
    // Разбиваем строку на элементы
    size_t pos = 0;
    std::string token;
    while ((pos = data.find(", ")) != std::string::npos) {
        token = data.substr(0, pos);
        try {
            T value = valueFromString<T>(token);
            result.insert(value);
        } catch (const std::exception& e) {
            // Пропускаем элементы, которые не могут быть преобразованы
        }
        data.erase(0, pos + 2);
    }
    
    // Обрабатываем последний элемент
    if (!data.empty()) {
        try {
            T value = valueFromString<T>(data);
            result.insert(value);
        } catch (const std::exception& e) {
            // Пропускаем элементы, которые не могут быть преобразованы
        }
    }
    
    return result;
}

// 1.5.2 Чтение из строки по обходу, задаваемому строкой форматирования
template <typename T>
BinarySearchTree<T> BinarySearchTree<T>::fromStringFormatted(const std::string& str, const std::string& format) {
    BinarySearchTree<T> result;
    if (str.empty() || format.empty()) return result;
    
    // Парсим строку форматирования и определяем тип обхода (может пригодиться для особой логики)
    TraversalType type = TraversalType::InOrder; // По умолчанию
    if (format == "{К}(Л)[П]") {
        type = TraversalType::PreOrder;     // КЛП
    } else if (format == "(Л){К}[П]") {
        type = TraversalType::InOrder;      // ЛКП
    } else if (format == "(Л)[П]{К}") {
        type = TraversalType::PostOrder;    // ЛПК
    } else if (format == "{К}[П](Л)") {
        type = TraversalType::ReversePreOrder;  // КПЛ
    } else if (format == "[П]{К}(Л)") {
        type = TraversalType::ReverseInOrder;   // ПКЛ
    } else if (format == "[П](Л){К}") {
        type = TraversalType::ReversePostOrder; // ПЛК
    }
    
    // Извлекаем все сегменты между {}, () и []
    std::vector<std::string> segments;
    for (size_t i = 0; i < str.size(); ++i) {
        char open = str[i];
        char close = 0;
        if (open == '{') close = '}';
        else if (open == '(') close = ')';
        else if (open == '[') close = ']';
        else continue;
        size_t end = str.find(close, i + 1);
        if (end == std::string::npos) break;
        segments.emplace_back(str.substr(i + 1, end - i - 1));
        i = end;
    }
    
    // Вставляем значения в дерево
    for (const auto& token : segments) {
        try {
            T value = valueFromString<T>(token);
            result.insert(value);
        } catch (const std::exception&) {
            // пропускаем некорректные элементы
        }
    }
    
    return result;
}

// 1.5.3 Чтение из строки в формате списка пар «узел-родитель»
template <typename T>
BinarySearchTree<T> BinarySearchTree<T>::fromNodeParentPairs(const std::vector<std::pair<T, T>>& pairs) {
    BinarySearchTree<T> result;
    if (pairs.empty()) return result;
    // Список узлов
    std::vector<std::pair<T, Node*>> nodeList;
    auto getNode = [&](const T& value) -> Node* {
        for (auto& pr : nodeList) {
            if (pr.first == value) return pr.second;
        }
        Node* n = new Node(value);
        nodeList.emplace_back(value, n);
        return n;
    };
    std::vector<T> children, parents;
    // Создаем узлы и собираем значения
    for (auto& pr : pairs) {
        getNode(pr.first);
        getNode(pr.second);
        children.push_back(pr.first);
        parents.push_back(pr.second);
    }
    // Находим корневое значение
    T rootValue = parents[0];
    for (T pv : parents) {
        bool found = false;
        for (T cv : children) {
            if (cv == pv) { found = true; break; }
        }
        if (!found) { rootValue = pv; break; }
    }
    // Привязываем потомков к родителям
    for (auto& pr : pairs) {
        Node* child = getNode(pr.first);
        Node* parent = getNode(pr.second);
        child->parent = parent;
        if (pr.first < pr.second) parent->left = child;
        else parent->right = child;
    }
    result.root = getNode(rootValue);
    result.size = nodeList.size();
    return result;
}

// 1.6 Извлечение поддерева (по заданному корню)
template <typename T>
BinarySearchTree<T> BinarySearchTree<T>::extractSubtree(const T& value) {
    BinarySearchTree<T> result;
    
    // Находим узел, который будет корнем поддерева
    Node* subtreeRoot = findNode(root, value);
    if (subtreeRoot == nullptr) {
        return result; // Пустое дерево, если элемент не найден
    }
    
    // Клонируем поддерево
    result.root = cloneTree(subtreeRoot);
    
    // Подсчитываем размер поддерева
    result.size = 0;
    result.traverse(TraversalType::PreOrder, [&result](const T&) {
        result.size++;
    });
    
    return result;
}

// 1.7 Поиск на вхождение поддерева
template <typename T>
bool BinarySearchTree<T>::areIdentical(Node* node1, Node* node2) const {
    // Если оба узла пусты, они идентичны
    if (node1 == nullptr && node2 == nullptr) {
        return true;
    }
    
    // Если только один из узлов пуст, они не идентичны
    if (node1 == nullptr || node2 == nullptr) {
        return false;
    }
    
    // Проверяем текущие узлы и рекурсивно их поддеревья
    return (node1->data == node2->data) &&
           areIdentical(node1->left, node2->left) &&
           areIdentical(node1->right, node2->right);
}

// Поиск на вхождение поддерева
template <typename T>
bool BinarySearchTree<T>::isSubtree(Node* tree, Node* subtree) const {
    // Пустое поддерево всегда является частью любого дерева
    if (subtree == nullptr) {
        return true;
    }
    
    // Если основное дерево пусто, а поддерево нет, то поддерево не может быть частью дерева
    if (tree == nullptr) {
        return false;
    }
    
    // Проверяем, идентично ли текущее дерево поддереву
    if (areIdentical(tree, subtree)) {
        return true;
    }
    
    // Проверяем, является ли поддерево частью левого или правого поддерева
    return isSubtree(tree->left, subtree) || isSubtree(tree->right, subtree);
}

// 1.7 Поиск на вхождение поддерева
template <typename T>
bool BinarySearchTree<T>::containsSubtree(const BinarySearchTree<T>& subtree) const {
    if (subtree.root == nullptr) {
        return true; // Пустое поддерево всегда является частью любого дерева
    }
    
    if (root == nullptr) {
        return false; // Если наше дерево пусто, а поддерево нет, то поддерево не может быть частью дерева
    }
    
    // Ищем корень поддерева в нашем дереве
    Node* node = findNode(root, subtree.root->data);
    if (node == nullptr) {
        return false; // Корень поддерева не найден в нашем дереве
    }
    
    // Проверяем, идентичны ли структуры деревьев, начиная с найденного узла
    return isSubtree(node, subtree.root);
}

// Вывод дерева в консоль (для отладки)
template <typename T>
void BinarySearchTree<T>::printTree() const {
    if (root == nullptr) {
        std::cout << "Дерево пусто" << std::endl;
        return;
    }
    
    std::cout << "Бинарное дерево поиска (размер: " << size << "):" << std::endl;
    
    // Используем уровневый обход для вывода
    std::queue<std::pair<Node*, int>> q; // пары (узел, уровень)
    q.push(std::make_pair(root, 0));
    
    int currentLevel = -1;
    
    while (!q.empty()) {
        Node* node = q.front().first;
        int level = q.front().second;
        q.pop();
        
        if (level > currentLevel) {
            currentLevel = level;
            std::cout << "Уровень " << level << ": ";
        }
        
        std::cout << valueToString(node->data) << " ";
        
        if (node->left) q.push(std::make_pair(node->left, level + 1));
        if (node->right) q.push(std::make_pair(node->right, level + 1));
        
        if (q.empty() || q.front().second > level) {
            std::cout << std::endl;
        }
    }
}

#endif // BINARY_SEARCH_TREE_H 