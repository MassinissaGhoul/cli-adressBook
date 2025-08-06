
````markdown
# AddressBook

## Prerequisites

- A C++17-compatible compiler (GCC 7+, Clang 5+)
- CMake 3.15 or newer

## Installation

```bash
# Clone the repository
git clone https://github.com/MassinissaGhoul/cli-adressBook.git
cd cle-adressBook

# Create and enter a build directory
mkdir build && cd build

# Configure the project
cmake ..

# Build the library and executable
cmake --build . or make
````

## Running

From the build folder:

```bash
./src/addressbook


```

The program will:

1. Load `addressbook.csv` if it exists.
2. Present an interactive menu (Add, Remove, Search, Quit).
3. Save all entries back to `addressbook.csv` on exit.

```
```

