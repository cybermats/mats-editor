project(piece_table_gtk_app VERSION 0.1 LANGUAGES CXX)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})


add_executable("winapp"
        src/main.cpp)

target_link_libraries("winapp"
        ${Boost_LIBRARIES} ${GTK3_LIBRARIES})
