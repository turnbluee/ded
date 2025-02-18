cmake_minimum_required(VERSION 3.10)

project(EvgSort)  # Название проекта (замените при необходимости)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -funsigned-char")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -funsigned-char")
# Автоматический поиск всех .c и .h файлов
file(GLOB SOURCES "*.c" "*.h" "*.txt")

# Создание исполняемого файла
add_executable(my_program ${SOURCES})
