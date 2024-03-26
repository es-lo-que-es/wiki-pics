cmake_minimum_required(VERSION 3.10)

project(wiki-pics)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)


SET(
   SOURCE_FILES 

   main_window.cpp
   picture_list_view.cpp
   picture_delegate.cpp
   picture_list_model.cpp
   picture_loader.cpp
   search_bar.cpp
   main.cpp   
)

add_executable(wiki-pics ${SOURCE_FILES})
target_link_libraries(wiki-pics Qt5::Widgets Qt5::Network)
