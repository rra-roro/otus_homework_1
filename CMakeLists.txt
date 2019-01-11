cmake_minimum_required(VERSION 3.2)

project(helloworld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.12")
    message(STATUS "CMake version ${CMAKE_VERSION}")
    cmake_policy(SET CMP0074 NEW)
endif ()

if(STATIC_LINK_LIBS)
	set (Boost_USE_STATIC_LIBS ON)
endif ()

set (Boost_NO_BOOST_CMAKE ON)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

if (Boost_FOUND)
	message(STATUS "Setting up BOOST")
	message(STATUS " Includes - ${Boost_INCLUDE_DIRS}")
	message(STATUS " Library  - ${Boost_LIBRARY_DIRS}")
endif (Boost_FOUND)

configure_file("./include/version.h.in" version.h)

add_library(helloworld ./src_lib/lib.cpp)
add_executable(helloworld_cli ./src/main.cpp)
add_executable(test_version ./src_test/test_version.cpp)

target_include_directories(helloworld PUBLIC "include/" "${CMAKE_CURRENT_BINARY_DIR}" )
target_include_directories(helloworld_cli PUBLIC "include/" "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(test_version PUBLIC "include/" "${CMAKE_CURRENT_BINARY_DIR}" "${Boost_INCLUDE_DIR}")

if (MSVC)

    message(STATUS "MSVC")

	set_target_properties(helloworld_cli helloworld test_version PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
      COMPILE_OPTIONS "-Wall"
    )

else()

	set_target_properties(helloworld_cli helloworld test_version PROPERTIES
		  CXX_STANDARD 14
		  CXX_STANDARD_REQUIRED ON
		  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
	)

endif ()

if(NOT STATIC_LINK_LIBS)
	set_target_properties(test_version PROPERTIES
            COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    )
endif ()

   
target_link_libraries(helloworld_cli helloworld)
target_link_libraries(test_version ${Boost_LIBRARIES} helloworld)

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT shebdim@gmail.com)

include(CPack)

enable_testing()

add_test(test_version test_version)