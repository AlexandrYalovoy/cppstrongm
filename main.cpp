#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>

std::random_device rd;
std::mt19937_64 random2(rd());

void printVecInt(const std::vector<int> &v) {
    for (const auto &i: v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

template<typename Container>
void printContainer(const Container &v) {
    for (const auto &i: v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

//Имеется отсортированный массив целых чисел. Необходимо разработать функцию insert_sorted, которая принимает вектор
//и новое число и вставляет новое число в определенную позицию в векторе, чтобы упорядоченность контейнера сохранялась.
//Реализуйте шаблонную функцию insert_sorted, которая сможет аналогично работать с любым контейнером, содержащим любой
//тип значения.

bool insert_sorted(std::vector<int> &v, int n) {
    if (*v.begin() < *(v.end() - 1)) {
        auto iter_position = std::lower_bound(v.begin(), v.end(), n);
        v.insert(iter_position, n);
        return true;
    } else {
        auto iter_position = std::lower_bound(v.rbegin(), v.rend(), n);
        v.insert(iter_position.base(), n);
    }
    return true;
}

template<typename Container, typename T>
bool insert_sorted(Container &v, T n) {
    std::vector<T> temp;

    for (const auto &i: v) {
        temp.push_back(i);
    }

    if (*temp.begin() < *(temp.end() - 1)) {
        auto it = std::lower_bound(temp.begin(), temp.end(), n);
        temp.insert(it, n);
    } else {
        auto it = std::lower_bound(temp.rbegin(), temp.rend(), n);
        temp.insert(it.base(), n);
    }

    v.clear();
    v.resize(temp.size());
    std::copy(temp.begin(), temp.end(), v.begin());

    return true;
}


template<typename Container, typename T>
bool insert_sorted2(Container &v, T n) {
    if (v.front() < v.back()) {
        auto it = std::lower_bound(v.begin(), v.end(), n);
        v.insert(it, n);
    } else {
        auto it = std::lower_bound(v.rbegin(), v.rend(), n);
        v.insert(it.base(), n);
    }
    return true;
}

int main() {

    std::cout << "Lesson 4_1" << std::endl;
    std::cout << "vector<int> func:" << std::endl;

    std::vector<int> v(20);
    std::generate(v.begin(), v.end(), []() { return ((random2() % 10000) / 300); });
    std::sort(v.begin(), v.end());

    printVecInt(v);
    std::cout << "Insert 15:" << std::endl;
    insert_sorted(v, 15);
    printVecInt(v);
    std::cout << "Reverse:" << std::endl;
    std::sort(v.rbegin(), v.rend());
    printVecInt(v);
    std::cout << "Insert 27:" << std::endl;
    insert_sorted(v, 27);
    printVecInt(v);
    std::cout << "--------------------------" << std::endl;

    std::list<int> ll = {2, 33, 66, 77, 99};
    std::forward_list<double> fl = {1.1, 5.5, 9.3, 16.9, 24.3};
    std::deque<int> de = {1, 5, 8, 12, 14};
    std::vector<double> vv = {1.1, 5.5, 9.3, 16.9, 24.3};

    std::cout << "Template func:" << std::endl;
    std::cout << "list<int>:" << std::endl;
    printContainer(ll);
    std::cout << "Insert 44:" << std::endl;
    insert_sorted(ll, 44);
    printContainer(ll);
    std::cout << "Reverse:" << std::endl;
    ll.reverse();
    printContainer(ll);
    std::cout << "Insert 68:" << std::endl;
    insert_sorted(ll, 68);
    printContainer(ll);
    std::cout << "--------------------------" << std::endl;

    std::cout << "forward_list<double>:" << std::endl;
    printContainer(fl);
    std::cout << "Insert 6.7:" << std::endl;
    insert_sorted(fl, 6.7);
    printContainer(fl);
    std::cout << "Reverse:" << std::endl;
    fl.reverse();
    printContainer(fl);
    std::cout << "Insert 11.3:" << std::endl;
    insert_sorted(fl, 11.3);
    printContainer(fl);
    std::cout << "--------------------------" << std::endl;

    std::cout << "deque<int>:" << std::endl;
    printContainer(de);
    std::cout << "Insert 6:" << std::endl;
    insert_sorted(de, 6);
    printContainer(de);
    std::cout << "Reverse:" << std::endl;
    std::sort(de.rbegin(), de.rend());
    printContainer(de);
    std::cout << "Insert 15:" << std::endl;
    insert_sorted(de, 15);
    printContainer(de);
    std::cout << "--------------------------" << std::endl;

    std::cout << "vector<double>:" << std::endl;
    printContainer(vv);
    std::cout << "Insert 0.5:" << std::endl;
    insert_sorted(vv, 0.5);
    printContainer(vv);
    std::cout << "Reverse:" << std::endl;
    std::sort(vv.rbegin(), vv.rend());
    printContainer(vv);
    std::cout << "Insert 15.3:" << std::endl;
    insert_sorted(vv, 15.3);
    printContainer(vv);
    std::cout << "--------------------------" << std::endl;

    std::cout << std::endl << std::endl;



//    Сгенерируйте вектор a, состоящий из 100 вещественный чисел, представляющий собой значения аналогового сигнала.
//    На основе этого массива чисел создайте другой вектор целых чисел b, представляющий цифровой сигнал,
//    в котором будут откинуты дробные части чисел. Выведите получившиеся массивы чисел. Посчитайте ошибку,
//    которой обладает цифровой сигнал по сравнению с аналоговым по формуле:

    std::cout << "Lesson 4_2" << std::endl;

    std::vector<double> rand_vect(100);
    std::generate(rand_vect.begin(), rand_vect.end(), []() { return ((double) (random2() % 10000) / 300); });
    std::cout << "vector<double> a:" << std::endl;
    printContainer(rand_vect);
    std::cout << std::endl;
    std::vector<int> b(100);
    std::copy(rand_vect.begin(), rand_vect.end(), b.begin());
    std::cout << "vector<int> b:" << std::endl;
    printContainer(b);

    // ошибка 1 вектор
    double sum = std::accumulate(rand_vect.begin(), rand_vect.end(), 0.0,
                                 [](double x, double y) {
                                     double t;
                                     return x + pow(modf(y, &t), 2.0);
                                 });

    std::cout << std::endl << "Error 1 vector: " << sum << std::endl;

    // ошибка 2 вектора
    double sum2 = std::inner_product(rand_vect.begin(), rand_vect.end(), b.begin(), 0.0,
                                     std::plus<double>(), [](double x, int y) { return pow((x - y), 2); });
    std::cout << std::endl << "Error 2 vector: " << sum2 << std::endl;

    std::cout << std::endl << std::endl;

    return 0;
}
