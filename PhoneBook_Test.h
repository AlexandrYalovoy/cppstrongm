#pragma once

#ifndef _PHONEBOOK_TEST_H
#define _PHONEBOOK_TEST_H

#include "PhoneBook.h"
#include "gtest/gtest.h"

class PhoneBook_Test : public testing::Test{
protected:
    void SetUp() override{
        personTest = new PhoneBook::Person("Kozlovskii", "Artem", "Daniilovich");
        phoneNumberTest = new PhoneBook::PhoneNumber(81, 8281, "7420182", 1);
        phoneBookTest = new PhoneBook::PhoneBook("Kozlovskii Artem Daniilovich", "81 8281 7420182 1");
    }

    void TearDown() override{
        delete phoneBookTest;
        delete personTest;
        delete phoneNumberTest;
    }

    PhoneBook::PhoneNumber *phoneNumberTest;
    PhoneBook::Person *personTest;
    PhoneBook::PhoneBook *phoneBookTest;
};



#endif //_PHONEBOOK_TEST_H