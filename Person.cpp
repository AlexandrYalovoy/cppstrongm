#include "Person.h"
#include <utility>

namespace PhoneBook{
    Person::Person() : m_surname("NONE"), m_name("NONE"), m_patronymic(std::nullopt){};
    Person::Person(std::string surname, std::string name) : m_surname(std::move(surname)), m_name(std::move(name)), m_patronymic(std::nullopt){};
    Person::Person(std::string surname, std::string name, std::string patronymic) : m_surname(std::move(surname)), m_name(std::move(name)), m_patronymic(std::move(patronymic)){};

    void Person::SetPerson(std::istringstream& line){
        std::string temp;

        line >> m_surname >> m_name >> temp;
        if(temp == "-"){
            return;
        }
        else{
            m_patronymic.emplace(temp);
        }
    }

    std::string Person::GetFullName(){
        std::ostringstream out;
        std::string temp;

        out << m_surname << m_name;
        if(m_patronymic.has_value()){
            out << m_patronymic.value();
        }

        out.str(temp);
        return temp;
    }
    std::string& Person::GetSurname(){
        return m_surname;
    }
    std::string& Person::GetName(){
        return m_name;
    }
    std::string& Person::GetPatronymic(){
        return m_patronymic.value();
    }

    std::ostream& operator<< (std::ostream& out, const Person& person){
        out << person.m_surname << " " << person.m_name;

        if(person.m_patronymic.has_value()){
            out << " " << person.m_patronymic.value();
        }

        return out;
    }
    bool operator< (const Person& personOne, const Person& personTwo){
        return tie(personOne.m_surname, personOne.m_name, personOne.m_patronymic) < tie(personTwo.m_surname, personTwo.m_name, personTwo.m_patronymic);
    }
    bool operator== (const Person& personOne, const Person& personTwo){
        return tie(personOne.m_surname, personOne.m_name, personOne.m_patronymic) == tie(personTwo.m_surname, personTwo.m_name, personTwo.m_patronymic);
    }
}