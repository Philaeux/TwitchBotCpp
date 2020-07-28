# Basic Setup
cmake_minimum_required (VERSION 3.13)
project ("TwitchBotCpp")

# Conan setup
if (NOT EXISTS conanbuildinfo.cmake)
  message(FATAL_ERROR "Conan needs to be executed: conan install <path_to_your_conanfile.txt>")
endif ()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# Sources setup
add_executable (${CMAKE_PROJECT_NAME} "")
include(twitchbotcpp/CMakeLists.txt)

# Configurations copy
file (GLOB cfg_files "twitchbotcpp/cfg/*")
foreach(cfg_file ${cfg_files})
  get_filename_component(cfg_file_name ${cfg_file} NAME)
  configure_file(${cfg_file} "${CMAKE_BINARY_DIR}/bin/cfg/${cfg_file_name}" COPYONLY)
endforeach()

# Data copy
file (COPY "twitchbotcpp/data" DESTINATION "${CMAKE_BINARY_DIR}/bin")
 
#Linking
target_link_libraries(${CMAKE_PROJECT_NAME} CONAN_PKG::boost)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
 