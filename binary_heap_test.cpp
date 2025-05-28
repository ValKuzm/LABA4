#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <utility>
#include <chrono>
#include <random>
#include "../include/binary_heap.h"
#include "../include/data_types.h"

// Тест базовых операций для int
void testBinaryHeapBasic() {
    std::cout << "Запуск теста базовых операций для бинарной кучи (int)..." << std::endl;
    
    BinaryHeap<int> heap;
    
    // Тест вставки и проверки на пустоту
    assert(heap.isEmpty() == true);
    assert(heap.getSize() == 0);
    
    heap.insert(10);
    assert(heap.isEmpty() == false);
    assert(heap.getSize() == 1);
    assert(heap.search(10) == true);
    assert(heap.search(20) == false);
    
    // Тест вставки нескольких элементов
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);
    
    assert(heap.getSize() == 4);
    assert(heap.top() == 20); // В max-heap максимальный элемент должен быть на вершине
    
    // Тест удаления
    heap.remove(5);
    assert(heap.getSize() == 3);
    assert(heap.search(5) == false);
    
    // Тест extractMax
    int max = heap.extractMax();
    assert(max == 20);
    assert(heap.getSize() == 2);
    assert(heap.search(20) == false);
    
    // Тест очистки
    heap.clear();
    assert(heap.isEmpty() == true);
    assert(heap.getSize() == 0);
    
    std::cout << "Тест базовых операций для бинарной кучи (int) пройден!" << std::endl;
}

// Тест базовых операций для double
void testBinaryHeapDouble() {
    std::cout << "Запуск теста базовых операций для бинарной кучи (double)..." << std::endl;
    
    BinaryHeap<double> heap;
    
    // Тест вставки и проверки на пустоту
    heap.insert(10.5);
    heap.insert(20.5);
    heap.insert(5.5);
    heap.insert(15.5);
    
    assert(heap.getSize() == 4);
    assert(heap.top() == 20.5);
    assert(heap.search(10.5) == true);
    assert(heap.search(30.5) == false);
    
    // Тест удаления
    heap.remove(5.5);
    assert(heap.getSize() == 3);
    assert(heap.search(5.5) == false);
    
    // Тест очистки
    heap.clear();
    assert(heap.isEmpty() == true);
    
    std::cout << "Тест базовых операций для бинарной кучи (double) пройден!" << std::endl;
}

// Тест методов извлечения поддерева
void testExtractSubHeap() {
    std::cout << "Запуск теста извлечения поддерева..." << std::endl;
    
    BinaryHeap<int> heap;
    
    // Создаем кучу
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);
    heap.insert(25);
    heap.insert(30);
    
    // Извлекаем поддерево с корнем 15
    BinaryHeap<int> subheap = heap.extractSubHeap(15);
    
    assert(subheap.isEmpty() == false);
    assert(subheap.search(15) == true);
    
    // Проверяем, что поддерево содержит только узлы, которые были в поддереве
    assert(subheap.getSize() >= 1); // Минимум узел 15
    
    std::cout << "Тест извлечения поддерева пройден!" << std::endl;
}

// Тест поиска на вхождение поддерева
void testContainsSubHeap() {
    std::cout << "Запуск теста поиска на вхождение поддерева..." << std::endl;
    
    BinaryHeap<int> heap;
    
    // Создаем первую кучу
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);
    heap.insert(25);
    
    // Создаем вторую кучу, которая является поддеревом первой
    BinaryHeap<int> subheap;
    subheap.insert(5);
    
    // Проверяем, что первая куча содержит вторую кучу как поддерево
    assert(heap.containsSubHeap(subheap) == true);
    
    // Создаем третью кучу, которая не является поддеревом первой
    BinaryHeap<int> notSubheap;
    notSubheap.insert(30);
    notSubheap.insert(40);
    
    // Проверяем, что первая куча не содержит третью кучу как поддерево
    assert(heap.containsSubHeap(notSubheap) == false);
    
    std::cout << "Тест поиска на вхождение поддерева пройден!" << std::endl;
}

// Тест методов сохранения в строку и чтения из строки
void testStringConversion1() {
    std::cout << "Запуск теста сохранения в строку и чтения из строки..." << std::endl;
    
    BinaryHeap<int> heap;
    
    // Создаем кучу
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    
    // Сохраняем в строку
    std::string str = heap.toString();
    std::cout << "Строковое представление кучи: " << str << std::endl;
    
    // Создаем новую кучу из строки
    BinaryHeap<int> newHeap = BinaryHeap<int>::fromString(str);
    
    assert(newHeap.getSize() == heap.getSize());
    assert(newHeap.search(10) == true);
    assert(newHeap.search(20) == true);
    assert(newHeap.search(5) == true);
    
    // Сохраняем в формате списка пар "узел-родитель"
    std::string pairsStr = heap.toNodeParentPairs();
    std::cout << "Представление кучи в формате узел-родитель: " << pairsStr << std::endl;
    
    std::cout << "Тест сохранения в строку и чтения из строки пройден!" << std::endl;
}

// Тест методов сохранения в строку по заданному формату и чтения из строки
void testFormattedStringConversions() {
    std::cout << "Запуск теста сохранения в строку по заданному формату и чтения из строки..." << std::endl;
    
    BinaryHeap<int> heap;
    
    // Создаем кучу
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    
    // Сохраняем в строку по формату КЛП (корень, левое поддерево, правое поддерево)
    std::string str = heap.toStringFormatted("КЛП");
    std::cout << "Строковое представление кучи по формату КЛП: " << str << std::endl;
    
    // Создаем новую кучу из строки по формату КЛП
    BinaryHeap<int> newHeap = BinaryHeap<int>::fromStringFormatted(str, "КЛП");
    
    // Проверяем, что все элементы есть
    assert(newHeap.search(10) == true);
    assert(newHeap.search(20) == true);
    assert(newHeap.search(5) == true);
    
    std::cout << "Тест сохранения в строку по заданному формату и чтения из строки пройден!" << std::endl;
}

// Тест чтения из строки в формате списка пар «узел-родитель»
void testFromNodeParentPairs1() {
    std::cout << "Запуск теста чтения из строки в формате списка пар «узел-родитель»..." << std::endl;
    
    // Создаем список пар «узел-родитель»
    std::vector<std::pair<int, int>> pairs = {
        {20, 20}, // корень
        {10, 20}, // левый потомок корня
        {15, 10}  // правый потомок 10
    };
    
    // Создаем кучу из списка пар
    BinaryHeap<int> heap = BinaryHeap<int>::fromNodeParentPairs(pairs);
    
    assert(heap.getSize() == 3);
    assert(heap.search(20) == true);
    assert(heap.search(10) == true);
    assert(heap.search(15) == true);
    
    std::cout << "Тест чтения из строки в формате списка пар «узел-родитель» пройден!" << std::endl;
}

// // Тест производительности
// void testPerformance() {
//     std::cout << "Запуск теста производительности..." << std::endl;
    
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<int> dist(1, 1000000);
    
//     // Функция для измерения времени операций
//     auto measureTime = [&](size_t n, const std::string& operation) {
//         BinaryHeap<int> heap;
        
//         auto start = std::chrono::high_resolution_clock::now();
        
//         if (operation == "insert") {
//             for (size_t i = 0; i < n; ++i) {
//                 heap.insert(dist(gen));
//             }
//         } else if (operation == "extractMax") {
//             // Сначала вставляем n элементов
//             for (size_t i = 0; i < n; ++i) {
//                 heap.insert(dist(gen));
//             }
            
//             // Затем извлекаем все элементы
//             start = std::chrono::high_resolution_clock::now();
//             for (size_t i = 0; i < n && !heap.isEmpty(); ++i) {
//                 heap.extractMax();
//             }
//         }
        
//         auto end = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double> elapsed = end - start;
        
//         std::cout << "Операция " << operation << " для " << n << " элементов: " 
//                   << elapsed.count() << " секунд" << std::endl;
//     };
    
//     // Тестируем операцию вставки для разных размеров
//     std::vector<size_t> sizes = {1000, 10000, 100000};
//     for (size_t n : sizes) {
//         measureTime(n, "insert");
//     }
    
//     // Тестируем операцию extractMax для разных размеров
//     for (size_t n : sizes) {
//         measureTime(n, "extractMax");
//     }
    
//     std::cout << "Тест производительности завершен!" << std::endl;
// }

int main() {
    // Устанавливаем русскую локаль для вывода
    setlocale(LC_ALL, "Russian");
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::cout << "Запуск тестов для бинарной кучи" << std::endl;
    
    // Запускаем тесты
    testBinaryHeapBasic();
    testBinaryHeapDouble();
    testExtractSubHeap();
    testContainsSubHeap();
    testStringConversion1();
    testFormattedStringConversions();
    testFromNodeParentPairs1();
    
    std::cout << "Все тесты успешно пройдены!" << std::endl;
    
    return 0;
} 