cmake_minimum_required(VERSION 3.10)
project(EUL)

set(CMAKE_CXX_STANDARD 17)

# Добавляем конфигурации сборки
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_executable  (EUL 
                    simple_vector/source.cpp
                )

