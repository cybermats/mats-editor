project(piece_table_app VERSION 0.1 LANGUAGES CXX)

add_executable("app"
        src/main.cpp)

target_link_libraries("app"
        piece_table_lib ${Boost_LIBRARIES})
