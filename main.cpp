#include <iostream>
#include "thread"
#include "mutex"
#include "chrono"
#include "vector"
#include "algorithm"

//    1. Создайте потокобезопасную оболочку для объекта cout. Назовите ее pcout. Необходимо, чтобы несколько потоков могли
//    обращаться к pcout и информация выводилась в консоль. Продемонстрируйте работу pcout.

std::mutex m_cout;

void pcout(std::string _string) {
    m_cout.lock();
    std::cout << _string << std::endl;
    m_cout.unlock();
}

//    2. Реализовать функцию, возвращающую i-ое простое число (например, миллионное простое число равно 15485863).
//    Вычисления реализовать во вторичном потоке. В консоли отображать прогресс вычисления.


// мутексы для второго задания не уверен что правильно понял как блочить
std::mutex m_even_number;
std::mutex m_n_even_number;
std::mutex m_is_end;

void search_n_even_number(size_t _n_number, size_t &_even_number, size_t &_n_even_number, bool &_is_end) {
    size_t n_count = 2;
    size_t search_number{};
    if (_n_number == 1) {
        m_cout.lock();
        std::cout << 2 << std::endl;
        m_cout.unlock();
    } else if (_n_number == 2) {
        m_cout.lock();
        std::cout << 3 << std::endl;
        m_cout.unlock();
    } else {
        size_t start_number = 4;
        while (_n_number != n_count) {
            size_t count_for_even{};
            for (size_t i = 2; i <= start_number; i++) {
                // если остаток от деления равен нулю увеличиваем счетчик
                if (start_number % i == 0) {
                    count_for_even++;
                }
                // если больше одного делителя заканчиваем поиск
                if (count_for_even > 1) {
                    break;
                }
            }
            // по завершению цикла увеличиваем стартовое число на 1
            start_number++;
            if (count_for_even == 1) {
                //берем число по ссылке по идеи его надо на этот момент времени заблокировать,
                // но это не точно просветите
                m_n_even_number.lock();
                _n_even_number = n_count;
                m_n_even_number.unlock();
                n_count++;
                search_number = start_number - 1;
            }
        }
        if (_n_number == n_count) {
            m_cout.lock();
            std::cout << "even number - " << search_number << std::endl;
            m_cout.unlock();
            m_even_number.lock();
            _even_number = search_number;
            m_even_number.unlock();
            m_is_end.lock();
            _is_end = true;
            m_is_end.unlock();
        }
    }
}

void print_stage_search(size_t &_n_even_number, bool &_is_end, size_t _n_number) {
    double result{};
    size_t n_even_number{};
    size_t n_number{};
    while (_is_end != true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // вот тут я крутил хвостом потом дошел до статик кастов, надо ли блочить ил нет не знаю.
        m_n_even_number.lock();
        n_even_number = _n_even_number;
        m_n_even_number.unlock();

        // вывод до конца в процентах в консоль
        result = ((static_cast<double>(n_even_number) / static_cast<double>(_n_number))) * 100;
        m_cout.lock();
        std::cout << "% done - " << result << std::endl;
        m_cout.unlock();
    }
}

void search_even_and_info(size_t _n_number) {
    bool is_end = false;
    size_t even_number{}; // сюда будем писать и брать по ссылке прочтое число
    size_t n_even_number{}; // сюда будем писать и брать по ссылке номер простого числа
    std::thread th_6_2_search(search_n_even_number, std::ref(_n_number), std::ref(even_number),
                              std::ref(n_even_number), std::ref(is_end));
    std::thread th_6_2_print(print_stage_search, std::ref(n_even_number), std::ref(is_end),
                            _n_number);
    th_6_2_search.join(); // будем ждать пока окончит
//    th_6_2_print.detach(); // не будем ждать пока окончит // мешало последующему.
    th_6_2_print.join();
}

//    3. Промоделировать следующую ситуацию. Есть два человека (2 потока): хозяин и вор. Хозяин приносит домой вещи
//    (функция добавляющая случайное число в вектор с периодичностью 1 раз в секунду). При этом у каждой вещи есть
//    своя ценность. Вор забирает вещи (функция, которая находит наибольшее число и удаляет из вектора с периодичностью
//    1 раз в 0.5 секунд), каждый раз забирает вещь с наибольшей ценностью.

int gen_int_number(size_t _range) {
    return rand() % _range + 1;
}

void add_rand_int_number_in_vector(std::vector<int> &_vector, size_t _quantity_number, size_t _range) {
    for (int i = 0; i <= _quantity_number ; ++i) {
        _vector.push_back(gen_int_number(_range));
    }
}

template<typename _type>
void print_array(_type &_array) {
    for (auto item: _array) {
        std::cout << item << ",";
    }
    std::cout << std::endl;
}

std::mutex m_vector;


void evro_gaz (std::vector<int> &_array, size_t _range) {
    while (!_array.empty()){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        m_vector.lock();
        _array.push_back(gen_int_number(_range));
        std::sort(_array.begin(), _array.end());
        print_array(_array);
        m_vector.unlock();
        if (_array.size() > 25) {
            break;
        }
    }
}

void ukraina_gaz(std::vector<int> &_array){
    while (!_array.empty()){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        m_vector.lock();
        _array.pop_back();
        print_array(_array);
        m_vector.unlock();
    }
}

void start_6_3(std::vector<int> &_array) {
    size_t range = 100;
    std::thread owner(evro_gaz, ref(_array), range);
    std::thread thief(ukraina_gaz, ref(_array));
    thief.join();
    owner.detach();
}


int main() {
//    1. Создайте потокобезопасную оболочку для объекта cout. Назовите ее pcout. Необходимо, чтобы несколько потоков могли
//    обращаться к pcout и информация выводилась в консоль. Продемонстрируйте работу pcout.
    std::cout << "///6.1///" << std::endl;
    std::cout << std::endl;

    std::thread th_6_1_1(pcout, "6.1.1");
    std::thread th_6_1_2(pcout, "6.1.2");
    th_6_1_1.join();
    th_6_1_2.join();

//    2. Реализовать функцию, возвращающую i-ое простое число (например, миллионное простое число равно 15485863).
//    Вычисления реализовать во вторичном потоке. В консоли отображать прогресс вычисления.

    std::cout << "///6.2///" << std::endl;
    search_even_and_info(10000);

//    3. Промоделировать следующую ситуацию. Есть два человека (2 потока): хозяин и вор. Хозяин приносит домой вещи
//    (функция добавляющая случайное число в вектор с периодичностью 1 раз в секунду). При этом у каждой вещи есть
//    своя ценность. Вор забирает вещи (функция, которая находит наибольшее число и удаляет из вектора с периодичностью
//    1 раз в 0.5 секунд), каждый раз забирает вещь с наибольшей ценностью.


    std::cout << "///6.3///" << std::endl;

    std::vector<int> vector_6_3;
    add_rand_int_number_in_vector(vector_6_3, 10, 100);
    print_array(vector_6_3);
    start_6_3(vector_6_3);
    print_array(vector_6_3);

    return 0;
}
