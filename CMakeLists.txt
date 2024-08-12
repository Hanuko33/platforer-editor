cmake_minimum_required(VERSION 3.10)
project(platforer-editor)
find_package(PkgConfig)
pkg_check_modules(SDL sdl2)
pkg_check_modules(SDL2_IMAGE SDL2_image)
pkg_check_modules(SDL2_TTF SDL2_ttf)
set(CMAKE_BUILD_TYPE Debug)
add_executable(platforer-editor list/list.c text.c main.c)

target_link_libraries(platforer-editor
    SDL2 SDL2_image SDL2_ttf
    ${SDL_LDFLAGS} -lm)
