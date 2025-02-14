set(app_name1 prog1)
set(app_name2 prog2)
set(lib_name lib)

add_library(${lib_name} STATIC SHARED
  lib/testLib.cpp
)

target_include_directories(${lib_name}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}  
)

set_target_properties(${lib_name} PROPERTIES PUBLIC_HEADER lib/testLib.hpp)

#####################################

add_executable(${app_name1})

target_include_directories(${app_name1} PRIVATE .)

target_sources(
  ${app_name1}
  PRIVATE
    ${app_name1}/prog1.cpp
)

target_link_libraries(${app_name1}
  PRIVATE
    ${lib_name}
)

set_target_properties(
  ${app_name1}
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/prog1
)

############################

add_executable(${app_name2})

target_include_directories(${app_name2} PRIVATE .)

target_sources(
  ${app_name2}
  PRIVATE
    ${app_name2}/prog2.cpp
)

target_link_libraries(${app_name2}
  PRIVATE
    ${lib_name}
)

set_target_properties(
  ${app_name2}
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/prog2
)