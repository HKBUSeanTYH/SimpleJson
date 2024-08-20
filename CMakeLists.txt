cmake_minimum_required(VERSION 3.5.0)
project(SimpleJson VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include(CTest)
# enable_testing()

# find_package(Boost REQUIRED)
add_library(SimpleJson STATIC src/JsonValue.cpp)
target_include_directories(SimpleJson PUBLIC include)
target_compile_features(SimpleJson PUBLIC cxx_std_20)

add_executable(main src/Main.cpp)
target_link_libraries(main PUBLIC SimpleJson)
# target_link_libraries(MyProject Boost::headers)