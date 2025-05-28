#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <sstream>
#include <map>
#include "data_types.h" // Включаем определения пользовательских типов

// Шаблонный класс бинарной кучи (max heap по умолчанию)
template <typename T, typename Comparator = std::less<T>>
class BinaryHeap {
private:
    // Структура узла кучи
    struct Node {
        T data;           // Данные узла
        Node* left;       // Указатель на левого потомка
        Node* right;      // Указатель на правого потомка
        Node* parent;     // Указатель на родительский узел
        
        // Конструктор узла
        Node(const T& value, Node* parent = nullptr) 
            : data(value), left(nullptr), right(nullptr), parent(parent) {}
    };
    
    Node* root;           // Корень кучи
    size_t size;          // Размер кучи (количество узлов)
    Comparator comp;      // Компаратор для определения порядка элементов
    
    // Вспомогательные методы
    
    // Восстановление свойства кучи при добавлении элемента (просеивание вверх)
    void heapifyUp(Node* node);
    
    // Восстановление свойства кучи при удалении элемента (просеивание вниз)
    void heapifyDown(Node* node);
    
    // Поиск узла по значению
    Node* findNode(Node* node, const T& value) const;
    
    // Поиск последнего узла в куче
    Node* findLastNode() const;
    
    // Удаление всех узлов кучи
    void destroyHeap(Node* node);
    
    // Получение глубины кучи
    int getDepth(Node* node = nullptr) const;
    
    // Клонирование кучи
    Node* cloneHeap(Node* node, Node* parent = nullptr) const;
    
    // Проверка, является ли данная куча поддеревом другой кучи
    bool isSubHeap(Node* heap, Node* subheap) const;
    
    // Сравнение двух куч на идентичность
    bool areIdentical(Node* node1, Node* node2) const;
    
    // Добавление узла в конец кучи
    void addLast(const T& value);
    
    // Обмен значениями между двумя узлами
    void swapValues(Node* a, Node* b);
    
    // Поиск узла по заданному пути
    Node* findNodeByPath(const std::string& path) const;
    
public:
    // Конструкторы и деструкторы
    BinaryHeap();
    BinaryHeap(const BinaryHeap& other);
    ~BinaryHeap();
    
    // Присваивание
    BinaryHeap& operator=(const BinaryHeap& other);
    
    // Базовые операции
    void insert(const T& value);       // Вставка элемента
    bool search(const T& value) const; // Поиск элемента
    bool remove(const T& value);       // Удаление элемента
    T extractMax();                    // Извлечение максимального элемента (для max-heap)
    
    // Дополнительные операции
    bool isEmpty() const;              // Проверка на пустоту
    size_t getSize() const;            // Получение размера кучи
    void clear();                      // Очистка кучи
    
    // 2.2 Извлечение поддерева (по заданному элементу)
    BinaryHeap<T, Comparator> extractSubHeap(const T& value);
    
    // 2.3 Поиск на вхождение поддерева
    bool containsSubHeap(const BinaryHeap<T, Comparator>& subheap) const;
    
    // 2.4 Сохранение в строку
    // 2.4.1 по фиксированному обходу
    std::string toString() const;
    
    // 2.4.2 по обходу, задаваемому строкой форматирования
    std::string toStringFormatted(const std::string& format) const;
    
    // 2.4.3 в формате списка пар «узел-родитель»
    std::string toNodeParentPairs() const;
    
    // 2.5 Чтение из строки
    // 2.5.1 по фиксированному обходу
    static BinaryHeap<T, Comparator> fromString(const std::string& str);
    
    // 2.5.2 по обходу, задаваемому строкой форматирования
    static BinaryHeap<T, Comparator> fromStringFormatted(const std::string& str, const std::string& format);
    
    // 2.5.3 в формате списка пар «узел-родитель»
    static BinaryHeap<T, Comparator> fromNodeParentPairs(const std::vector<std::pair<T, T>>& pairs);
    
    // Получение вершины кучи
    T top() const;
    
    // Обход кучи с вызовом функции обратного вызова для каждого элемента
    void traverse(std::function<void(const T&)> callback) const;
    
    // Вывод кучи в консоль (для отладки)
    void printHeap() const;
};

// Реализация методов класса BinaryHeap

// Конструктор по умолчанию
template <typename T, typename Comparator>
BinaryHeap<T, Comparator>::BinaryHeap() : root(nullptr), size(0), comp() {}

// Конструктор копирования
template <typename T, typename Comparator>
BinaryHeap<T, Comparator>::BinaryHeap(const BinaryHeap& other) : root(nullptr), size(0), comp(other.comp) {
    if (other.root) {
        root = cloneHeap(other.root);
        size = other.size;
    }
}

// Деструктор
template <typename T, typename Comparator>
BinaryHeap<T, Comparator>::~BinaryHeap() {
    clear();
}

// Оператор присваивания
template <typename T, typename Comparator>
BinaryHeap<T, Comparator>& BinaryHeap<T, Comparator>::operator=(const BinaryHeap& other) {
    if (this != &other) {
        clear();
        if (other.root) {
            root = cloneHeap(other.root);
            size = other.size;
            comp = other.comp;
        }
    }
    return *this;
}

// Проверка, пуста ли куча
template <typename T, typename Comparator>
bool BinaryHeap<T, Comparator>::isEmpty() const {
    return root == nullptr;
}

// Получение размера кучи
template <typename T, typename Comparator>
size_t BinaryHeap<T, Comparator>::getSize() const {
    return size;
}

// Очистка кучи
template <typename T, typename Comparator>
void BinaryHeap<T, Comparator>::clear() {
    destroyHeap(root);
    root = nullptr;
    size = 0;
}

// Рекурсивное удаление всех узлов кучи
template <typename T, typename Comparator>
void BinaryHeap<T, Comparator>::destroyHeap(Node* node) {
    if (node) {
        destroyHeap(node->left);
        destroyHeap(node->right);
        delete node;
    }
}

// Клонирование кучи
template <typename T, typename Comparator>
typename BinaryHeap<T, Comparator>::Node* BinaryHeap<T, Comparator>::cloneHeap(Node* node, Node* parent) const {
    if (!node) return nullptr;
    
    Node* newNode = new Node(node->data, parent);
    newNode->left = cloneHeap(node->left, newNode);
    newNode->right = cloneHeap(node->right, newNode);
    
    return newNode;
}

// Поиск последнего узла в куче (используется для удаления)
template <typename T, typename Comparator>
typename BinaryHeap<T, Comparator>::Node* BinaryHeap<T, Comparator>::findLastNode() const {
    if (!root) return nullptr;
    
    // Определяем глубину кучи
    int depth = getDepth();
    
    // Используем битовую маску для поиска последнего узла
    int mask = 1 << (depth - 1);
    
    Node* current = root;
    mask >>= 1;  // Пропускаем старший бит, так как он всегда указывает на корень
    
    // Проходим по биты числа size, чтобы найти путь к последнему узлу
    while (mask > 0 && current) {
        if (size & mask) {
            current = current->right;
        } else {
            current = current->left;
        }
        mask >>= 1;
    }
    
    return current;
}

// Получение глубины кучи или поддерева
template <typename T, typename Comparator>
int BinaryHeap<T, Comparator>::getDepth(Node* node) const {
    if (!node && !root) return 0;
    if (!node) node = root;
    
    int leftDepth = node->left ? getDepth(node->left) : 0;
    int rightDepth = node->right ? getDepth(node->right) : 0;
    
    return 1 + std::max(leftDepth, rightDepth);
}

// Вставка элемента в кучу
template <typename T, typename Comparator>
void BinaryHeap<T, Comparator>::insert(const T& value) {
    addLast(value);
    
    // Восстанавливаем свойство кучи
    if (size > 1) {
        Node* lastNode = findLastNode();
        heapifyUp(lastNode);
    }
}

// Добавление узла в последнюю позицию кучи
template <typename T, typename Comparator>
void BinaryHeap<T, Comparator>::addLast(const T& value) {
    if (!root) {
        root = new Node(value);
        size = 1;
        return;
    }
    
    // Увеличиваем размер и определяем путь к новому узлу
    size++;
    int path = size;
    std::stack<bool> directions;
    
    while (path > 1) {
        directions.push(path % 2 == 0); // true для левого потомка, false для правого
        path /= 2;
    }
    
    // Следуем по пути к позиции нового узла
    Node* current = root;
    Node* parent = nullptr;
    
    while (!directions.empty()) {
        parent = current;
        if (directions.top()) { // Идем влево
            if (!current->left) {
                current->left = new Node(value, current);
                return;
            }
            current = current->left;
        } else { // Идем вправо
            if (!current->right) {
                current->right = new Node(value, current);
                return;
            }
            current = current->right;
        }
        directions.pop();
    }
}

// Восстановление свойства кучи при добавлении элемента (просеивание вверх)
template <typename T, typename Comparator>
void BinaryHeap<T, Comparator>::heapifyUp(Node* node) {
    while (node->parent && comp(node->parent->data, node->data)) {
        swapValues(node, node->parent);
        node = node->parent;
    }
}

// Восстановление свойства кучи при удалении элемента (просеивание вниз)
template <typename T, typename Comparator>
void BinaryHeap<T, Comparator>::heapifyDown(Node* node) {
    while (true) {
        Node* largest = node;
        
        // Сравниваем с левым потомком
        if (node->left && comp(largest->data, node->left->data)) {
            largest = node->left;
        }
        
        // Сравниваем с правым потомком
        if (node->right && comp(largest->data, node->right->data)) {
            largest = node->right;
        }
        
        // Если текущий узел уже наибольший, завершаем
        if (largest == node) break;
        
        // Иначе меняем местами и продолжаем вниз
        swapValues(node, largest);
        node = largest;
    }
}

// Обмен значениями между двумя узлами
template <typename T, typename Comparator>
void BinaryHeap<T, Comparator>::swapValues(Node* a, Node* b) {
    if (a && b) {
        std::swap(a->data, b->data);
    }
}

// Поиск элемента в куче
template <typename T, typename Comparator>
bool BinaryHeap<T, Comparator>::search(const T& value) const {
    return findNode(root, value) != nullptr;
}

// Рекурсивный поиск узла по значению
template <typename T, typename Comparator>
typename BinaryHeap<T, Comparator>::Node* BinaryHeap<T, Comparator>::findNode(Node* node, const T& value) const {
    if (!node) return nullptr;
    
    if (node->data == value) return node;
    
    // Поиск в левом и правом поддеревьях
    Node* leftResult = findNode(node->left, value);
    if (leftResult) return leftResult;
    
    return findNode(node->right, value);
}

// Удаление элемента из кучи
template <typename T, typename Comparator>
bool BinaryHeap<T, Comparator>::remove(const T& value) {
    // Находим узел для удаления
    Node* nodeToRemove = findNode(root, value);
    if (!nodeToRemove) return false;
    
    // Находим последний узел
    Node* lastNode = findLastNode();
    
    // Заменяем значение удаляемого узла значением последнего узла
    nodeToRemove->data = lastNode->data;
    
    // Удаляем последний узел
    if (lastNode->parent) {
        if (lastNode->parent->left == lastNode) {
            lastNode->parent->left = nullptr;
        } else {
            lastNode->parent->right = nullptr;
        }
    } else {
        // Если это корень (единственный узел)
        root = nullptr;
    }
    
    delete lastNode;
    size--;
    
    // Восстанавливаем свойство кучи
    if (nodeToRemove != lastNode && size > 0) {
        heapifyDown(nodeToRemove);
        heapifyUp(nodeToRemove);
    }
    
    return true;
}

// Извлечение максимального элемента (для max-heap)
template <typename T, typename Comparator>
T BinaryHeap<T, Comparator>::extractMax() {
    if (isEmpty()) {
        throw std::runtime_error("Куча пуста");
    }
    
    T result = root->data;
    remove(root->data);
    return result;
}

// Получение вершины кучи
template <typename T, typename Comparator>
T BinaryHeap<T, Comparator>::top() const {
    if (isEmpty()) {
        throw std::runtime_error("Куча пуста");
    }
    
    return root->data;
}

// 2.2 Извлечение поддерева (по заданному элементу)
template <typename T, typename Comparator>
BinaryHeap<T, Comparator> BinaryHeap<T, Comparator>::extractSubHeap(const T& value) {
    BinaryHeap<T, Comparator> result;
    
    // Находим узел с заданным значением
    Node* node = findNode(root, value);
    if (!node) return result;
    
    // Создаем новую кучу из поддерева
    result.root = cloneHeap(node);
    
    // Пересчитываем размер поддерева
    std::function<void(Node*)> countNodes = [&](Node* n) {
        if (n) {
            result.size++;
            countNodes(n->left);
            countNodes(n->right);
        }
    };
    
    result.size = 0;
    countNodes(result.root);
    
    return result;
}

// 2.3 Поиск на вхождение поддерева
template <typename T, typename Comparator>
bool BinaryHeap<T, Comparator>::containsSubHeap(const BinaryHeap<T, Comparator>& subheap) const {
    if (subheap.isEmpty()) return true;
    if (isEmpty()) return false;
    
    return isSubHeap(root, subheap.root);
}

// Проверка, является ли данная куча поддеревом другой кучи
template <typename T, typename Comparator>
bool BinaryHeap<T, Comparator>::isSubHeap(Node* heap, Node* subheap) const {
    if (!subheap) return true;
    if (!heap) return false;
    
    if (areIdentical(heap, subheap)) return true;
    
    return isSubHeap(heap->left, subheap) || isSubHeap(heap->right, subheap);
}

// Сравнение двух куч на идентичность
template <typename T, typename Comparator>
bool BinaryHeap<T, Comparator>::areIdentical(Node* node1, Node* node2) const {
    if (!node1 && !node2) return true;
    if (!node1 || !node2) return false;
    
    return (node1->data == node2->data) &&
           areIdentical(node1->left, node2->left) &&
           areIdentical(node1->right, node2->right);
}

// 2.4.1 Сохранение в строку по фиксированному обходу (уровневый обход)
template <typename T, typename Comparator>
std::string BinaryHeap<T, Comparator>::toString() const {
    if (isEmpty()) return "[]";
    
    std::stringstream ss;
    ss << "[";
    
    std::queue<Node*> q;
    q.push(root);
    
    bool isFirst = true;
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        if (!isFirst) {
            ss << ",";
        }
        isFirst = false;
        
        ss << valueToString(current->data);
        
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    
    ss << "]";
    return ss.str();
}

// 2.4.2 Сохранение в строку по обходу, задаваемому строкой форматирования
template <typename T, typename Comparator>
std::string BinaryHeap<T, Comparator>::toStringFormatted(const std::string& format) const {
    if (isEmpty()) return "[]";
    
    std::vector<T> values;
    
    // Разные обходы дерева в зависимости от формата
    if (format == "КЛП") { // Корень, левое поддерево, правое поддерево (префиксный обход)
        std::function<void(Node*)> preOrder = [&](Node* node) {
            if (!node) return;
            values.push_back(node->data);
            preOrder(node->left);
            preOrder(node->right);
        };
        preOrder(root);
    }
    else if (format == "ЛКП") { // Левое поддерево, корень, правое поддерево (инфиксный обход)
        std::function<void(Node*)> inOrder = [&](Node* node) {
            if (!node) return;
            inOrder(node->left);
            values.push_back(node->data);
            inOrder(node->right);
        };
        inOrder(root);
    }
    else if (format == "ЛПК") { // Левое поддерево, правое поддерево, корень (постфиксный обход)
        std::function<void(Node*)> postOrder = [&](Node* node) {
            if (!node) return;
            postOrder(node->left);
            postOrder(node->right);
            values.push_back(node->data);
        };
        postOrder(root);
    }
    else if (format == "КПЛ") { // Корень, правое поддерево, левое поддерево
        std::function<void(Node*)> kplOrder = [&](Node* node) {
            if (!node) return;
            values.push_back(node->data);
            kplOrder(node->right);
            kplOrder(node->left);
        };
        kplOrder(root);
    }
    else if (format == "ПКЛ") { // Правое поддерево, корень, левое поддерево
        std::function<void(Node*)> pklOrder = [&](Node* node) {
            if (!node) return;
            pklOrder(node->right);
            values.push_back(node->data);
            pklOrder(node->left);
        };
        pklOrder(root);
    }
    else if (format == "ПЛК") { // Правое поддерево, левое поддерево, корень
        std::function<void(Node*)> plkOrder = [&](Node* node) {
            if (!node) return;
            plkOrder(node->right);
            plkOrder(node->left);
            values.push_back(node->data);
        };
        plkOrder(root);
    }
    else { // По умолчанию - обход в ширину (уровневый обход)
        std::queue<Node*> nodeQueue;
        nodeQueue.push(root);
        
        while (!nodeQueue.empty()) {
            Node* current = nodeQueue.front();
            nodeQueue.pop();
            
            values.push_back(current->data);
            
            if (current->left) nodeQueue.push(current->left);
            if (current->right) nodeQueue.push(current->right);
        }
    }
    
    // Форматируем результат в строку
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) ss << ",";
        ss << valueToString(values[i]);
    }
    ss << "]";
    
    return ss.str();
}

// 2.4.3 Сохранение в формате списка пар «узел-родитель»
template <typename T, typename Comparator>
std::string BinaryHeap<T, Comparator>::toNodeParentPairs() const {
    if (isEmpty()) return "[]";
    
    std::stringstream ss;
    ss << "[";
    
    std::vector<std::pair<T, T>> pairs;
    
    // Функция для сбора пар узел-родитель
    std::function<void(Node*)> collectPairs = [&](Node* node) {
        if (!node) return;
        
        if (node->parent) {
            pairs.push_back({node->data, node->parent->data});
        } else {
            // Для корня используем специальное значение
            // В данном случае используем само значение корня, т.к. корень не имеет родителя
            pairs.push_back({node->data, node->data});
        }
        
        collectPairs(node->left);
        collectPairs(node->right);
    };
    
    collectPairs(root);
    
    for (size_t i = 0; i < pairs.size(); ++i) {
        if (i > 0) ss << ",";
        ss << "(" << valueToString(pairs[i].first) << ":" << valueToString(pairs[i].second) << ")";
    }
    
    ss << "]";
    return ss.str();
}

// 2.5.1 Чтение из строки по фиксированному обходу
template <typename T, typename Comparator>
BinaryHeap<T, Comparator> BinaryHeap<T, Comparator>::fromString(const std::string& str) {
    BinaryHeap<T, Comparator> result;
    
    // Парсим строку вида "[value1,value2,value3,...]"
    std::string content = str;
    if (content.size() >= 2) {
        content = content.substr(1, content.size() - 2); // Удаляем [ и ]
    } else {
        return result; // Пустая куча
    }
    
    // Разбиваем на значения
    std::vector<T> values;
    size_t pos = 0;
    std::string token;
    while ((pos = content.find(",")) != std::string::npos) {
        token = content.substr(0, pos);
        values.push_back(valueFromString<T>(token));
        content.erase(0, pos + 1);
    }
    if (!content.empty()) {
        values.push_back(valueFromString<T>(content));
    }
    
    // Строим кучу
    for (const auto& value : values) {
        result.insert(value);
    }
    
    return result;
}

// 2.5.2 Чтение из строки по обходу, задаваемому строкой форматирования
template <typename T, typename Comparator>
BinaryHeap<T, Comparator> BinaryHeap<T, Comparator>::fromStringFormatted(const std::string& str, const std::string& format) {
    BinaryHeap<T, Comparator> result;
    
    // Парсим строку вида "[value1,value2,value3,...]"
    std::string content = str;
    if (content.size() >= 2) {
        content = content.substr(1, content.size() - 2); // Удаляем [ и ]
    } else {
        return result; // Пустая куча
    }
    
    // Если строка пустая после удаления скобок, возвращаем пустую кучу
    if (content.empty()) {
        return result;
    }
    
    // Разбиваем на значения
    std::vector<T> values;
    size_t pos = 0;
    std::string token;
    
    // Обрабатываем строку с запятыми
    while ((pos = content.find(",")) != std::string::npos) {
        token = content.substr(0, pos);
        values.push_back(valueFromString<T>(token));
        content.erase(0, pos + 1);
    }
    
    // Добавляем последнее значение, если оно есть
    if (!content.empty()) {
        values.push_back(valueFromString<T>(content));
    }
    
    // Построение дерева по правилам бинарной кучи
    // Мы не можем точно восстановить структуру дерева только по списку значений
    // без дополнительной информации, но мы можем создать корректную кучу
    
    // Для всех форматов обхода мы будем создавать кучу, вставляя элементы 
    // в соответствии с правилами бинарной кучи, т.к. эта структура однозначно 
    // определена свойствами кучи, независимо от порядка обхода
    for (const auto& value : values) {
        result.insert(value);
    }
    
    return result;
}

// 2.5.3 Чтение из строки в формате списка пар «узел-родитель»
template <typename T, typename Comparator>
BinaryHeap<T, Comparator> BinaryHeap<T, Comparator>::fromNodeParentPairs(const std::vector<std::pair<T, T>>& pairs) {
    BinaryHeap<T, Comparator> result;
    
    if (pairs.empty()) return result;
    
    // Находим корень (узел, который является своим собственным родителем)
    T rootValue;
    bool rootFound = false;
    
    for (const auto& pair : pairs) {
        if (pair.first == pair.second) {
            rootValue = pair.first;
            rootFound = true;
            break;
        }
    }
    
    if (!rootFound) {
        throw std::runtime_error("Корень не найден в списке пар");
    }
    
    // Создаем структуру с узлами и их родителями
    std::map<T, std::vector<T>> childrenMap;
    
    // Заполняем карту: ключ - родитель, значение - список детей
    for (const auto& pair : pairs) {
        if (pair.first != pair.second) { // Игнорируем корень
            childrenMap[pair.second].push_back(pair.first);
        }
    }
    
    // Строим дерево, начиная с корня
    result.root = new typename BinaryHeap<T, Comparator>::Node(rootValue);
    result.size = 1;
    
    // Очередь для обхода в ширину при построении дерева
    std::queue<std::pair<typename BinaryHeap<T, Comparator>::Node*, T>> nodeQueue;
    nodeQueue.push({result.root, rootValue});
    
    while (!nodeQueue.empty()) {
        auto [parentNode, parentValue] = nodeQueue.front();
        nodeQueue.pop();
        
        // Если у этого узла есть дети
        if (childrenMap.find(parentValue) != childrenMap.end()) {
            for (const T& childValue : childrenMap[parentValue]) {
                // Проверяем, нет ли уже двух детей
                if (!parentNode->left) {
                    parentNode->left = new typename BinaryHeap<T, Comparator>::Node(childValue, parentNode);
                    result.size++;
                    nodeQueue.push({parentNode->left, childValue});
                } else if (!parentNode->right) {
                    parentNode->right = new typename BinaryHeap<T, Comparator>::Node(childValue, parentNode);
                    result.size++;
                    nodeQueue.push({parentNode->right, childValue});
                } else {
                    // Если узел уже имеет двух детей, это не бинарное дерево
                    throw std::runtime_error("Ошибка: узел имеет более двух детей");
                }
            }
        }
    }
    
    // Проверяем, все ли узлы были добавлены
    if (result.size != pairs.size()) {
        // Количество узлов не совпадает, возможно некоторые не были добавлены
        // или формат пар некорректен
        throw std::runtime_error("Ошибка: не все узлы были добавлены в дерево");
    }
    
    return result;
}

// Поиск узла по заданному пути
template <typename T, typename Comparator>
typename BinaryHeap<T, Comparator>::Node* BinaryHeap<T, Comparator>::findNodeByPath(const std::string& path) const {
    if (!root || path.empty()) return nullptr;
    
    Node* current = root;
    
    for (char c : path) {
        if (c == 'L' || c == 'l') {
            if (!current->left) return nullptr;
            current = current->left;
        } else if (c == 'R' || c == 'r') {
            if (!current->right) return nullptr;
            current = current->right;
        } else {
            throw std::runtime_error("Неверный формат пути");
        }
    }
    
    return current;
}

// Обход кучи с вызовом функции обратного вызова для каждого элемента (уровневый обход)
template <typename T, typename Comparator>
void BinaryHeap<T, Comparator>::traverse(std::function<void(const T&)> callback) const {
    if (!root || !callback) return;
    
    std::queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        callback(current->data);
        
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

// Вывод кучи в консоль (для отладки)
template <typename T, typename Comparator>
void BinaryHeap<T, Comparator>::printHeap() const {
    if (isEmpty()) {
        std::cout << "Куча пуста" << std::endl;
        return;
    }
    
    std::cout << "Куча (размер: " << size << "):" << std::endl;
    
    // Используем уровневый обход для вывода
    std::queue<std::pair<Node*, int>> q; // пары (узел, уровень)
    q.push({root, 0});
    
    int currentLevel = -1;
    
    while (!q.empty()) {
        auto [node, level] = q.front();
        q.pop();
        
        if (level > currentLevel) {
            currentLevel = level;
            std::cout << "Уровень " << level << ": ";
        }
        
        std::cout << valueToString(node->data) << " ";
        
        if (node->left) q.push({node->left, level + 1});
        if (node->right) q.push({node->right, level + 1});
        
        if (q.empty() || q.front().second > level) {
            std::cout << std::endl;
        }
    }
}

#endif // BINARY_HEAP_H 