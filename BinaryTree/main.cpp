#include <iostream>
#include <functional>
#include "BinarySearchTree.h"
#include "IntTest.h"

// Тип данных в дереве
typedef float DataType;

void printMenu() {
    std::cout << "Меню:\n";
    std::cout << "1. Вставить значение\n";
    std::cout << "2. Удалить значение\n";
    std::cout << "3. Найти значение\n";
    std::cout << "4. Обходы\n";
    std::cout << "5. Напечатать дерево\n";
    std::cout << "6. Очистить дерево\n";
    std::cout << "7. Извлечь поддерево\n";
    std::cout << "8. Проверить наличие поддерева\n";
    std::cout << "9. Map (каждое значение умножается на 2)\n";
    std::cout << "10. Where (фильтрация элементов)\n";
    std::cout << "11. Слияние деревьев\n";
    std::cout << "12. Reduce (сумма всех элементов)\n";
    std::cout << "13. Тесты\n";
    std::cout << "14. Выйти\n";
    std::cout << "Выберите опцию: ";
}

void printTraversalMenu() {
    std::cout << "\nТипы обходов:\n";
    std::cout << "1. КЛП (Прямой обход)\n";
    std::cout << "2. КПЛ (Обратный прямой обход)\n";
    std::cout << "3. ЛПК (Прямой симметричный обход)\n";
    std::cout << "4. ЛКП (Обратный симметричный обход)\n";
    std::cout << "5. ПЛК (Прямой обратный обход)\n";
    std::cout << "6. ПКЛ (Обратный обратный обход)\n";
    std::cout << "Выберите тип обхода: ";
}

int main() {
    setlocale(LC_ALL, "ru");
    BinarySearchTree<DataType> bst;
    int choice;
    DataType value;

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
            do {
                printTraversalMenu();
                std::cin >> choice;

                switch (choice) {
                case 1:
                    std::cout << "Дерево (КЛП, Прямой обход):\n";
                    bst.printPreorder();
                    std::cout << std::endl;
                    break;

                case 2:
                    std::cout << "Дерево (КПЛ):\n";
                    bst.printReversePreorder();
                    std::cout << std::endl;
                    break;

                case 3:
                    std::cout << "Дерево (ЛПК):\n";
                    bst.printPostorder();
                    std::cout << std::endl;
                    break;

                case 4:
                    std::cout << "Дерево (ЛКП):\n";
                    bst.printReversePostorder();
                    std::cout << std::endl;
                    break;

                case 5:
                    std::cout << "Дерево (ПЛК):\n";
                    bst.printInorder();
                    std::cout << std::endl;
                    break;

                case 6:
                    std::cout << "Дерево (ПКЛ):\n";
                    bst.printReverseInorder();
                    std::cout << std::endl;
                    break;

                default:
                    std::cout << "Неверный выбор. Попробуйте снова.\n";
                    break;
                }

                std::cout << std::endl;
            } while (choice < 1 || choice > 6);

            break;

        case 5:
            std::cout << "Дерево:\n";
            bst.printTree();
            std::cout << std::endl;
            break;

        case 6:
            bst.clear();
            std::cout << "Дерево очищено.\n";
            break;

        case 7:
            std::cout << "Введите значение корня поддерева для извлечения: ";
            std::cin >> value;
            {
                BinarySearchTree<DataType> subtree = bst.extractSubtree(value);
                std::cout << "Извлеченное поддерево:\n";
                subtree.printTree();
            }
            break;

        case 8:
            std::cout << "Введите значения для проверки поддерева (окончание ввода -1):\n";
            {
                BinarySearchTree<DataType> subtree;
                while (true) {
                    std::cin >> value;
                    if (value == -1) break;
                    subtree.insert(value);
                }
                if (bst.containsSubtree(subtree)) {
                    std::cout << "Поддерево найдено.\n";
                }
                else {
                    std::cout << "Поддерево не найдено.\n";
                }
            }
            break;

        case 9:
        {
            std::cout << "map (каждое значение умножается на 2):\n";
            BinarySearchTree<DataType> newTree = bst.map<DataType>([](DataType value) { return value * 2; });
            std::cout << "Новое дерево:\n";
            newTree.printTree();
        }
        break;

        case 10:
        {
            std::cout << "where (оставляем только четные значения):\n";
            BinarySearchTree<DataType> filteredTree = bst.where([](const DataType& value) { return value > 4; });
            std::cout << "Новое дерево:\n";
            filteredTree.printTree();
        }
        break;

        case 11:
        {
            std::cout << "Введите значения для второго дерева для слияния (окончание ввода -1):\n";
            BinarySearchTree<DataType> otherTree;
            while (true) {
                std::cin >> value;
                if (value == -1) break;
                otherTree.insert(value);
            }
            BinarySearchTree<DataType> mergedTree = bst.merge(otherTree);
            std::cout << "Слитое дерево:\n";
            mergedTree.printTree();
        }
        break;

        case 12:
        {
            std::cout << "Reduce (сумма всех элементов):\n";
            DataType sum = bst.reduce<DataType>([](DataType acc, DataType value) { return acc + value; }, 0);
            std::cout << "Сумма всех элементов: " << sum << std::endl;
        }
        break;
        case 13:
        {
            IntBinarySearchTreeTest test;
            test.runAllTests();
        }
        break;
        case 14:
            std::cout << "Выход из программы.\n";
            break;
        
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }

        std::cout << std::endl;
    } while (choice != 14);

    return 0;
}