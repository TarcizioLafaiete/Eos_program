find_package(dispatcher REQUIRED)


include_directories(/usr/local/include)
link_directories(/usr/local/lib)

file(GLOB BUSINESS_SOURCES
    src/*.cpp)

add_library(business ${BUSINESS_SOURCES})

target_include_directories(business PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(business PUBLIC
    dispatcher::dispatcher
)