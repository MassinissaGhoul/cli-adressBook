#pragma once
#include "Person.hpp"
#include "hashMap.hpp"
#include <optional>

class AddressBook {
    public:
        AddressBook() = default;
        ~AddressBook() = default;

        void addPerson(const Person &person);

        bool removePersonByEmail(const std::string &email);

        std::optional<Person> getPersonByEmail(const std::string &email);

        std::vector<Person> searchByFirstName(const std::string &firstName);
        std::vector<Person> searchByOtherNames(const std::string &otherNames);
        std::vector<Person> searchByTown(const std::string &town);
        std::vector<Person> searchByCountry(const std::string &country);

        bool loadFromCSV(const std::string &filename);

        bool saveToCSV(const std::string &filename);

        std::size_t size() const noexcept { return persons_.size(); }
        bool empty() const noexcept { return persons_.empty(); }

    private:
        std::vector<Person> persons_;

        HashMap<std::string, std::vector<std::size_t>> indexFirstName_;
        HashMap<std::string, std::vector<std::size_t>> indexOtherNames_;
        HashMap<std::string, std::size_t> indexEmail_;
        HashMap<std::string, std::vector<std::size_t>> indexTown_;
        HashMap<std::string, std::vector<std::size_t>> indexCountry_;

        void indexEntry(const Person &person, std::size_t idx);
        void removeIndex(const Person &person, std::size_t idx);
};
