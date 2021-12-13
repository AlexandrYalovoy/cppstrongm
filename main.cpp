#include <iostream>
#include <sstream>
#include "set"
#include "vector"
#include "string"
#include "map"

// шаблонная функция для чтения всяческих массивов
template<class type_array>
void print_array(type_array _array) {
    for (auto &_item: _array) {
        std::cout << _item << std::endl;
    }
}

//    Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов,
//    и выводящую в консоль список уникальных слов (если слово повторяется больше 1 раза, то вывести его надо один раз).
//    Продемонстрировать работу функции, передав итераторы различных типов.

template<class T_begin, class T_end>
void unique_strings(T_begin _begin, T_end _end) {
    std::set<std::string> spam_set{};
    spam_set.insert(_begin, _end);
    print_array<std::set<std::string>>(spam_set);
}

//    Используя ассоциативный контейнер, напишите программу, которая будет считывать данные введенные пользователем
//    из стандартного потока ввода и разбивать их на предложения. Далее программа должна вывести пользователю
//    все предложения, отсортировав их по длине.

void sorting_words_from_stream() {
    std::multimap<size_t, std::string> spam_map{};

    std::string cin_temp{};
    std::string word{};

    std::cout << "inter string, inter 'qqt' -> Quit" << std::endl;

    do {
        std::getline(std::cin, cin_temp);
        std::istringstream ist(cin_temp);
        for (word; ist >> word; spam_map.insert({static_cast<size_t>(word.length()), word}));
    } while (word != "qqt");

    for (auto &_item: spam_map) {
        std::cout << "Key - " << _item.first << " " << "Value - " << _item.second << std::endl;
    }
}


int main() {
//    Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов,
//    и выводящую в консоль список уникальных слов (если слово повторяется больше 1 раза, то вывести его надо один раз).
//    Продемонстрировать работу функции, передав итераторы различных типов.

    std::cout << "Lesson5_1" << std::endl;

    std::vector<std::string> test_sequence{};
    test_sequence.reserve(10);
    test_sequence.emplace_back("1string1");
    test_sequence.emplace_back("2string22");
    test_sequence.emplace_back("3string333");
    test_sequence.emplace_back("4string4444");
    test_sequence.emplace_back("5string55555");
    test_sequence.emplace_back("6string______");
    test_sequence.emplace_back("6string______");
    test_sequence.emplace_back("6string______");
    test_sequence.emplace_back("10string10");
    unique_strings(test_sequence.begin(), test_sequence.end());

    std::cout << std::endl;

    std::cout << "Lesson5_1" << std::endl;

//    Используя ассоциативный контейнер, напишите программу, которая будет считывать данные введенные пользователем
//    из стандартного потока ввода и разбивать их на предложения. Далее программа должна вывести пользователю
//    все предложения, отсортировав их по длине.

    sorting_words_from_stream();


    return 0;
}
