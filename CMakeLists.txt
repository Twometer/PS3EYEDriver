cmake_minimum_required(VERSION 3.1)

project(PS3EYEDriver)

set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
set(CMAKE_CXX_STANDARD 17)
set(SDK_LIBUSB ${CMAKE_SOURCE_DIR}\\lib)

add_definitions(-DNOMINMAX)
add_definitions(-DWIN32_LEAN_AND_MEAN)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_definitions(-DPS3EYE_DEBUG)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

if(NOT WIN32)
    add_definitions(-pthread)
    link_libraries(-pthread)
endif()

if(NOT MSVC)
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(libusb "libusb-1.0" QUIET)
    endif()
    if(libusb_FOUND)
        include_directories(SYSTEM ${libusb_INCLUDE_DIRS})
        link_libraries(${libusb_LIBRARIES})
    endif()
else()
    set(SDK_LIBUSB CACHE PATH "")
    if(SDK_LIBUSB)
        set(libusb_FOUND TRUE)
        link_directories("${SDK_LIBUSB}")
        include_directories(SYSTEM "${SDK_LIBUSB}")
        link_libraries(libusb-1.0)
    endif()
endif()

if(libusb_FOUND)
    add_library(ps3eye-driver STATIC
        "ps3eye.cpp"
        "urb.cpp"
        "queue.cpp"
        "mgr.cpp"
        "accessors.cpp")
endif()

add_library(libps3eye SHARED driverlib.cpp)
target_link_libraries(libps3eye ps3eye-driver)

add_executable(libps3eye-test driverlib_test.cpp)
target_link_libraries(libps3eye-test ps3eye-driver)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(SDL2 QUIET)

if(SDL2_FOUND)
    include_directories(SYSTEM ${SDL2_INCLUDE_DIRS})
    link_libraries(${SDL2_LIBRARIES})
    link_libraries(ps3eye-driver)
    add_executable(ps3eye-sdl "sdl.cxx")
endif()

add_executable(ps3eye-mode-test "mode-test.cxx")
target_link_libraries(ps3eye-mode-test ps3eye-driver)

add_executable(ps3eye-frame-test "frame-test.cxx")
target_link_libraries(ps3eye-frame-test ps3eye-driver)