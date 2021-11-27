//
// Created by alexa on 27.11.2021.
//

#ifndef CPPSTRONGM_TIMER_H
#define CPPSTRONGM_TIMER_H

#include <chrono>
#include <iostream>
#include <utility>

class Timer {
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::string m_name;
    std::chrono::time_point<clock_t> m_beg;

    [[nodiscard]] double elapsed() const {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }

public:
    Timer() : m_beg(clock_t::now()) {}

    explicit Timer(std::string name) : m_name(std::move(name)), m_beg(clock_t::now()) {}

    void start(std::string name) {
        m_name = std::move(name);
        m_beg = clock_t::now();
    }

    void print() const {
        std::cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
    }
};

#endif //CPPSTRONGM_TIMER_H
