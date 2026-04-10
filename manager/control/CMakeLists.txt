
find_package(dispatcher REQUIRED)

file(GLOB CONTROL_SOURCES src/*.cpp)

add_executable(app
    main.cpp
    ${CONTROL_SOURCES}
)

target_include_directories(app
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(app PRIVATE dispatcher::dispatcher
    view
)