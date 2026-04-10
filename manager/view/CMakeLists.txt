find_package(X11 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(dispatcher REQUIRED)

include_directories(/usr/local/include)

link_directories(/usr/local/lib)

file(GLOB VIEW_SOURCES 
    src/*.cpp)

add_library(view ${VIEW_SOURCES})


target_include_directories(view PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                                        ${OpenCV_INCLUDE_DIRS})

target_link_libraries(view PUBLIC
                business
                nana
                X11
                Xft
                fontconfig
                pthread
                dispatcher::dispatcher
                ${OpenCV_LIBS}
)

add_custom_command(TARGET view POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:view>/../control/resources
    COMMENT "Movendo resources para a pasta de build")