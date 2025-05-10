cmake_minimum_required(VERSION 3.25)
project(game)            # this sets the project name

option(BUILD_GUI "Builds the user interface (needs extra dependencies)" ON)

###############################################################################
## file globbing ##############################################################
###############################################################################

# These instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variables 
# `sources` and `data`.
file(GLOB_RECURSE sources      src/*.cpp src/*.h)
file(GLOB_RECURSE sources_test tests/*.cpp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
## target definitions #########################################################
###############################################################################

# The data is just added to the executable, because in some IDEs (QtCreator) 
# files are invisible when they are not explicitly part of the project.
add_library(game ${sources} ${data})

# Just for example add some compiler flags.
target_compile_options(game PUBLIC -Wall)

# This allows to include files relative to the root of the src directory with a <> pair
target_include_directories(game PUBLIC src/)

###############################################################################
## testing ####################################################################
###############################################################################

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(unit_tests ${sources_test})

target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

target_link_libraries(unit_tests PUBLIC
  GTest::gtest_main
  game
)

include(GoogleTest)
gtest_discover_tests(unit_tests)


if(BUILD_GUI)
    # Adding Raylib
    include(FetchContent)
    set(FETCHCONTENT_QUIET FALSE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

    FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
    )

    set_target_properties(game PROPERTIES ENABLE_EXPORTS on)

    FetchContent_MakeAvailable(raylib)

    file(GLOB_RECURSE ui_sources   ui/src/*.cpp ui/src/*.h)

    project(gui)

    file(COPY ui/res
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

    add_executable(gui ${ui_sources})
    target_link_libraries(gui PRIVATE raylib  game)
endif(BUILD_GUI)