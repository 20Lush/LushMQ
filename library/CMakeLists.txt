cmake_minimum_required(VERSION 3.22)

# Lets initialize the project for our actual library
project(LushMQ
    VERSION ${PROJECT_VERSION}
    DESCRIPTION "LushMQ Project"
)
message(STATUS "Project name: " ${PROJECT_NAME})

# Define what source files we actually are going to compile
set(SOURCE_FILES
    src/LushMQ.cpp
    src/Subscriber.cpp
)

# Define what header files are going to be exposed(only put interfaces!)
set(PUBLIC_INCLUDE_FILES
    include/LushMQ.hpp
    include/Subscriber.hpp
)

# Do a CMake add_library to mark it for build. change STATIC to SHARED or whatever when needed.
add_library( ${PROJECT_NAME}
    STATIC
        ${SOURCE_FILES}
)

# There might be some includes we want at build-time here
include_directories("${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
include_directories(${DEPENDENCY_PATH})

# Put some versioning info into our 
configure_file(
    "${PROJECT_SOURCE_DIR}/include/version.hpp.in"
    "${PROJECT_SOURCE_DIR}/include/version.hpp"
)

# The installed directory is going to have its own include directory.
# In the unlikely scenario this library is used in another project,
# they'll need the public headers.
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Put any compile features we'd want in here, like language standards
target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_std_20
)

# We are going to be statically linking my packaged up ZeroMQ artifact. There are some LGPL concerns regarding if thats even
# ok, however considering LushMQ is opensource itself, it shouldn't be a problem. One should be totally able to run an edited
# version of LMQ with my distribution of ZMQ, or an edited version of ZMQ with my version of LMQ (provided they build from source)
set(ZeroMQ_DIR ${DEPS_PATH}/zmq/lib/cmake/ZeroMQ)
find_package(ZeroMQ HINTS ${DEPS_PATH} REQUIRED)

# Set some target properties of the installed binaries, liked if they have position independent code
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        LINKER_LANGUAGE CXX
        POSITION_INDEPENDENT_CODE TRUE
)

# Link the libraries we want, like OpenCV or the cuda toolkit
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        stdfc++
        libzmq
        cppzmq
)

# Send to boilerplate!
message(STATUS "Installing library to " ${CMAKE_INSTALL_PREFIX} "/...")
# Found in INSTALLER.cmake
DefaultInstall(${PROJECT_NAME})