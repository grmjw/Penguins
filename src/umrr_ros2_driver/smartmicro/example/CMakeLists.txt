project(SmartAccessExample)

cmake_minimum_required(VERSION 3.13)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/${SMART_ACCESS_LIB_FOLDER})

add_executable(example_app
               src/example_app.cpp)

target_include_directories(example_app PUBLIC
                           ../include)

if(WIN32)
target_link_libraries(example_app
                      smart_access)
else()
target_link_libraries(example_app
                      smart_access
                      com_lib
                      osal
                      dl)
endif()

install(TARGETS example_app DESTINATION bin)
