#include <iostream>

#include "any"
#include "iomanip"
#include "vector"
#include "algorithm"
#include "fstream"
//#include "ostream"
#include "Timer.h"
#include <cstdlib>

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

//int For_For(std::ifstream &f) {
//    int counter = 0;
//    std::string str;
//    std::string vm = "aeiouy";
//    while (!f.eof()) {
//        getline(f, str);
//        for (char ch: vm) {
//            for (char s: str) {
//                if (ch == s) ++counter;
//            }
//        }
//    }
//    return counter;
//}

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

    std::string spam_c{};
    Timer tm("For - For");
    std::ifstream open_file("test.txt");
//    std::cout << For_For(file) << "   ";
    open_file.open("test.txt");
    if (open_file.is_open()) {
        open_file >> spam_c;
        std::cout << spam_c << std::endl;
        open_file.close();
    } else {
        std::cout << "Open fail" << std::endl;
    }


    tm.print();


    return 0;
}
