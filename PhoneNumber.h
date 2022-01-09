#pragma once

#ifndef _PHONENUMBER_H
#define _PHONENUMBER_H

#include <sstream>
#include <iostream>
#include <optional>
#include <tuple>

namespace PhoneBook{
    class PhoneNumber {
    public:
        PhoneNumber();
        PhoneNumber(int codeCountry, int codeCity, std::string number);
        PhoneNumber(int codeCountry, int codeCity, std::string number, std::optional<int> additionalNumber);

        std::string GetPhoneNumber();
        std::optional<int> GetPhoneNumberAdditional();
        void SetPhoneNumber(std::istringstream& line);

        friend std::ostream& operator<< (std::ostream& out, const PhoneNumber& phoneNumber);
        friend bool operator< (const PhoneNumber& phoneNumberOne, const PhoneNumber& phoneNumberTwo);

    private:
        int m_codeCountry;
        int m_codeCity;
        std::string m_number;
        std::optional<int> m_additionalNumber;
    };

    std::ostream& operator<< (std::ostream& out, const PhoneNumber& phoneNumber);
    bool operator< (const PhoneNumber& phoneNumberOne, const PhoneNumber& phoneNumberTwo);
}

#endif //_PHONENUMBER_H