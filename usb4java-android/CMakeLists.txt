# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/.cmake/Modules/")

set(LibUsb_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/../../libusb-1.0.21/libusb")
set(LibUsb_LIBRARIES "${CMAKE_SOURCE_DIR}/../../libusb-1.0.21/android/obj/local")

find_package(LibUsb REQUIRED)


include_directories(${LibUsb_INCLUDE_DIRS})

set(distribution_DIR ${CMAKE_SOURCE_DIR}/libs)


add_library(libusb-1.0 SHARED IMPORTED)
set_target_properties(
    libusb-1.0 PROPERTIES IMPORTED_LOCATION
    ${distribution_DIR}/libusb-1.0/${ANDROID_ABI}/libusb1.0.so)

# add_subdirectory(src/main/cpp)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

file(GLOB SOURCES
    src/main/cpp/*.h
    src/main/cpp/*.cpp
    src/main/cpp/*.c
)

add_library( # Sets the name of the library.
             LibUsb

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${SOURCES} )


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

# find_library( # Sets the name of the path variable.
#              log-lib
#
#              # Specifies the name of the NDK library that
#              # you want CMake to locate.
#              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       LibUsb

                       # Links the target library to the log library
                       # included in the NDK.
                       libusb-1.0 )
