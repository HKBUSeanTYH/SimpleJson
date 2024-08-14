cmake_minimum_required(VERSION 3.5.0)
project(SimpleJson VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include(CTest)
# enable_testing()

# add_library(SimpleJson STATIC src/CipherMap.cpp src/Enigma.cpp src/Plugboard.cpp src/Reflector.cpp src/Rotor.cpp src/StringUtil.cpp)
# target_include_directories(SimpleJson PUBLIC include)
# target_compile_features(SimpleJson PUBLIC cxx_std_20)

# file(COPY resources DESTINATION .)

add_executable(main src/Main.cpp)
# target_link_libraries(main PUBLIC SimpleJson)