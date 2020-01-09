cmake_minimum_requirement(3.13)

# set project name
project(cnn)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# add boost for numeric ublas tensor
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS ublas filesystem regex)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(cnn file1.cxx file2.cxx)
    target_link_libraries(cnn $(Boost_LIBRARIES))
endif()




# configure header files
configure_file(tutorial.h)


# add executables
add_executable(cnn cnn.cxx)


# include directories
target_include_directories(cnn "$(PROJECT_BINARY_DIR)")

