#pragma once
#include <string>

class Person {
    private:
        std::string firstName;
        std::string otherNames;
        std::string mail;
        std::string telephoneNumber;
        std::string street;
        std::string town;
        std::string country;

    public:
        Person() = default;
        Person(std::string firstName, std::string otherNames, std::string mail,
               std::string telephoneNumber, std::string street,
               std::string town, std::string country);

        const std::string &getFirstName();
        const std::string &getOtherNames();
        const std::string &getMail();
        const std::string &getTelephoneNumber();
        const std::string &getStreet();
        const std::string &getTown();
        const std::string &getCountry();

        void setFirstName(const std::string &firstName);
        void setOtherNames(const std::string &otherNames);
        void setMail(const std::string &mail);
        void setTelephoneNumber(const std::string &telephoneNumber);
        void setStreet(const std::string &street);
        void setTown(const std::string &town);
        void setCountry(const std::string &country);
};
