set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug) #Debug Release RelWithDebInfo MinSizeRe

add_definitions(-Wall -Werror)

cmake_minimum_required (VERSION 3.12)
project(datastruct)

set(SOURCE_FILES 
${PROJECT_SOURCE_DIR}/tree/tree.c
${PROJECT_SOURCE_DIR}/stack/stack.c
${PROJECT_SOURCE_DIR}/sort/sort.c
${PROJECT_SOURCE_DIR}/search/search.c
${PROJECT_SOURCE_DIR}/queue/queue.c
${PROJECT_SOURCE_DIR}/graph/graph.c
)
aux_source_directory(./	ROOT_SOURCES)
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${ROOT_SOURCES})


include_directories(${PROJECT_SOURCE_DIR})

add_executable(tree ${PROJECT_SOURCE_DIR}/tree/test.cc)
target_link_libraries(tree ${PROJECT_NAME})

add_executable(sort ${PROJECT_SOURCE_DIR}/sort/test.cc)
target_link_libraries(sort ${PROJECT_NAME})

add_executable(search ${PROJECT_SOURCE_DIR}/search/test.cc)
target_link_libraries(search ${PROJECT_NAME})

add_executable(graph ${PROJECT_SOURCE_DIR}/graph/test.cc)
target_link_libraries(graph ${PROJECT_NAME})

if(MSVC)
    # Use the static C library for all build types
    foreach(var
        CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
      )
      if(${var} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${var} "${${var}}")
      endif()
    endforeach()
endif(MSVC)


#cmake -G "MinGW Makefiles" .. ; mingw32-make.exe