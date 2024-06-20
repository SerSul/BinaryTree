#include <locale>
#include "FloatTest.h"


#include <iostream>
#include <functional>
#include "BinarySearchTree.h" // Убедитесь, что ваш заголовочный файл подключен правильно

void printMenu() {
    std::cout << "Меню:\n";
    std::cout << "1. Вставить значение\n";
    std::cout << "2. Удалить значение\n";
    std::cout << "3. Найти значение\n";
    std::cout << "4. Напечатать дерево\n";
    std::cout << "5. Очистить дерево\n";
    std::cout << "6. Выйти\n";
    std::cout << "Выберите опцию: ";
}

int main() {
    setlocale(LC_ALL, "ru");
    BinarySearchTree<int> bst;
    int choice, value;

    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите значение для вставки: ";
            std::cin >> value;
            try {
                bst.insert(value);
                std::cout << "Значение вставлено.\n";
            }
            catch (const std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
            break;

        case 2:
            std::cout << "Введите значение для удаления: ";
            std::cin >> value;
            bst.remove(value);
            std::cout << "Значение удалено.\n";
            break;

        case 3:
            std::cout << "Введите значение для поиска: ";
            std::cin >> value;
            if (bst.find(value)) {
                std::cout << "Значение найдено.\n";
            }
            else {
                std::cout << "Значение не найдено.\n";
            }
            break;

        case 4:
            std::cout << "Дерево (прямой обход):\n";
            bst.printTree();
            break;

        case 5:
            bst.clear();
            std::cout << "Дерево очищено.\n";
            break;

        case 6:
            std::cout << "Выход из программы.\n";
            break;

        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
        std::cout << std::endl;
    } while (choice != 6);

    return 0;
}






/*
int main() {
    setlocale(LC_ALL, "ru");
    FloatTest test;
    test.testFind();
    test.testRemove();
    test.testMap();
    test.testWhere();
    test.testReduce();
    return 0;
}
*/