#include "PhoneBook.h"

namespace PhoneBook{
    PhoneBook::PhoneBook(std::ifstream& file){
        if(file.is_open()){
            InsertToPhoneBook(file);
        }
    }

    PhoneBook::PhoneBook(const std::string& person, const std::string& phoneNumber){
        InsertToPhoneBookManually(person, phoneNumber);
    }

    void PhoneBook::InsertToPhoneBook(std::ifstream& file){
        std::string line;
        while(std::getline(file, line)){
            std::istringstream issLine(line);
            Person person;
            person.SetPerson(issLine);
            PhoneNumber phoneNumber;
            phoneNumber.SetPhoneNumber(issLine);

            m_phoneBook.push_back(std::make_pair(person, phoneNumber));
        }
    }

    void PhoneBook::InsertToPhoneBookManually(const std::string& personText, const std::string& phoneNumberText){
        std::istringstream issLinePerson(personText);
        std::istringstream issLinePhoneNumber(phoneNumberText);
        Person person;
        person.SetPerson(issLinePerson);
        PhoneNumber phoneNumber;
        phoneNumber.SetPhoneNumber(issLinePhoneNumber);
        m_phoneBook.push_back(std::make_pair(person, phoneNumber));
    }

    void PhoneBook::SortByName(){
        std::sort(m_phoneBook.begin(), m_phoneBook.end(),
                  [](std::pair<Person, PhoneNumber>& current, std::pair<Person, PhoneNumber>& next){return current.first < next.first;});
    }


    void PhoneBook::SortByPhone(){
        std::sort(m_phoneBook.begin(), m_phoneBook.end(),
                  [](std::pair<Person, PhoneNumber>& current, std::pair<Person, PhoneNumber>& next){return current.second < next.second;});
    }

    std::tuple<std::string, PhoneNumber> PhoneBook::GetPhoneNumber(const std::string& surname) const{
        std::tuple<std::string, PhoneNumber> out;
        std::string text;
        int count = 0;

        std::for_each(std::begin(m_phoneBook), std::end(m_phoneBook), [&count, &out, &surname](std::pair<Person, PhoneNumber> pB){
            if(pB.first.GetSurname() == surname){
                count++;
                std::get<1>(out) = pB.second;
            }
        });

        if(count == 1){
            return out;
        }
        else if(count > 1){
            std::get<0>(out) = "found more than 1";
            return out;
        }
        else{
            std::get<0>(out) = "not found";
            return out;
        }
    }

    std::string PhoneBook::GetPhoneNumberTest(const std::string& surname) const{
        std::tuple<std::string, PhoneNumber> out;
        int count = 0;

        std::for_each(std::begin(m_phoneBook), std::end(m_phoneBook), [&count, &out, &surname](std::pair<Person, PhoneNumber> pB){
            if(pB.first.GetSurname() == surname){
                count++;
                std::get<1>(out) = pB.second;
            }
        });

        if(count == 1){
            return std::get<1>(out).GetPhoneNumber();
        }
        else if(count > 1){
            std::get<0>(out) = "found more than 1";
            return std::get<0>(out);
        }
        else{
            std::get<0>(out) = "not found";
            return std::get<0>(out);
        }
    }

    std::string PhoneBook::GetPersonTest(const std::string& number) const{
        std::tuple<std::string, Person> out;
        int count = 0;

        std::for_each(std::begin(m_phoneBook), std::end(m_phoneBook), [&count, &out, &number](std::pair<Person, PhoneNumber> pB){
            if(pB.second.GetPhoneNumber() == number){
                count++;
                std::get<1>(out) = pB.first;
            }
        });

        if(count == 1){
            return std::get<1>(out).GetFullName();
        }
        else if(count > 1){
            std::get<0>(out) = "found more than 1";
            return std::get<0>(out);
        }
        else{
            std::get<0>(out) = "not found";
            return std::get<0>(out);
        }
    }

    void PhoneBook::ChangePhoneNumber(const Person& person, const PhoneNumber& phoneNumber){
        auto result = std::find_if(m_phoneBook.begin(), m_phoneBook.end(), [&person](std::pair<Person, PhoneNumber>& found){
            return found.first == person;
        });

        if(!(result == m_phoneBook.end())){
            result->second = phoneNumber;
        }
    }

    std::ostream& operator<< (std::ostream& out, PhoneBook& phoneBook){
        for(auto& pB : phoneBook.m_phoneBook){
            out << pB.first << " " << pB.second << std::endl;
        }

        out << std::endl;

        return out;
    }
}