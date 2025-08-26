cmake_minimum_required(VERSION 3.24)
project(Logging VERSION 1.0)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Папка для вывода DLL
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Создаём DLL с фиксированным именем Logging.dll
add_library(Logging SHARED
    source/core/logger.cpp
    source/core/logger.hpp
)

# Экспорт функций
target_compile_definitions(Logging PRIVATE LOGGING_EXPORTS)

# Переименовываем DLL
set_target_properties(Logging PROPERTIES
    OUTPUT_NAME "Logging"
)
