#include "PhoneNumber.h"

namespace PhoneBook{
    PhoneNumber::PhoneNumber()
            : m_codeCountry(0), m_codeCity(0), m_number("0000000"), m_additionalNumber(std::nullopt){};
    PhoneNumber::PhoneNumber(int codeCountry, int codeCity, std::string number)
            : m_codeCountry(codeCountry), m_codeCity(codeCity), m_number(std::move(number)), m_additionalNumber(std::nullopt){};
    PhoneNumber::PhoneNumber(int codeCountry, int codeCity, std::string number, std::optional<int> additionalNumber)
            : m_codeCountry(codeCountry), m_codeCity(codeCity), m_number(std::move(number)), m_additionalNumber(additionalNumber){};

    void PhoneNumber::SetPhoneNumber(std::istringstream& line){
        std::string temp;
        line >> m_codeCountry >> m_codeCity >> m_number >> temp;
        if(temp == "-"){
            return;
        }
        else{
            m_additionalNumber.emplace(std::stoi(temp));
        }
    }


    std::string PhoneNumber::GetPhoneNumber(){
        std::string temp;
        temp.append(std::to_string(m_codeCountry));
        temp.append(" ");
        temp.append(std::to_string(m_codeCity));
        temp.append(" ");
        temp.append(m_number);
        temp.append(" ");
        if(m_additionalNumber.has_value()){
            temp.append(std::to_string(m_additionalNumber.value()));
            return temp;
        }
        else{
            return temp;
        }
    }
    std::optional<int> PhoneNumber::GetPhoneNumberAdditional(){
        return m_additionalNumber;
    }

    std::ostream& operator<< (std::ostream& out, const PhoneNumber& phoneNumber){
        out << "+" << phoneNumber.m_codeCountry << " (" << phoneNumber.m_codeCity << ") " << phoneNumber.m_number;
        if(phoneNumber.m_additionalNumber.has_value()){
            out << " " << phoneNumber.m_additionalNumber.value();
        }

        return out;
    }


    bool operator< (const PhoneNumber& phoneNumberOne, const PhoneNumber& phoneNumberTwo){
        return tie(phoneNumberOne.m_codeCountry, phoneNumberOne.m_codeCity, phoneNumberOne.m_number, phoneNumberOne.m_additionalNumber)
               < tie(phoneNumberTwo.m_codeCountry, phoneNumberOne.m_codeCity, phoneNumberOne.m_number, phoneNumberOne.m_additionalNumber);
    }
}