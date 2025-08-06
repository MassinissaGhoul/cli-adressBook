
#include "include/Person.hpp"
Person::Person(std::string firstName, std::string otherNames, std::string mail,
               std::string telephoneNumber, std::string street,
               std::string town, std::string country)
    : firstName(std::move(firstName)),
      otherNames(std::move(otherNames)),
      mail(std::move(mail)),
      telephoneNumber(std::move(telephoneNumber)),
      street(std::move(street)),
      town(std::move(town)),
      country(std::move(country)) {}

const std::string &Person::getFirstName() { return firstName; }

const std::string &Person::getOtherNames() { return otherNames; }

const std::string &Person::getMail() { return mail; }

const std::string &Person::getTelephoneNumber() { return telephoneNumber; }

const std::string &Person::getStreet() { return street; }

const std::string &Person::getTown() { return town; }

const std::string &Person::getCountry() { return country; }

void Person::setFirstName(const std::string &firstName) {
    this->firstName = firstName;
}

void Person::setOtherNames(const std::string &otherNames) {
    this->otherNames = otherNames;
}

void Person::setMail(const std::string &mail) { this->mail = mail; }

void Person::setTelephoneNumber(const std::string &telephoneNumber) {
    this->telephoneNumber = telephoneNumber;
}

void Person::setStreet(const std::string &street) { this->street = street; }

void Person::setTown(const std::string &town) { this->town = town; }

void Person::setCountry(const std::string &country) { this->country = country; }
