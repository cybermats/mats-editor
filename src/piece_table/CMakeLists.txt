project(piece_table_lib VERSION 0.1 LANGUAGES CXX)

find_package(Boost 1.66 REQUIRED COMPONENTS
        filesystem)


add_library("${PROJECT_NAME}"
        src/piece_table.cpp
        src/piece_table_impl.cpp
        src/file_piece_table.cpp
        src/large_file_piece_table.cpp)

target_include_directories("${PROJECT_NAME}" PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE src)

export(TARGETS "${PROJECT_NAME}" FILE piece_table.cmake)

add_executable("test_${PROJECT_NAME}"
  test/testmain.cpp)

target_link_libraries("test_${PROJECT_NAME}"
"${PROJECT_NAME}" ${Boost_LIBRARIES} gtest_main)

add_test("test_${PROJECT_NAME}" "test_${PROJECT_NAME}")