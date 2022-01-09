#pragma once

#ifndef _PERSON_H
#define _PERSON_H

#include <sstream>
#include <iostream>
#include <optional>
#include <tuple>

namespace PhoneBook{
    class Person {
    public:
        Person();
        Person(std::string surname, std::string name);
        Person(std::string surname, std::string name, std::string patronymic);

        void SetPerson(std::istringstream& line);

        std::string GetFullName();
        std::string& GetSurname();
        std::string& GetName();
        std::string& GetPatronymic();

        friend std::ostream& operator<< (std::ostream& out, const Person& person);
        friend bool operator< (const Person& personOne, const Person& personTwo);
        friend bool operator== (const Person& personOne, const Person& personTwo);

    private:
        std::string m_surname;
        std::string m_name;
        std::optional<std::string> m_patronymic;
    };

    std::ostream& operator<< (std::ostream& out, const Person& person);
    bool operator< (const Person& personOne, const Person& personTwo);
    bool operator== (const Person& personOne, const Person& personTwo);
}

#endif //_PERSON_H