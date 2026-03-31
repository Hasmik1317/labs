cmake_minimum_required(VERSION 3.10)
project(USB_Dongle_Protection)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

file(GLOB SOURCES "src/*.cpp")

add_executable(Lab5 ${SOURCES})

# Linux-ի համար երբեմն պետք է լինում կապել filesystem գրադարանը
if(UNIX)
    target_link_libraries(Lab5 stdc++fs)
endif()
