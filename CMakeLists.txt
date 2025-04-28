cmake_minimum_required(VERSION 3.0)
project(game)            # this sets the project name

###############################################################################
## file globbing ##############################################################
###############################################################################

# These instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variables 
# `sources` and `data`.
file(GLOB_RECURSE sources      src/*.cpp src/*.h)
file(GLOB_RECURSE sources_test tests/*.cpp)

###############################################################################
## target definitions #########################################################
###############################################################################

# The data is just added to the executable, because in some IDEs (QtCreator) 
# files are invisible when they are not explicitly part of the project.
add_executable(game ${sources} ${data})

# Just for example add some compiler flags.
target_compile_options(game PUBLIC -Wall)

# This allows to include files relative to the root of the src directory with a <> pair
target_include_directories(game PUBLIC src/)

###############################################################################
## testing ####################################################################
###############################################################################

# This is for our testing framework,
# we don't add REQUIRED because it's just for testing.
# People who might want to build the project to use it should not be required
# to install testing dependencies.
find_package(GTest)

if(GTEST_FOUND)
  add_executable(unit_tests ${sources_test} ${sources})

  # This define is added to prevent collision with the main.
  # It might be better solved by not adding the source with the main to the
  # testing target.
  target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

  # This allows us to use the executable as a link library, and inherit all 
  # linker options and library dependencies from it, by simply adding it as dependency.
  set_target_properties(game PROPERTIES ENABLE_EXPORTS on)

  target_link_libraries(unit_tests PUBLIC
    ${GTEST_BOTH_LIBRARIES}
    game
  )

  target_include_directories(unit_tests PUBLIC
    ${GTEST_INCLUDE_DIRS} # doesn't do anything on linux
  )
  
endif()