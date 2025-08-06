
add_library(PersonDir
    Person.cpp
    hashMap.cpp
    adressBook.cpp
)
target_include_directories(PersonDir PUBLIC ${CMAKE_SOURCE_DIR}/src/include)
add_executable(addressBook main.cpp)
target_link_libraries(addressBook PersonDir)

