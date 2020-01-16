# CMakeLists.txt

cmake_minimum_required(VERSION 3.13)

# set project name
project(cnn)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# recursively get all source and header files
file(GLOB_RECURSE SOURCE
    # "lib/*.{cpp,h}"
    "src/*.cpp"
    "include/*.hpp"
)

list(REMOVE_ITEM SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/controller.cpp")
list(REMOVE_ITEM SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/include/controller.h")

# add boost for numeric ublas tensor
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# add_executable(cnn ${SOURCE})

find_package(Boost REQUIRED COMPONENTS system filesystem regex )

if(Boost_FOUND)
    include_directories(
        ${BOOST_INCLUDE_DIRS}
    )
    # create executable cnn
    add_executable(cnn ${SOURCE})
    target_link_libraries(cnn
        ${Boost_LIBRARIES}
    )
endif()

