cmake_minimum_required(VERSION 3.10)

project(EvgSort)  # �������� ������� (�������� ��� �������������)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -funsigned-char")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -funsigned-char")
# �������������� ����� ���� .c � .h ������
file(GLOB SOURCES "*.c" "*.h" "*.txt")

# �������� ������������ �����
add_executable(my_program ${SOURCES})
