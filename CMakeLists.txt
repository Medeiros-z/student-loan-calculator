cmake_minimum_required(VERSION 4.2)
project(student_loan_calculator)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(json)

include_directories(.)

add_executable(student_loan_calculator
        Loan.cpp
        Loan.h
        Payment.cpp
        Payment.h
        main.cpp)

target_link_libraries(student_loan_calculator PRIVATE nlohmann_json::nlohmann_json)
