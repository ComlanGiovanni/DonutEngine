cmake_minimum_required(VERSION 3.10)
project(ft_donut CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ft_donut main.cpp donut.cpp)

if(MSVC)
  target_compile_options(ft_donut PRIVATE /W4)
else()
  target_compile_options(ft_donut PRIVATE -Wall -Wextra -Werror)
endif()
