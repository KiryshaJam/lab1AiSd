#include <iostream>

class DynamicArray {
private:
    int* array;      // Указатель на массив
    int capacity;    // Ёмкость массива
    int size;        // Текущий размер массива

    // Метод для увеличения ёмкости массива
    void resize(int newCapacity) {
        int* newArray = new int[newCapacity];  // Выделяем новую память
        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i];            // Копируем старые данные
        }
        delete[] array;                        // Освобождаем старую память
        array = newArray;                      // Переназначаем указатель
        capacity = newCapacity;                // Обновляем ёмкость
    }

public:
    // Конструктор
    DynamicArray() {
        array = new int[2]; // Начальная ёмкость
        capacity = 2;
        size = 0;
    }

    // Деструктор для освобождения памяти
    ~DynamicArray() {
        delete[] array;
    }

    // Метод добавления элемента в конец массива
    void addElement(int element) {
        if (size == capacity) {
            resize(capacity * 2);  // Удваиваем ёмкость при переполнении
        }
        array[size] = element;
        ++size;
    }

    // Метод для вывода элемента по индексу
    void getElement(int index) const {
        if (index >= 0 && index < size) {
            std::cout << "Элемент на индексе " << index << ": " << array[index] << std::endl;
        } else {
            std::cout << "Индекс вне диапазона!" << std::endl;
        }
    }

    // Метод для добавления элемента по индексу
    void insertElement(int index, int element) {
        if (index < 0 || index > size) {
            std::cout << "Индекс вне диапазона!" << std::endl;
            return;
        }

        if (size == capacity) {
            resize(capacity * 2);  // Удваиваем ёмкость при переполнении
        }

        // Сдвигаем элементы вправо
        for (int i = size; i > index; --i) {
            array[i] = array[i - 1];
        }

        array[index] = element;
        ++size;
    }

    // Метод для вывода всего массива
    void printArray() const {
        std::cout << "Элементы массива: ";
        for (int i = 0; i < size; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

    // Метод для удаления массива
    void deleteArray() {
        delete[] array;  // Освобождаем выделенную память
        array = nullptr; // Устанавливаем указатель в nullptr
        size = 0;
        capacity = 0;
        std::cout << "Массив удален." << std::endl;
    }
};

int main() {
    DynamicArray myArray;

    // Пример использования методов
    myArray.addElement(10);
    myArray.addElement(20);
    myArray.addElement(30);
    myArray.printArray();

    myArray.getElement(1); // Получение элемента на индексе 1

    myArray.insertElement(1, 15); // Вставка элемента 15 на индекс 1
    myArray.printArray();

    myArray.deleteArray();
    myArray.printArray();

    return 0;
}