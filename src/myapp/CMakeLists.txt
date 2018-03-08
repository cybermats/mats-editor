find_package(Boost 1.66 REQUIRED COMPONENTS
        filesystem)

add_executable("app"
  src/main.cpp)

target_link_libraries("app"
  piece_table_lib ${Boost_LIBRARIES})
