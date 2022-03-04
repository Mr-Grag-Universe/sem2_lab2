cmake_minimum_required(VERSION 3.16)
project(universal_stack  C)

include_directories("template files")

set(CMAKE_C_STANDARD 99)

add_executable(universal_stack main.c KGetLine.c MyString.c "template files/func_template.c" "template files/func.c")
