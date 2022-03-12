cmake_minimum_required(VERSION 3.7)
project(GeoJoe VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

set(GEOJOE_VERSION "0.1a")

if(WIN32)
    set(SDL2_INCLUDE_DIR "C:/Program Files/mingw64/include/SDL2")
    set(SDL2_LIBRARY_DIR "C:/Program Files/mingw64/lib")
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
    ${PROJECT_SOURCE_DIR}/src/GUI
    ${PROJECT_SOURCE_DIR}/src/FileIO
    )
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/GameLoop.cpp
    ${PROJECT_SOURCE_DIR}/src/States/State.cpp
    ${PROJECT_SOURCE_DIR}/src/States/GameState.cpp
    ${PROJECT_SOURCE_DIR}/src/Input/Mouse.cpp
    ${PROJECT_SOURCE_DIR}/src/Input/Keyboard.cpp
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
    ${PROJECT_SOURCE_DIR}/src/Render/Text.cpp
    ${PROJECT_SOURCE_DIR}/src/GUI/Clickable.cpp
    ${PROJECT_SOURCE_DIR}/src/GUI/Button.cpp
    ${PROJECT_SOURCE_DIR}/src/GUI/ShopButton.cpp
    ${PROJECT_SOURCE_DIR}/src/GUI/ObjectClickable.cpp
    ${PROJECT_SOURCE_DIR}/src/GUI/Shop.cpp
    ${PROJECT_SOURCE_DIR}/src/GUI/ResetButton.cpp
    ${PROJECT_SOURCE_DIR}/src/GUI/NextLevelButton.cpp
    ${PROJECT_SOURCE_DIR}/src/FileIO/FileIO.cpp
    ${PROJECT_SOURCE_DIR}/src/FileIO/LevelLoader.cpp
    )

if(WIN32)
    include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SOURCE_INCLUDES})
    add_executable(GeoJoe ${SOURCES})
    # remove -mconsole for release builds
    target_link_libraries(GeoJoe -lmingw32 ${SDL2_LIBRARY_DIR}/libSDL2main.a ${SDL2_LIBRARY_DIR}/libSDL2.dll.a ${SDL2_IMAGE_LIBRARY_DIR}/libSDL2_image.dll.a ${SDL2_TTF_LIBRARY_DIR}/libSDL2_ttf.dll.a -mwindows)
    add_custom_command(TARGET GeoJoe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:GeoJoe>/res/)
elseif(APPLE)
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR} ${SOURCE_INCLUDES})
    add_executable(GeoJoe MACOSX_BUNDLE ${SOURCES})
    target_link_libraries(GeoJoe ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})
    set_target_properties(GeoJoe PROPERTIES
        BUNDLE True
        MACOSX_BUNDLE_EXECUTABLE_NAME GeoJoe
        MACOSX_BUNDLE_ICON_FILE icon.png
        MACOSX_BUNDLE_GUI_IDENTIFIER com.straub.geojoe
        MACOSX_BUNDLE_LONG_VERSION_STRING ${GeoJoe_VERSION}
        MACOSX_BUNDLE_BUNDLE_NAME GeoJoe
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${GeoJoe_VERSION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${GeoJoe_VERSION}
        MACOSX_BUNDLE_COPYRIGHT "© Tyler Straub 2022"
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/cmake/Info.plist.in)
    file(COPY ${CMAKE_SOURCE_DIR}/cmake/icon.png DESTINATION GeoJoe.app/Contents/Resources)
    install(CODE "
        include(BundleUtilities)
        fixup_bundle(\"${CMAKE_BINARY_DIR}/GeoJoe.app\"   \"\"   \"${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY}\")" COMPONENT Runtime)
    add_custom_command(TARGET GeoJoe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:GeoJoe>/../Resources/res/)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
