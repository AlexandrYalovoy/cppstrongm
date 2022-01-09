#pragma once

#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include "Person.h"
#include "PhoneNumber.h"

namespace PhoneBook{

    class PhoneBook {
    public:
        PhoneBook() = default;
        PhoneBook(const std::string& person, const std::string& phoneNumber);
        PhoneBook(std::ifstream& file);

        void SortByName();
        void SortByPhone();

        std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string& surname) const;
        std::string GetPhoneNumberTest(const std::string& surname) const;
        std::string GetPersonTest(const std::string& surname) const;
        void ChangePhoneNumber(const Person& person, const PhoneNumber& phoneNumber);

        friend std::ostream& operator<< (std::ostream& out, PhoneBook& phoneBook);

    private:
        std::vector<std::pair<Person, PhoneNumber>> m_phoneBook;

        void InsertToPhoneBook(std::ifstream& file);
        void InsertToPhoneBookManually(const std::string& personText, const std::string& phoneNumberText);
    };
}


#endif //_PHONEBOOK_H