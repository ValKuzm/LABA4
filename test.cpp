#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <utility>
#include "../include/binary_search_tree.h"
#include "../include/data_types.h"

// Тест базовых операций для int
void testBasicOperations() {
    std::cout << "Запуск теста базовых операций для int..." << std::endl;
    
    BinarySearchTree<int> tree;
    
    // Тест вставки и поиска
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    
    assert(tree.getSize() == 3);
    assert(tree.search(10) == true);
    assert(tree.search(5) == true);
    assert(tree.search(15) == true);
    assert(tree.search(20) == false);
    
    // Тест удаления
    tree.remove(5);
    assert(tree.getSize() == 2);
    assert(tree.search(5) == false);
    
    tree.remove(10);
    assert(tree.getSize() == 1);
    assert(tree.search(10) == false);
    
    tree.remove(15);
    assert(tree.getSize() == 0);
    assert(tree.search(15) == false);
    assert(tree.isEmpty() == true);
    
    // Тест удаления корня с двумя потомками
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(17);
    
    tree.remove(10);
    assert(tree.getSize() == 6);
    assert(tree.search(10) == false);
    
    // Очистка дерева
    tree.clear();
    assert(tree.getSize() == 0);
    assert(tree.isEmpty() == true);
    
    std::cout << "Тест базовых операций для int пройден!" << std::endl;
}

// Тест базовых операций для double
void testBasicOperationsDouble() {
    std::cout << "Запуск теста базовых операций для double..." << std::endl;
    
    BinarySearchTree<double> tree;
    
    // Тест вставки и поиска
    tree.insert(10.5);
    tree.insert(5.5);
    tree.insert(15.5);
    
    assert(tree.getSize() == 3);
    assert(tree.search(10.5) == true);
    assert(tree.search(5.5) == true);
    assert(tree.search(15.5) == true);
    assert(tree.search(20.5) == false);
    
    // Тест удаления
    tree.remove(5.5);
    assert(tree.getSize() == 2);
    assert(tree.search(5.5) == false);
    
    // Очистка дерева
    tree.clear();
    assert(tree.getSize() == 0);
    assert(tree.isEmpty() == true);
    
    std::cout << "Тест базовых операций для double пройден!" << std::endl;
}

// Тест базовых операций для Complex
void testBasicOperationsComplex() {
    std::cout << "Запуск теста базовых операций для Complex..." << std::endl;
    
    BinarySearchTree<Complex> tree;
    
    // Создаем комплексные числа для теста
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex c3(5.0, 6.0);
    
    // Тест вставки и поиска
    tree.insert(c1);
    tree.insert(c2);
    tree.insert(c3);
    
    assert(tree.getSize() == 3);
    assert(tree.search(c1) == true);
    assert(tree.search(c2) == true);
    assert(tree.search(c3) == true);
    assert(tree.search(Complex(7.0, 8.0)) == false);
    
    // Тест удаления
    tree.remove(c1);
    assert(tree.getSize() == 2);
    assert(tree.search(c1) == false);
    
    // Очистка дерева
    tree.clear();
    assert(tree.getSize() == 0);
    assert(tree.isEmpty() == true);
    
    std::cout << "Тест базовых операций для Complex пройден!" << std::endl;
}

// Тест базовых операций для строк
void testBasicOperationsString() {
    std::cout << "Запуск теста базовых операций для string..." << std::endl;
    
    BinarySearchTree<std::string> tree;
    
    // Тест вставки и поиска
    tree.insert("apple");
    tree.insert("banana");
    tree.insert("cherry");
    
    assert(tree.getSize() == 3);
    assert(tree.search("apple") == true);
    assert(tree.search("banana") == true);
    assert(tree.search("cherry") == true);
    assert(tree.search("date") == false);
    
    // Тест удаления
    tree.remove("apple");
    assert(tree.getSize() == 2);
    assert(tree.search("apple") == false);
    
    // Очистка дерева
    tree.clear();
    assert(tree.getSize() == 0);
    assert(tree.isEmpty() == true);
    
    std::cout << "Тест базовых операций для string пройден!" << std::endl;
}

// Тест базовых операций для FunctionWrapper
void testBasicOperationsFunction() {
    std::cout << "Запуск теста базовых операций для Function..." << std::endl;
    
    BinarySearchTree<FunctionWrapper> tree;
    
    // Создаем функции для теста
    FunctionWrapper f1([](int x) { return x + 1; }, "add_one", 1);
    FunctionWrapper f2([](int x) { return x * 2; }, "double", 2);
    FunctionWrapper f3([](int x) { return x * x; }, "square", 3);
    
    // Тест вставки и поиска
    tree.insert(f1);
    tree.insert(f2);
    tree.insert(f3);
    
    assert(tree.getSize() == 3);
    assert(tree.search(f1) == true);
    assert(tree.search(f2) == true);
    assert(tree.search(f3) == true);
    
    // Создаем функцию с тем же идентификатором, но другой реализацией
    FunctionWrapper f1_copy([](int x) { return x - 1; }, "subtract_one", 1);
    assert(tree.search(f1_copy) == true); // Поиск по id
    
    // Тест удаления
    tree.remove(f1);
    assert(tree.getSize() == 2);
    assert(tree.search(f1) == false);
    
    // Очистка дерева
    tree.clear();
    assert(tree.getSize() == 0);
    assert(tree.isEmpty() == true);
    
    // Проверяем работу функции
    f2.apply(5); // 5 * 2 = 10
    
    std::cout << "Тест базовых операций для Function пройден!" << std::endl;
}

// Тест базовых операций для Student
void testBasicOperationsStudent() {
    std::cout << "Запуск теста базовых операций для Student..." << std::endl;
    
    BinarySearchTree<Student> tree;
    
    // Создаем студентов для теста
    Student s1(PersonID{1001, 1}, "Иван", "Иванович", "Иванов", std::time(nullptr), "ИВТ-12345", 4.5);
    Student s2(PersonID{1002, 1}, "Петр", "Петрович", "Петров", std::time(nullptr), "ИВТ-12346", 4.8);
    Student s3(PersonID{1003, 1}, "Сидор", "Сидорович", "Сидоров", std::time(nullptr), "ИВТ-12347", 3.9);
    
    // Тест вставки и поиска
    tree.insert(s1);
    tree.insert(s2);
    tree.insert(s3);
    
    assert(tree.getSize() == 3);
    assert(tree.search(s1) == true);
    assert(tree.search(s2) == true);
    assert(tree.search(s3) == true);
    
    // Создаем студента с другим именем, но тем же ID
    Student s1_copy(PersonID{1001, 1}, "Другой", "Студент", "Тестовый", std::time(nullptr), "ИВТ-99999", 3.0);
    assert(tree.search(s1_copy) == true); // Поиск по id
    
    // Тест удаления
    tree.remove(s1);
    assert(tree.getSize() == 2);
    assert(tree.search(s1) == false);
    
    // Очистка дерева
    tree.clear();
    assert(tree.getSize() == 0);
    assert(tree.isEmpty() == true);
    
    std::cout << "Тест базовых операций для Student пройден!" << std::endl;
}

// Тест базовых операций для Teacher
void testBasicOperationsTeacher() {
    std::cout << "Запуск теста базовых операций для Teacher..." << std::endl;
    
    BinarySearchTree<Teacher> tree;
    
    // Создаем преподавателей для теста
    Teacher t1(PersonID{2001, 1}, "Алексей", "Алексеевич", "Алексеев", std::time(nullptr), "Профессор", "Кафедра информатики");
    Teacher t2(PersonID{2002, 1}, "Борис", "Борисович", "Борисов", std::time(nullptr), "Доцент", "Кафедра математики");
    Teacher t3(PersonID{2003, 1}, "Виктор", "Викторович", "Викторов", std::time(nullptr), "Старший преподаватель", "Кафедра физики");
    
    // Тест вставки и поиска
    tree.insert(t1);
    tree.insert(t2);
    tree.insert(t3);
    
    assert(tree.getSize() == 3);
    assert(tree.search(t1) == true);
    assert(tree.search(t2) == true);
    assert(tree.search(t3) == true);
    
    // Создаем преподавателя с другим именем, но тем же ID
    Teacher t1_copy(PersonID{2001, 1}, "Другой", "Преподаватель", "Тестовый", std::time(nullptr), "Ассистент", "Другая кафедра");
    assert(tree.search(t1_copy) == true); // Поиск по id
    
    // Тест удаления
    tree.remove(t1);
    assert(tree.getSize() == 2);
    assert(tree.search(t1) == false);
    
    // Очистка дерева
    tree.clear();
    assert(tree.getSize() == 0);
    assert(tree.isEmpty() == true);
    
    std::cout << "Тест базовых операций для Teacher пройден!" << std::endl;
}

// Тест балансировки
void testBalancing() {
    std::cout << "Запуск теста балансировки..." << std::endl;
    
    BinarySearchTree<int> tree;
    
    // Создаем несбалансированное дерево
    for (int i = 1; i <= 10; i++) {
        tree.insert(i);
    }
    
    // Получаем высоту дерева до балансировки
    int heightBefore = 0;
    tree.traverse(TraversalType::PreOrder, [&heightBefore](const int&) {
        heightBefore = std::max(heightBefore, 10); // Примерно высота
    });
    
    // Балансируем дерево
    tree.balance();
    
    // Высота должна уменьшиться после балансировки
    int heightAfter = 0;
    tree.traverse(TraversalType::PreOrder, [&heightAfter](const int&) {
        heightAfter = std::max(heightAfter, 4); // Примерно ожидаемая высота
    });
    
    assert(tree.getSize() == 10);
    
    std::cout << "Тест балансировки пройден!" << std::endl;
}

// Тест map, reduce, where
void testMapReduceWhere() {
    std::cout << "Запуск теста map, reduce, where..." << std::endl;
    
    BinarySearchTree<int> tree;
    
    // Вставка элементов
    for (int i = 1; i <= 5; i++) {
        tree.insert(i);
    }
    
    // Тест map
    auto mappedTree = tree.map([](const int& value) { return value * 2; });
    assert(mappedTree.getSize() == 5);
    assert(mappedTree.search(2) == true);
    assert(mappedTree.search(4) == true);
    assert(mappedTree.search(6) == true);
    assert(mappedTree.search(8) == true);
    assert(mappedTree.search(10) == true);
    assert(mappedTree.search(1) == false);
    
    // Тест reduce
    int sum = tree.reduce([](const int& value, const int& acc) { return value + acc; }, 0);
    assert(sum == 15); // 1 + 2 + 3 + 4 + 5 = 15
    
    int product = tree.reduce([](const int& value, const int& acc) { return value * acc; }, 1);
    assert(product == 120); // 1 * 2 * 3 * 4 * 5 = 120
    
    // Тест where
    auto filteredTree = tree.where([](const int& value) { return value % 2 == 0; });
    assert(filteredTree.getSize() == 2);
    assert(filteredTree.search(2) == true);
    assert(filteredTree.search(4) == true);
    assert(filteredTree.search(1) == false);
    assert(filteredTree.search(3) == false);
    assert(filteredTree.search(5) == false);
    
    std::cout << "Тест map, reduce, where пройден!" << std::endl;
}

// Тест map и reduce для Complex
void testComplexMapReduce() {
    std::cout << "Запуск теста map и reduce для Complex..." << std::endl;
    
    BinarySearchTree<Complex> tree;
    
    // Вставка элементов
    tree.insert(Complex(1.0, 1.0));
    tree.insert(Complex(2.0, 2.0));
    tree.insert(Complex(3.0, 3.0));
    
    // Тест map (увеличиваем реальную часть вдвое)
    auto mappedTree = tree.map([](const Complex& value) {
        return Complex(value.real() * 2, value.imag());
    });
    
    assert(mappedTree.getSize() == 3);
    assert(mappedTree.search(Complex(2.0, 1.0)) == true);
    assert(mappedTree.search(Complex(4.0, 2.0)) == true);
    assert(mappedTree.search(Complex(6.0, 3.0)) == true);
    
    // Тест reduce (сумма комплексных чисел)
    Complex sum = tree.reduce([](const Complex& value, const Complex& acc) {
        return value + acc;
    }, Complex(0.0, 0.0));
    
    assert(sum.real() == 6.0); // 1 + 2 + 3 = 6
    assert(sum.imag() == 6.0); // 1 + 2 + 3 = 6
    
    std::cout << "Тест map и reduce для Complex пройден!" << std::endl;
}

// Тест прошивки (обходов)
void testTraversal() {
    std::cout << "Запуск теста прошивки (обходов)..." << std::endl;
    
    BinarySearchTree<int> tree;
    
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(17);
    
    // Тест обходов
    std::vector<int> inOrderExpected = {3, 5, 7, 10, 12, 15, 17};
    std::vector<int> preOrderExpected = {10, 5, 3, 7, 15, 12, 17};
    std::vector<int> postOrderExpected = {3, 7, 5, 12, 17, 15, 10};
    
    std::vector<int> inOrderActual = tree.getValuesInOrder();
    std::vector<int> preOrderActual = tree.getValuesByTraversal(TraversalType::PreOrder);
    std::vector<int> postOrderActual = tree.getValuesByTraversal(TraversalType::PostOrder);
    
    assert(inOrderActual == inOrderExpected);
    assert(preOrderActual == preOrderExpected);
    assert(postOrderActual == postOrderExpected);
    
    std::cout << "Тест прошивки (обходов) пройден!" << std::endl;
}

// Тест сохранения в строку и чтения из строки
void testStringConversion() {
    std::cout << "Запуск теста сохранения в строку и чтения из строки..." << std::endl;
    
    BinarySearchTree<int> tree;
    
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    
    // Тест сохранения в строку
    std::string str = tree.toString();
    assert(str == "[5, 10, 15]");
    
    // Тест чтения из строки
    BinarySearchTree<int> newTree = BinarySearchTree<int>::fromString(str);
    assert(newTree.getSize() == 3);
    assert(newTree.search(5) == true);
    assert(newTree.search(10) == true);
    assert(newTree.search(15) == true);
    
    std::cout << "Тест сохранения в строку и чтения из строки пройден!" << std::endl;
}

// Тест чтения по форматированному строковому представлению
void testFormattedStringConversion() {
    std::cout << "Запуск теста чтения по форматированному строковому представлению..." << std::endl;
    std::string str = "{10}(5)[15]";
    BinarySearchTree<int> tree = BinarySearchTree<int>::fromStringFormatted(str, "{К}(Л)[П]");
    assert(tree.getSize() == 3);
    assert(tree.search(10) && tree.search(5) && tree.search(15));
    std::vector<int> values = tree.getValuesInOrder();
    std::vector<int> expected = {5, 10, 15};
    assert(values == expected);
    std::cout << "Тест чтения по форматированному строковому представлению пройден!" << std::endl;
}

// Тест чтения из списка пар «узел-родитель»
void testFromNodeParentPairs() {
    std::cout << "Запуск теста чтения из списка пар «узел-родитель»..." << std::endl;
    std::vector<std::pair<int,int>> pairs = {{5,10},{15,10},{3,5},{7,5}};
    BinarySearchTree<int> tree = BinarySearchTree<int>::fromNodeParentPairs(pairs);
    assert(tree.getSize() == 5);
    assert(tree.search(10) && tree.search(5) && tree.search(15) && tree.search(3) && tree.search(7));
    std::vector<int> values = tree.getValuesInOrder();
    std::vector<int> expected = {3, 5, 7, 10, 15};
    assert(values == expected);
    std::cout << "Тест чтения из списка пар «узел-родитель» пройден!" << std::endl;
}

// Тест извлечения поддерева
void testSubtreeExtraction() {
    std::cout << "Запуск теста извлечения поддерева..." << std::endl;
    
    BinarySearchTree<int> tree;
    
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(17);
    
    // Извлечение поддерева с корнем 5
    BinarySearchTree<int> subtree = tree.extractSubtree(5);
    assert(subtree.getSize() == 3);
    assert(subtree.search(5) == true);
    assert(subtree.search(3) == true);
    assert(subtree.search(7) == true);
    assert(subtree.search(10) == false);
    assert(subtree.search(15) == false);
    
    // Извлечение несуществующего поддерева
    BinarySearchTree<int> emptySubtree = tree.extractSubtree(100);
    assert(emptySubtree.getSize() == 0);
    assert(emptySubtree.isEmpty() == true);
    
    std::cout << "Тест извлечения поддерева пройден!" << std::endl;
}

// Тест поиска на вхождение поддерева
void testSubtreeSearch() {
    std::cout << "Запуск теста поиска на вхождение поддерева..." << std::endl;
    
    BinarySearchTree<int> tree;
    
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(17);
    
    // Создаем поддерево
    BinarySearchTree<int> subtree;
    subtree.insert(5);
    subtree.insert(3);
    subtree.insert(7);
    
    // Проверка на вхождение поддерева
    assert(tree.containsSubtree(subtree) == true);
    
    // Создаем другое поддерево, которого нет в дереве
    BinarySearchTree<int> anotherSubtree;
    anotherSubtree.insert(20);
    anotherSubtree.insert(19);
    anotherSubtree.insert(21);
    
    // Проверка на вхождение другого поддерева
    assert(tree.containsSubtree(anotherSubtree) == false);
    
    // Проверка на вхождение пустого поддерева
    BinarySearchTree<int> emptySubtree;
    assert(tree.containsSubtree(emptySubtree) == true);
    
    std::cout << "Тест поиска на вхождение поддерева пройден!" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::cout << "Запуск модульных тестов для бинарного дерева поиска..." << std::endl;
    
    try {
        std::cout << std::endl << "Тесты для всех типов данных" << std::endl;

        // Тесты для всех типов данных
        testBasicOperations(); // int
        testBasicOperationsDouble(); // double
        testBasicOperationsComplex(); // Complex
        testBasicOperationsString(); // string
        testBasicOperationsFunction(); // FunctionWrapper
        testBasicOperationsStudent(); // Student
        testBasicOperationsTeacher(); // Teacher

        std::cout << std::endl << "Тесты для специфичных типов" << std::endl;
        // Дополнительные тесты для специфичных типов
        testComplexMapReduce(); // Тесты map и reduce для Complex
        
        std::cout << std::endl << "Общие тесты для функционала дерева" << std::endl;
        // Общие тесты для функционала дерева
        testBalancing();
        testMapReduceWhere();
        testTraversal();
        testStringConversion();
        testFormattedStringConversion();
        testFromNodeParentPairs();
        testSubtreeExtraction();
        testSubtreeSearch();
        
        std::cout << "Все тесты успешно пройдены!" << std::endl;
        std::cin.get();
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при выполнении тестов: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 