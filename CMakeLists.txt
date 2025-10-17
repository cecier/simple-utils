cmake_minimum_required(VERSION 3.24)
project(EUL VERSION 1.0)

# Добавляем конфигурации сборки
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add your executable. This command CREATES the MARIOEUL target.
add_executable(EUL simple_counter/source.cc)

# Now you can set properties on the MARIOEUL target.
set_property(TARGET EUL PROPERTY CXX_STANDARD 17)
set_property(TARGET EUL PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET EUL PROPERTY CXX_EXTENSIONS OFF)
