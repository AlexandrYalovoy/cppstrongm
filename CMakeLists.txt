cmake_minimum_required(VERSION 3.20)
project(cppstrongm)

set(CMAKE_CXX_STANDARD 17)

add_executable(cppstrongm
        main.cpp
        Person.cpp
        Person.h
        PhoneBook.cpp
        PhoneBook.h
        PhoneBook_Test.cpp
        PhoneBook_Test.h
        PhoneNumber.cpp
        PhoneNumber.h)
