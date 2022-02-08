cmake_minimum_required(VERSION 3.7)
project(SDLGameJam VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if(WIN32)
    set(SDL2_INCLUDE_DIR "C:/Program Files/mingw-w64/mingw64/include/SDL2")
    set(SDL2_LIBRARY_DIR "C:/Program Files/mingw-w64/mingw64/lib")
    set(SDL2_IMAGE_INCLUDE_DIR "C:/SDL_image/include/SDL2")
    set(SDL2_IMAGE_LIBRARY_DIR "C:/SDL_image/lib")
    set(SDL2_TTF_INCLUDE_DIR "C:/SDL_ttf/include/SDL2")
    set(SDL2_TTF_LIBRARY_DIR "C:/SDL_ttf/lib")
elseif(APPLE)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2TTF REQUIRED)
endif()

set(SOURCE_INCLUDES
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/src/States
    ${PROJECT_SOURCE_DIR}/src/Input
    ${PROJECT_SOURCE_DIR}/src/Level
    ${PROJECT_SOURCE_DIR}/src/Level/Objects
    ${PROJECT_SOURCE_DIR}/src/Collision
    ${PROJECT_SOURCE_DIR}/src/Entities
    ${PROJECT_SOURCE_DIR}/src/Render
    ${PROJECT_SOURCE_DIR}/src/Shop
    )
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/GameLoop.cpp
    ${PROJECT_SOURCE_DIR}/src/States/State.cpp
    ${PROJECT_SOURCE_DIR}/src/States/GameState.cpp
    ${PROJECT_SOURCE_DIR}/src/Input/Mouse.cpp
    ${PROJECT_SOURCE_DIR}/src/Level/Tilemap.cpp
    ${PROJECT_SOURCE_DIR}/src/Level/Grid.cpp
    ${PROJECT_SOURCE_DIR}/src/Level/Object.cpp
    ${PROJECT_SOURCE_DIR}/src/Level/Objects/RightTriangle.cpp
    ${PROJECT_SOURCE_DIR}/src/Level/Objects/Square.cpp
    ${PROJECT_SOURCE_DIR}/src/Level/Objects/Diamond.cpp
    ${PROJECT_SOURCE_DIR}/src/Level/Objects/LongRightTriangle.cpp
    ${PROJECT_SOURCE_DIR}/src/Collision/Edge.cpp
    ${PROJECT_SOURCE_DIR}/src/Collision/CollisionDetector.cpp
    ${PROJECT_SOURCE_DIR}/src/Entities/Entity.cpp
    ${PROJECT_SOURCE_DIR}/src/Entities/Projectile.cpp
    ${PROJECT_SOURCE_DIR}/src/Entities/Goal.cpp
    ${PROJECT_SOURCE_DIR}/src/Render/Spritesheet.cpp
    ${PROJECT_SOURCE_DIR}/src/Shop/Clickable.cpp
    ${PROJECT_SOURCE_DIR}/src/Shop/Button.cpp
    ${PROJECT_SOURCE_DIR}/src/Shop/ShopButton.cpp
    )

if(WIN32)
    include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SOURCE_INCLUDES})
    add_executable(SDLGameJam ${SOURCES})
    # remove -mconsole for release builds
    target_link_libraries(SDLGameJam -lmingw32 ${SDL2_LIBRARY_DIR}/libSDL2main.a ${SDL2_LIBRARY_DIR}/libSDL2.dll.a ${SDL2_IMAGE_LIBRARY_DIR}/libSDL2_image.dll.a ${SDL2_TTF_LIBRARY_DIR}/libSDL2_ttf.dll.a -mwindows -mconsole)
elseif(APPLE)
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR} ${SOURCE_INCLUDES})
    add_executable(SDLGameJam ${SOURCES})
    target_link_libraries(SDLGameJam ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})
endif()

add_custom_command(TARGET SDLGameJam POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${PROJECT_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:SDLGameJam>/res/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
