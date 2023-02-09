
cmake_minimum_required(VERSION 3.9) # 3.9: OpenMP improved support
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(EZ_ROOT $ENV{EZ_PATH})

project(findfunc)
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release")
endif()

file(GLOB findfunc_src ${CMAKE_SOURCE_DIR}/*.cpp ${CMAKE_SOURCE_DIR}/*.c)
add_executable(findfunc ${findfunc_src})

target_compile_features(findfunc PUBLIC cxx_std_14)
target_compile_options(findfunc PUBLIC
	$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2 /W3>
	$<$<AND:$<NOT:$<CXX_COMPILER_ID:MSVC>>,$<CONFIG:Release>>:-O3 -march=native -mtune=native -Wall -Wextra -pedantic>
	$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/W4 /DEBUG:FULL>
	$<$<AND:$<NOT:$<CXX_COMPILER_ID:MSVC>>,$<CONFIG:Debug>>:-O2 -g -Wall -Wextra -pedantic>
	)

find_library(libeasea_LIB
	NAMES libeasea easea
	HINTS ${EZ_ROOT} ${CMAKE_INSTALL_PREFIX}/easena ${CMAKE_INSTALL_PREFIX}/EASENA
	PATH_SUFFIXES lib libeasea easea easena)
find_path(libeasea_INCLUDE
	NAMES CLogger.h
	HINTS ${EZ_ROOT}/libeasea ${CMAKE_INSTALL_PREFIX}/*/libeasea
	PATH_SUFFIXES include easena libeasea)
find_package(Boost)
find_package(OpenMP)

target_include_directories(findfunc PUBLIC ${Boost_INCLUDE_DIRS} ${libeasea_INCLUDE})
target_link_libraries(findfunc PUBLIC ${libeasea_LIB} OpenMP::OpenMP_CXX $<$<CXX_COMPILER_ID:MSVC>:winmm>)

