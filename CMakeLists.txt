cmake_minimum_required(VERSION 3.18)
project(MFRCScan)

set(CMAKE_CXX_STANDARD 17)

add_executable(MFRCScan main.cpp RPi-RFID/MFRC522.cpp hash-library/sha1.cpp)

include(FetchContent)
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba
) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
set(CPR_ENABLE_SSL OFF)

FetchContent_MakeAvailable(cpr)

target_link_libraries(MFRCScan PRIVATE cpr::cpr bcm2835)