#ifndef BINARY_HEAP_WRAPPER_H
#define BINARY_HEAP_WRAPPER_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <random>
#include "binary_heap.h"

// Абстрактный класс для унифицированного доступа к бинарной куче
class AbstractHeapWrapper {
public:
    virtual ~AbstractHeapWrapper() {}
    
    virtual void insert(const std::string& valueStr) = 0;
    virtual bool remove(const std::string& valueStr) = 0;
    virtual bool search(const std::string& valueStr) = 0;
    virtual void printHeap() const = 0;
    virtual size_t getSize() const = 0;
    virtual void clear() = 0;
    virtual std::string toString() const = 0;
    virtual std::string toStringFormatted(const std::string& format) const = 0;
    virtual std::string toNodeParentPairs() const = 0;
    virtual std::shared_ptr<AbstractHeapWrapper> extractSubHeap(const std::string& valueStr) = 0;
    virtual bool containsSubHeap(const AbstractHeapWrapper& subheap) const = 0;
    virtual void fillWithRandomValues(int count, const std::string& minStr, const std::string& maxStr) = 0;
    virtual std::string extractMax() = 0;
    virtual std::string top() const = 0;
    virtual std::shared_ptr<AbstractHeapWrapper> fromString(const std::string& str) = 0;
    virtual std::shared_ptr<AbstractHeapWrapper> fromStringFormatted(const std::string& str, const std::string& format) = 0;
    virtual std::shared_ptr<AbstractHeapWrapper> fromNodeParentPairs(const std::string& pairsStr) = 0;
};

// Шаблонный класс обертки для конкретной кучи
template <typename T>
class HeapWrapper : public AbstractHeapWrapper {
private:
    BinaryHeap<T> heap;
    
    // Преобразование строки в значение типа T
    T parseValue(const std::string& valueStr) const {
        return valueFromString<T>(valueStr);
    }
    
public:
    HeapWrapper() : heap() {}
    
    void insert(const std::string& valueStr) override {
        try {
            T value = parseValue(valueStr);
            heap.insert(value);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при вставке: " << e.what() << std::endl;
        }
    }
    
    bool remove(const std::string& valueStr) override {
        try {
            T value = parseValue(valueStr);
            return heap.remove(value);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при удалении: " << e.what() << std::endl;
            return false;
        }
    }
    
    bool search(const std::string& valueStr) override {
        try {
            T value = parseValue(valueStr);
            return heap.search(value);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при поиске: " << e.what() << std::endl;
            return false;
        }
    }
    
    void printHeap() const override {
        heap.printHeap();
    }
    
    size_t getSize() const override {
        return heap.getSize();
    }
    
    void clear() override {
        heap.clear();
    }
    
    std::string toString() const override {
        return heap.toString();
    }
    
    std::string toStringFormatted(const std::string& format) const override {
        return heap.toStringFormatted(format);
    }
    
    std::string toNodeParentPairs() const override {
        return heap.toNodeParentPairs();
    }
    
    std::shared_ptr<AbstractHeapWrapper> extractSubHeap(const std::string& valueStr) override {
        try {
            T value = parseValue(valueStr);
            auto subheap = heap.extractSubHeap(value);
            
            auto result = std::make_shared<HeapWrapper<T>>();
            result->heap = subheap;
            return result;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при извлечении поддерева: " << e.what() << std::endl;
            return std::make_shared<HeapWrapper<T>>();
        }
    }
    
    bool containsSubHeap(const AbstractHeapWrapper& subheap) const override {
        try {
            // Проверяем, что subheap имеет тот же тип
            const HeapWrapper<T>* castedSubheap = dynamic_cast<const HeapWrapper<T>*>(&subheap);
            if (castedSubheap == nullptr) {
                return false; // Разные типы, не может быть поддеревом
            }
            
            return heap.containsSubHeap(castedSubheap->heap);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при проверке поддерева: " << e.what() << std::endl;
            return false;
        }
    }
    
    void fillWithRandomValues(int count, const std::string& minStr, const std::string& maxStr) override {
        // По умолчанию ничего не делаем, реализуется в специализациях
        std::cerr << "Заполнение случайными значениями не поддерживается для данного типа" << std::endl;
    }
    
    std::string extractMax() override {
        try {
            T maxValue = heap.extractMax();
            return valueToString(maxValue);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при извлечении максимального элемента: " << e.what() << std::endl;
            return "Ошибка";
        }
    }
    
    std::string top() const override {
        try {
            T topValue = heap.top();
            return valueToString(topValue);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при получении вершины кучи: " << e.what() << std::endl;
            return "Ошибка";
        }
    }
    
    std::shared_ptr<AbstractHeapWrapper> fromString(const std::string& str) override {
        try {
            auto result = std::make_shared<HeapWrapper<T>>();
            result->heap = BinaryHeap<T>::fromString(str);
            return result;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при чтении из строки: " << e.what() << std::endl;
            return std::make_shared<HeapWrapper<T>>();
        }
    }
    
    std::shared_ptr<AbstractHeapWrapper> fromStringFormatted(const std::string& str, const std::string& format) override {
        try {
            auto result = std::make_shared<HeapWrapper<T>>();
            result->heap = BinaryHeap<T>::fromStringFormatted(str, format);
            return result;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при чтении из форматированной строки: " << e.what() << std::endl;
            return std::make_shared<HeapWrapper<T>>();
        }
    }
    
    std::shared_ptr<AbstractHeapWrapper> fromNodeParentPairs(const std::string& pairsStr) override {
        try {
            auto result = std::make_shared<HeapWrapper<T>>();
            
            // Парсим строку вида "[(node1:parent1),(node2:parent2),...]"
            std::string content = pairsStr;
            if (content.size() >= 2) {
                content = content.substr(1, content.size() - 2); // Удаляем [ и ]
            } else {
                return result; // Пустая куча
            }
            
            std::vector<std::pair<T, T>> pairs;
            size_t pos = 0;
            
            while ((pos = content.find("(")) != std::string::npos) {
                size_t endPos = content.find(")", pos);
                if (endPos == std::string::npos) break;
                
                std::string pairStr = content.substr(pos + 1, endPos - pos - 1);
                size_t colonPos = pairStr.find(":");
                
                if (colonPos != std::string::npos) {
                    std::string nodeStr = pairStr.substr(0, colonPos);
                    std::string parentStr = pairStr.substr(colonPos + 1);
                    
                    T node = parseValue(nodeStr);
                    T parent = parseValue(parentStr);
                    
                    pairs.push_back({node, parent});
                }
                
                content.erase(0, endPos + 1);
            }
            
            result->heap = BinaryHeap<T>::fromNodeParentPairs(pairs);
            return result;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при чтении из списка пар: " << e.what() << std::endl;
            return std::make_shared<HeapWrapper<T>>();
        }
    }
    
    // Получить саму кучу
    BinaryHeap<T>& getHeap() {
        return heap;
    }
};

// Специализация для целых чисел
template<>
void HeapWrapper<int>::fillWithRandomValues(int count, const std::string& minStr, const std::string& maxStr) {
    try {
        int min = std::stoi(minStr);
        int max = std::stoi(maxStr);
        
        // Проверка на корректность границ
        if (min > max) {
            std::swap(min, max);
        }
        
        // Очищаем кучу перед заполнением
        heap.clear();
        
        // Генерируем случайные числа
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(min, max);
        
        for (int i = 0; i < count; ++i) {
            heap.insert(dist(gen));
        }
        
        std::cout << "Куча заполнена " << count << " случайными значениями в диапазоне [" 
                  << min << ", " << max << "]" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при заполнении случайными значениями: " << e.what() << std::endl;
    }
}

#endif // BINARY_HEAP_WRAPPER_H 