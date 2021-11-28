
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cstdlib>


//Написать функцию, добавляющую в конец списка вещественных чисел элемент, значение которого равно среднему
//арифметическому всех его элементов.
void Push_Arithmetic_Mean(std::list<double> &_list) {
    double result = 0;
    for (const auto item: _list) {
        result += item;
    }

    _list.push_back(result / static_cast<double>(_list.size()));
}

template<typename T>
void Print_Arr(T &_list) {
    for (const auto &item: _list) {
        std::cout << item << " ";
    }

    std::cout << std::endl;
}

//Создать класс, представляющий матрицу. Реализовать в нем метод, вычисляющий определитель матрицы.
class Matrix {
private:
    std::vector<int> m_data;
    int m_size{};

    static int Random(int min, int max) {
        int spam_number = rand() % (max - min) + min;
        return spam_number;
    }

    Matrix fillMatrixNew(int ind);

public:
    Matrix() = default;

    void fillMatrixRandom(int sz, int min, int max);

    void printMatrix();

    int getDeterminant();

    void push_back(int n) {
        m_data.push_back(n);
    }
};

void Matrix::fillMatrixRandom(int sz, int min, int max) {
    srand(time(nullptr));
    m_size = sz;
    for (int i = 0; i < sz * sz; i++)
        m_data.push_back(Random(min, max));
}

void Matrix::printMatrix() {
    int i = 0;
    for (const auto &el: m_data) {
        std::cout << std::setw(4) << el;
        i++;
        if (i == m_size) {
            std::cout << std::endl;
            i = 0;
        }
    }
    std::cout << std::endl;
}

int Matrix::getDeterminant() {
    if (m_size == 1) return m_data.front();
    int dt = 0;
    for (int i = 0; i < m_size; ++i) {
        Matrix temp = fillMatrixNew(i);
        dt += m_data[i] * temp.getDeterminant() * (i % 2 == 0 ? 1 : -1);
    }
    return dt;
}

Matrix Matrix::fillMatrixNew(int ind) {
    int i = 0;
    Matrix res;
    for (auto p = m_data.begin() + m_size; p < m_data.end(); ++p) {
        if (i != ind)
            res.push_back(*p);
        i++;
        if (i == m_size)
            i = 0;
    }
    res.m_size = m_size - 1;
    return res;
}

//Реализовать собственный класс итератора, с помощью которого можно будет проитерироваться
//по диапазону целых чисел в цикле for-range-based.
class My_class {
private:
    std::vector<int> m_data;
public:
    explicit My_class(std::vector<int> &v) : m_data(v) {}

    std::vector<int>::iterator begin() {
        return m_data.begin();
    }

    std::vector<int>::iterator end() {
        return m_data.end();
    }
};


int main() {
    std::cout << std::endl;
    std::cout << "3_1" << std::endl;
    std::list<double> test_list = {1.5, 0.2, -3.0, 4.6, 5.1};
    Push_Arithmetic_Mean(test_list);
    Print_Arr(test_list);

    std::cout << std::endl;
    std::cout << "3_2" << std::endl;
    Matrix mtrx{};
    mtrx.fillMatrixRandom(5, 0, 100);
    mtrx.printMatrix();
    std::cout << "Matrix\'s determinant is " << mtrx.getDeterminant() << std::endl;

    std::cout << std::endl;
    std::cout << std::endl << "3_3" << std::endl;
    std::vector<int> vec = {8, 4, 0, 2, 6};
    My_class test_my_class(vec);
    sort(test_my_class.begin(), test_my_class.end());
    Print_Arr(test_my_class);

    return 0;
}

