#include <iostream>
#include "string"
#include "tuple"
#include "optional"
#include "ostream"
#include "vector"
#include "fstream"
#include "cstdlib"
#include "algorithm"

//    Создайте структуру Person с 3 полями: фамилия, имя, отчество. Поле отчество должно быть
//    опционального типа, т.к. не у всех людей есть отчество. Перегрузите оператор вывода данных
//    для этой структуры. Также перегрузите операторы < и == (используйте tie).

struct Person {
    // параметры
    std::string surname{};
    std::string name{};
    std::string patronymic{};

    // перегрузка оператора сравнения через кортеж
    bool operator<(Person &_second) {
        bool result{};
        result = std::tie(surname, name, patronymic)
                 < std::tie(_second.surname, _second.name, _second.patronymic);

        return result;
    }

    // перегрузка оператора сравнения через кортеж
    bool operator==(Person &_second) {
        bool result{};
        result = std::tie(surname, name, patronymic)
                 == std::tie(_second.surname, _second.name, _second.patronymic);

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const Person &_p_struct) {
    return out << _p_struct.surname << " "
               << _p_struct.name << " "
               << _p_struct.patronymic << " ";
}

//Создайте структуру PhoneNumber с 4 полями:
//· код страны (целое число)
//· код города (целое число)
//· номер (строка)
//· добавочный номер (целое число, опциональный тип)
//Для этой структуры перегрузите оператор вывода. Необходимо, чтобы номер телефона
//выводился в формате: +7(911)1234567 12, где 7 – это номер страны, 911 – номер города,
//1234567 – номер, 12 – добавочный номер. Если добавочного номера нет, то его выводить ненадо.

struct PhoneNumber {
    int country_code{};
    int city_code{};
    std::string number{};
    std::optional<int> extension_number{};

    bool operator<(PhoneNumber &_second) {
        bool result{};
        result = std::tie(country_code, city_code, number, extension_number)
                 < std::tie(_second.country_code, _second.city_code, _second.number, _second.extension_number);
        return result;
    }

    bool operator==(PhoneNumber &_second) {
        bool result{};
        result = std::tie(country_code, city_code, number, extension_number)
                 == std::tie(_second.country_code, _second.city_code, _second.number, _second.extension_number);
        return result;
    }

};

std::ostream &operator<<(std::ostream &out, const PhoneNumber &_p_n_struct) {
    return out << "+" << _p_n_struct.country_code << "(" << _p_n_struct.city_code << ")"
               << _p_n_struct.number << _p_n_struct.extension_number.value();
}

//Создайте класс PhoneBook, который будет в контейнере хранить пары: Человек – Номер
//телефона. Конструктор этого класса должен принимать параметр типа ifstream – поток данных,
//полученных из файла. В теле конструктора происходит считывание данных из файла и 25 заполнение контейнера.

//Класс PhoneBook должен содержать перегруженный оператор
//вывода, для вывода всех данных из контейнера в консоль.

//В классе PhoneBook реализуйте метод SortByName, который должен сортировать элементы
//контейнера по фамилии людей в алфавитном порядке. Если фамилии будут одинаковыми, то
//сортировка должна выполняться по именам, если имена будут одинаковы, то сортировка
//производится по отчествам. Используйте алгоритмическую функцию sort.

//Реализуйте метод SortByPhone, который должен сортировать элементы контейнера по
//номерам телефонов. Используйте алгоритмическую функцию sort.

//Реализуйте метод GetPhoneNumber, который принимает фамилию человека, а возвращает
//кортеж из строки и PhoneNumber. Строка должна быть пустой, если найден ровно один
//человек с заданном фамилией в списке. Если не найден ни один человек с заданной
//фамилией, то в строке должна быть запись «not found», если было найдено больше одного
//человека, то в строке должно быть «found more than 1».

//Реализуйте метод ChangePhoneNumber, который принимает человека и новый номер
//телефона и, если находит заданного человека в контейнере, то меняет его номер телефона на
//новый, иначе ничего не делает.

std::string GetWord(std::ifstream &_inter_file) {
    std::string str;
    if (_inter_file.is_open() && !_inter_file.eof()) {
        char a;
        while (!_inter_file.eof() && (a = _inter_file.get()) != ' ' && a != '\n' && a != '\t' && a != '\r')
            str += a;
        return str;
    }
    return str = "";
}

class PhoneBook {
private:
    std::vector<std::pair<Person, PhoneNumber>> _phone_book{};

public:
    PhoneBook(std::ifstream &_inter_file) {
        if (_inter_file.is_open()) {
            while (!_inter_file.eof()) {
                std::pair<Person, PhoneNumber> spam_return_pair{};
                Person spam_person{};
                PhoneNumber spam_phone_number{};
                while (!_inter_file.eof()) {
                    spam_person.surname = GetWord(_inter_file);
                    spam_person.name = GetWord(_inter_file);
                    spam_person.patronymic = GetWord(_inter_file);

                    spam_phone_number.country_code = atoi(GetWord(_inter_file).c_str());
                    spam_phone_number.city_code = atoi(GetWord(_inter_file).c_str());
                    spam_phone_number.number = GetWord(_inter_file);
                    spam_phone_number.extension_number = atoi(GetWord(_inter_file).c_str());
                }

                spam_return_pair.first = spam_person;
                spam_return_pair.second = spam_phone_number;
                _phone_book.push_back(spam_return_pair);
            }
        } else {
            std::cout << "Reading fail" << std::endl;
        }
    }

    void print_book() const {
        for (const std::pair<Person, PhoneNumber>& item: _phone_book) {
            std::cout << item.first << item.second << std::endl;
        }
    }

    ~PhoneBook() = default;

    std::vector<std::pair<Person, PhoneNumber>> &GetPhoneBook() {
        return _phone_book;
    };


    void SortByName() {
        std::sort(_phone_book.begin(), _phone_book.end(),
                  [](std::pair<Person, PhoneNumber> &item_1, std::pair<Person, PhoneNumber> &item_2) {
                      return item_1.first < item_2.first;
                  });
    }


    void SortByPhone() {
        std::sort(_phone_book.begin(), _phone_book.end(),
                  [](std::pair<Person, PhoneNumber> &item_1, std::pair<Person, PhoneNumber> &item_2) {
                      return item_1.second < item_2.second;
                  });
    }

    std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string &surname) {
        int counter = 0;
        PhoneNumber num;
        for (const auto& record: _phone_book)
            if (surname == record.first.surname) {
                counter++;
                num = record.second;
            }

        switch (counter) {
            case 0:
                return std::make_tuple("not found", num);
            case 1:
                return std::make_tuple("", num);
            default:
                return std::make_tuple("found more then 1", num);
        }
    }


    void ChangePhoneNumber(const Person &person, const PhoneNumber& newPhone) {
        for (auto & i : _phone_book)
            if ((const_cast<Person &>(person)) == i.first)
                i.second = newPhone;
    }
};

std::ostream &operator<<(std::ostream &out, PhoneBook &book) {
    std::for_each(book.GetPhoneBook().begin(), book.GetPhoneBook().end(), [&](std::pair<Person, PhoneNumber> &record) {
        out << record.first << "\t" << record.second << std::endl;
    });
    return out;

};


int main() {

    //
    std::ifstream file("PhoneBook.txt");
    PhoneBook book(file);
    std::cout << book;

    //
    std::cout << "------------SortByPhone-------------" << std::endl;
    book.SortByPhone();
    std::cout << book;

    //
    std::cout << "------------SortByName-------------" << std::endl;
    book.SortByName();
    std::cout << book;

    //
    std::cout << "------------GetPhoneNumber-------------" << std::endl;

    auto print_phone_number = [&book](const std::string& surname){
        std::cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);

        if(std::get<0>(answer).empty())
            std::cout << std::get<1>(answer);
        else
            std::cout << std::get<0>(answer);
        std::cout << std::endl;
    };

    print_phone_number("Ivanov");
    print_phone_number("Petrov ");

    //
    std::cout << "------------ChangePhoneNumber-------------" << std::endl;
    book.ChangePhoneNumber(Person{"Kotov", "Vasilii", "Eliseevich"},
                           PhoneNumber{7,123,"15344458", std::nullopt});
    book.ChangePhoneNumber(Person{"Mironova", "Margarita", "Vladimirovna"},
                           PhoneNumber{16,465,"9155448", 13});
    std::cout << book;

    return 0;
}
