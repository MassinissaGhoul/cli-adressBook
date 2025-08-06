

#include "include/adressBook.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

static void pause() {
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    AddressBook book;

    // 1) Load existing data
    constexpr char FILENAME[] = "addressbook.csv";
    if (book.loadFromCSV(FILENAME)) {
        std::cout << "Loaded existing address book from " << FILENAME << " ("
                  << book.size() << " entries).\n";
    } else {
        std::cout << "No existing address book found; starting fresh.\n";
    }

    // 2) Main loop
    while (true) {
        std::cout << "\n=== Address Book ===\n"
                  << "1) Add person\n"
                  << "2) Remove person by email\n"
                  << "3) Search\n"
                  << "4) Quit\n"
                  << "Select option (1-4): ";
        int choice;
        if (!(std::cin >> choice))
            break;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            // Add
            std::string fn, on, em, ph, st, tn, co;
            std::cout << "First name: ";
            std::getline(std::cin, fn);
            std::cout << "Other names: ";
            std::getline(std::cin, on);
            std::cout << "Email: ";
            std::getline(std::cin, em);
            std::cout << "Phone: ";
            std::getline(std::cin, ph);
            std::cout << "Street: ";
            std::getline(std::cin, st);
            std::cout << "Town: ";
            std::getline(std::cin, tn);
            std::cout << "Country: ";
            std::getline(std::cin, co);

            book.addPerson(Person(fn, on, em, ph, st, tn, co));
            std::cout << "Added: " << fn << " " << on << "\n";
            pause();

        } else if (choice == 2) {
            // Remove
            std::string email;
            std::cout << "Email to remove: ";
            std::getline(std::cin, email);
            bool ok = book.removePersonByEmail(email);
            std::cout << (ok ? "Removed.\n" : "Not found.\n");
            pause();

        } else if (choice == 3) {
            // Search
            std::cout << "\nSearch by:\n"
                      << "  1) First name\n"
                      << "  2) Other names\n"
                      << "  3) Email \n"
                      << "  4) Town\n"
                      << "  5) Country\n"
                      << "Select (1-5): ";
            int f;
            if (!(std::cin >> f))
                break;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::string query;
            std::vector<Person> results;
            switch (f) {
            case 1:
                std::cout << "First name: ";
                std::getline(std::cin, query);
                results = book.searchByFirstName(query);
                break;
            case 2:
                std::cout << "Other names: ";
                std::getline(std::cin, query);
                results = book.searchByOtherNames(query);
                break;
            case 3: {
                std::cout << "Email: ";
                std::getline(std::cin, query);
                if (auto opt = book.getPersonByEmail(query)) {
                    results.push_back(*opt);
                }
                break;
            }
            case 4:
                std::cout << "Town: ";
                std::getline(std::cin, query);
                results = book.searchByTown(query);
                break;
            case 5:
                std::cout << "Country: ";
                std::getline(std::cin, query);
                results = book.searchByCountry(query);
                break;
            default:
                std::cout << "Invalid choice.\n";
                pause();
                continue;
            }

            // Display results
            std::cout << "\nFound " << results.size() << " record(s):\n";
            for (auto &p : results) {
                std::cout << " - " << p.getFirstName() << " "
                          << p.getOtherNames() << " | " << p.getMail() << " | "
                          << p.getTelephoneNumber() << " | " << p.getStreet()
                          << ", " << p.getTown() << ", " << p.getCountry()
                          << "\n";
            }
            pause();

        } else if (choice == 4) {
            // Quit
            break;

        } else {
            std::cout << "Please enter a number from 1 to 4.\n";
            pause();
        }
    }

    // 3) Save on exit
    if (book.saveToCSV(FILENAME)) {
        std::cout << "Address book saved to " << FILENAME << ".\n";
    } else {
        std::cout << "Error: could not save to " << FILENAME << ".\n";
    }

    return 0;
}
