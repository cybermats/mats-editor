cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 14)
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result) 
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)


project(piece_table VERSION 0.0.0)

include(CTest)
enable_testing()

SET(SOURCE source/piece_table.cpp)



add_executable("${PROJECT_NAME}" main.cpp ${SOURCE})
add_executable("unittest_${PROJECT_NAME}" testmain.cpp ${SOURCE})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
target_link_libraries("unittest_${PROJECT_NAME}" gtest_main)
add_test(NAME "unittest_${PROJECT_NAME}" COMMAND "unittest_${PROJECT_NAME}")