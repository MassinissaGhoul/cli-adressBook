

#include "include/adressBook.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>

// Add all index entries for person at position idx
// We const_cast away const so we can call the non-const getters
void AddressBook::indexEntry(const Person &person, std::size_t idx) {
    Person &p = const_cast<Person &>(person);

    const std::string &fn = p.getFirstName();
    if (auto *vec = indexFirstName_.find(fn)) {
        vec->push_back(idx);
    } else {
        indexFirstName_.insert(fn, {idx});
    }

    const std::string &on = p.getOtherNames();
    if (auto *vec = indexOtherNames_.find(on)) {
        vec->push_back(idx);
    } else {
        indexOtherNames_.insert(on, {idx});
    }

    const std::string &em = p.getMail();
    indexEmail_.insert(em, idx);

    const std::string &tn = p.getTown();
    if (auto *vec = indexTown_.find(tn)) {
        vec->push_back(idx);
    } else {
        indexTown_.insert(tn, {idx});
    }

    const std::string &cn = p.getCountry();
    if (auto *vec = indexCountry_.find(cn)) {
        vec->push_back(idx);
    } else {
        indexCountry_.insert(cn, {idx});
    }
}

// Remove all index entries for person at position idx
void AddressBook::removeIndex(const Person &person, std::size_t idx) {
    Person &p = const_cast<Person &>(person);

    auto eraseFrom = [&](auto &map, const std::string &key) {
        if (auto *vec = map.find(key)) {
            auto &v = *vec;
            v.erase(std::remove(v.begin(), v.end(), idx), v.end());
            if (v.empty()) {
                map.erase(key);
            }
        }
    };

    eraseFrom(indexFirstName_, p.getFirstName());
    eraseFrom(indexOtherNames_, p.getOtherNames());
    indexEmail_.erase(p.getMail());
    eraseFrom(indexTown_, p.getTown());
    eraseFrom(indexCountry_, p.getCountry());
}

void AddressBook::addPerson(const Person &person) {
    std::size_t idx = persons_.size();
    persons_.push_back(person);
    indexEntry(persons_.back(), idx);
}

bool AddressBook::removePersonByEmail(const std::string &email) {
    if (auto *ptr = indexEmail_.find(email)) {
        std::size_t idx = *ptr;
        // Make a local copy to pass into removeIndex
        Person backup = persons_[idx];
        removeIndex(backup, idx);

        // Swap-erase to keep vector compact
        std::size_t last = persons_.size() - 1;
        if (idx != last) {
            std::swap(persons_[idx], persons_[last]);
            // Update indexes for moved entry
            removeIndex(persons_[idx], last);
            indexEntry(persons_[idx], idx);
        }
        persons_.pop_back();
        return true;
    }
    return false;
}

std::optional<Person> AddressBook::getPersonByEmail(const std::string &email) {
    if (auto *ptr = indexEmail_.find(email)) {
        return persons_[*ptr];
    }
    return std::nullopt;
}

std::vector<Person>
AddressBook::searchByFirstName(const std::string &firstName) {
    std::vector<Person> results;
    if (auto *ptr = indexFirstName_.find(firstName)) {
        for (auto idx : *ptr) {
            results.push_back(persons_[idx]);
        }
    }
    return results;
}

std::vector<Person>
AddressBook::searchByOtherNames(const std::string &otherNames) {
    std::vector<Person> results;
    if (auto *ptr = indexOtherNames_.find(otherNames)) {
        for (auto idx : *ptr) {
            results.push_back(persons_[idx]);
        }
    }
    return results;
}

std::vector<Person> AddressBook::searchByTown(const std::string &town) {
    std::vector<Person> results;
    if (auto *ptr = indexTown_.find(town)) {
        for (auto idx : *ptr) {
            results.push_back(persons_[idx]);
        }
    }
    return results;
}

std::vector<Person> AddressBook::searchByCountry(const std::string &country) {
    std::vector<Person> results;
    if (auto *ptr = indexCountry_.find(country)) {
        for (auto idx : *ptr) {
            results.push_back(persons_[idx]);
        }
    }
    return results;
}

bool AddressBook::loadFromCSV(const std::string &filename) {
    std::ifstream in(filename);
    if (!in.is_open())
        return false;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty())
            continue;
        std::istringstream ss(line);
        std::vector<std::string> cols;
        std::string token;
        while (std::getline(ss, token, ',')) {
            cols.push_back(token);
        }
        if (cols.size() != 7)
            continue;
        Person p(cols[0], cols[1], cols[2], cols[3], cols[4], cols[5], cols[6]);
        addPerson(p);
    }
    return true;
}

bool AddressBook::saveToCSV(const std::string &filename) {
    std::ofstream out(filename);
    if (!out.is_open())
        return false;
    for (const auto &entry : persons_) {
        Person &p = const_cast<Person &>(entry);
        out << p.getFirstName() << ',' << p.getOtherNames() << ','
            << p.getMail() << ',' << p.getTelephoneNumber() << ','
            << p.getStreet() << ',' << p.getTown() << ',' << p.getCountry()
            << '\n';
    }
    return true;
}
