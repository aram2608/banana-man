add_library(bmanlib
    bmanlib/bman/bman.cpp
    bmanlib/game/game.cpp
    bmanlib/platforms/platform.cpp
    bmanlib/platforms/grid.cpp
)

find_package(raylib 3.0 REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(bmanlib
    PUBLIC 
    raylib 
    glfw
)

target_include_directories(bmanlib
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/bmanlib/
)

target_compile_options(bmanlib
    PRIVATE
    -Wall 
    -Wextra 
    -Wpedantic 
    -Wconversion
    -Wpessimizing-move
    -Wredundant-move
    -Wmove
    -Wrange-loop-construct
)

add_executable(bman
    app/main.cpp
)

# raylib and gflw are propogated from the library
target_link_libraries(bman
    PRIVATE
    bmanlib
)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if(APPLE)
    target_link_libraries(bman
        PRIVATE
            "-framework Cocoa"
            "-framework IOKit"
            "-framework OpenGL"
    )
endif()