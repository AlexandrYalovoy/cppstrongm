#include <iostream>

#include "any"
#include "iomanip"
#include "vector"
#include "algorithm"
#include "fstream"
//#include "ostream"
#include "Timer.h"
#include <cstdlib>
#include "cctype"

#define MAX_POINTER        5

//Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения,
//на которые указывают эти указатели (нужно обменивать именно сами указатели, переменные должны оставаться
//в тех же адресах памяти).

template<typename T>
void print_swap(T *x, T *y) {
    std::cout << std::setw(MAX_POINTER) << x << std::setw(5) << *x << std::setw(MAX_POINTER) << y
    << std::setw(5) << *y << std::endl;
}

template<typename T>
void my_swap(T **x, T **y) {
    T *temp = *x;
    *x = *y;
    *y = temp;;
}

//Реализуйте шаблонную функцию SortPointers, которая принимает вектор указателей
//и сортирует указатели по значениям, на которые они указывают.

template<typename T>
void print_vector(std::vector<T> &v) {
    for (T el: v) {
        std::cout << std::setw(MAX_POINTER) << *el << std::setw(4);
    }
    std::cout << std::endl;
}

template<typename T>
void my_sort(std::vector<T> &v) {
    sort(v.begin(), v.end(), [](T lhs, T rhs) { return *lhs < *rhs; });
}

//Подсчитайте количество гласных букв в книге “Война и мир”. Для подсчета используйте 4 способа:

int for_for(std::string _road) {
    std::ifstream open_file(_road);

    if (open_file.is_open()) {
        int quantity_vowels{};
        std::string vowels_base = "aeiouy";
        std::string read_line{};

        while (!open_file.eof()) {
            getline(open_file,read_line);
            for (char line_char: read_line) {
                for (char volowes_i: vowels_base) {
                    if (std::tolower(line_char) == volowes_i) {
                        quantity_vowels++;
                    }
                }
            }
        }
        open_file.close();
//        std::cout << quantity_vowels << std::endl;
        return quantity_vowels;
    } else {
        std::cout << "Open fail" << std::endl;
        return -1;
    }
}

int switch_test(std::string _road) {
    std::ifstream open_file(_road);

    if (open_file.is_open()) {
        int quantity_vowels{};
        char spam_char{};

        while (!open_file.eof()) {
            open_file.get(spam_char);
            spam_char = tolower(spam_char);
            switch (spam_char) {
                case 'a':
                    quantity_vowels++;
                    break;
                case 'e':
                    quantity_vowels++;
                    break;
                case 'i':
                    quantity_vowels++;
                    break;
                case 'o':
                    quantity_vowels++;
                    break;
                case 'u':
                    quantity_vowels++;
                    break;
                case 'y':
                    quantity_vowels++;
                    break;
            }
        }
        open_file.close();
//        std::cout << quantity_vowels << std::endl;
        return quantity_vowels;
    } else {
        std::cout << "Open fail" << std::endl;
        return -1;
    }
}

int main() {
    std::cout << "L2_1" << std::endl;
    std::cout << std::endl;

    int *a = new int(6);
    int *b = new int(7);
    print_swap(a, b);
    my_swap(&a, &b);
    print_swap(a, b);
    delete a;
    delete b;

    std::cout << std::endl;
    std::cout << "END L2_1" << std::endl;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "L2_2" << std::endl;
    std::cout << std::endl;

    srand(time(NULL));
    std::vector<int *> vec;
    for (size_t i = 0; i < 10; ++i) {
        vec.push_back(new int(rand() % 100));
    }

    print_vector(vec);
    my_sort(vec);
    print_vector(vec);
    for (auto & i : vec) {
        delete i;
    }

    std::cout << std::endl;
    std::cout << "END L2_2" << std::endl;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "L2_3" << std::endl;
    std::cout << std::endl;

    int spam_quantity{};

    std::cout << "For - For" << std::endl;
    Timer tm("For - For");
    spam_quantity = for_for("..\\War and peace.txt");
    std::cout << spam_quantity << std::endl;
    tm.print();

    std::cout << "switch_test" << std::endl;
    tm.start("switch_test");
    spam_quantity = for_for("..\\War and peace.txt");
    std::cout << spam_quantity << std::endl;
    tm.print();


    return 0;
}
