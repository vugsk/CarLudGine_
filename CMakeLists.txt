cmake_minimum_required(VERSION 3.26)

project(CarLudGine)
set(CMAKE_CXX_STANDARD 26)

## Curses
if(WIN32)
    include_directories(${PDCURSES_DIR})
    file(GLOB PDCURSES_SRC ${PDCURSES_DIR}/pdcurses/*.c)
    file(GLOB PDCURSES_SRC_WINCON ${PDCURSES_DIR}/wincon/*.c)
    add_library(pdcurses ${PDCURSES_SRC} ${PDCURSES_SRC_WINCON})
    target_compile_options(pdcurses PRIVATE -DPDC_WIDE -DPDC_FORCE_UTF8)
    set(PD_OR_N_CURSES pdcurses)
else()
    set(CURSES_NEED_NCURSES ON)
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    set(PD_OR_N_CURSES ${CURSES_LIBRARIES})
endif()

## Boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS)

## Nlohmann json
find_package(nlohmann_json 3.2.0 REQUIRED)

## Yaml-cpp
find_package(yaml-cpp REQUIRED)
include_directories(${YAML_CPP_INCLUDE_DIRS})

## OpenAL
include(FetchContent)
FetchContent_Declare(
        openalpp
        GIT_REPOSITORY https://github.com/Laguna1989/OpenALpp.git
        GIT_TAG master
)
FetchContent_MakeAvailable(openalpp)

#configure_file(
#    ./Setting_game.json
#    ${CMAKE_CURRENT_BINARY_DIR}/Setting_game.json
#)

include_directories(include/CarLudGine)
file(GLOB SRC_ROOT src/main.cpp)
file(GLOB SRC_CURSESCPP 
    src/Module/CursesCpp/*.cpp
)

# set(SRC_ROOT 
#     src/main.cpp
# )

# set(SRC_CURSESCPP
#     src/Module/CursesCpp/Window.cpp
#     src/Module/CursesCpp/Config.cpp
# )



add_executable( CarLudGine ${SRC_ROOT} ${SRC_CURSESCPP}
                include/CarLudGine/ParserJsonFiles.hpp
                src/Module/ParserFiles/ParserJsonFiles.cpp
                src/Module/ParserFiles/ParserYamlFiles.cpp
                include/CarLudGine/ParserYamlFiles.hpp
                src/Module/ParserFiles/ParserIniFiles.cpp
                include/CarLudGine/ParserIniFiles.hpp
                src/Module/SoundControll/SoungControl.cpp
                include/CarLudGine/SoungControl.hpp
)

# target_include_directories(CarLudGine PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(CarLudGine
    OpenALpp_Lib
    ${PD_OR_N_CURSES}
    ${nlohmann_LIB}
    ${YAML_CPP_LIBRARIES}
    ${Boost_INCLUDE}
)

## building project
# add_library(${PROJECT_NAME} ${SRC_ROOT})
# target_include_directories(${PROJECT_NAME} PUBLIC includes)
# target_link_libraries(${PROJECT_NAME} ${PD_OR_N_CURSES} ${Boost_LIBRARIES} ${nlohmann_LIB})
# include(GNUInstallDirs)
# install(TARGETS ${PROJECT_NAME}
#         RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#         ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
# install(DIRECTORY includes/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# ## ABI version
# set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION 1)
