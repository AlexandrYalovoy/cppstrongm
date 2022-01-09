#include <fstream>
#include "PhoneBook_Test.h"

TEST_F(PhoneBook_Test, FullNameSTR){
char const *surname = "Kozlovskii";
char const *name = "Artem";
char const *patronymic = "Daniilovich";
ASSERT_STREQ(personTest->GetSurname().c_str(), surname);
ASSERT_STRNE(personTest->GetSurname().c_str(), name);
ASSERT_STREQ(personTest->GetName().c_str(), name);
ASSERT_STRNE(personTest->GetName().c_str(), surname);
ASSERT_STREQ(personTest->GetPatronymic().c_str(), patronymic);
ASSERT_STRNE(personTest->GetPatronymic().c_str(), surname);
}

TEST_F(PhoneBook_Test, FullNameEQ){
char const *surname = "Kozlovskii";
char const *name = "Artem";
char const *patronymic = "Daniilovich";
ASSERT_EQ(personTest->GetSurname(), surname);
ASSERT_EQ(personTest->GetName(), name);
ASSERT_EQ(personTest->GetPatronymic(), patronymic);
ASSERT_NE(personTest->GetSurname(), name);
ASSERT_NE(personTest->GetName(), surname);
ASSERT_NE(personTest->GetPatronymic(), name);
}

TEST_F(PhoneBook_Test, PhoneNumber){
char const *number = "81 8281 7420182 1";
ASSERT_TRUE(phoneNumberTest->GetPhoneNumberAdditional() != std::nullopt);
ASSERT_EQ(phoneNumberTest->GetPhoneNumber(), number);
ASSERT_LT(phoneNumberTest->GetPhoneNumber(), "81 8281 7420182 2");
ASSERT_STRNE(phoneNumberTest->GetPhoneNumber().c_str(), "81 8281 7420182 -");
}

int main() {
    /*std::ifstream in("PhoneBook.txt");
    PhoneBook::PhoneBook phoneBook(in);
    std::cout << phoneBook;
    std::cout << "------SortByPhone-------" << std::endl;
    phoneBook.SortByName();
    std::cout << phoneBook;
    std::cout << "------SortByName--------" << std::endl;
    phoneBook.SortByPhone();
    std::cout << phoneBook;
    auto print_phone_number = [&phoneBook](const std::string& surname) {
        std::cout << surname << "\t";
        auto answer = phoneBook.GetPhoneNumber(surname);
        if (std::get<0>(answer).empty())
            std::cout << std::get<1>(answer);
        else
            std::cout << std::get<0>(answer);
        std::cout << std::endl;
    };
    print_phone_number("Ivanov");
    print_phone_number("Petrov");
    print_phone_number("Solovev");
    std::cout << "----ChangePhoneNumber----" << std::endl;
    phoneBook.ChangePhoneNumber(PhoneBook::Person{ "Kotov", "Vasilii", "Eliseevich" },PhoneBook::PhoneNumber{7, 123, "15344458", std::nullopt});
    phoneBook.ChangePhoneNumber(PhoneBook::Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneBook::PhoneNumber{ 16, 465, "9155448", 13 });
    std::cout << phoneBook;*/

    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}