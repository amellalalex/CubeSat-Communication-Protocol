cmake_minimum_required(VERSION 2.6)

project("LibserialCXX")

set ( src-files
  "main.cpp"
)

add_library ( "serial_ext"
  "libserial_ext.hpp"
  "libserial_ext.cpp"
)

add_executable(${PROJECT_NAME} ${src-files})

target_link_libraries(${PROJECT_NAME} "serial")

target_link_libraries(${PROJECT_NAME} "serial_ext")
