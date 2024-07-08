# .

cmake_minimum_required(VERSION 3.20)

project(gtkmm3 VERSION 1.0.0.0 DESCRIPTION "Programa prueba de gtkmm3" LANGUAGES CXX)

set(BIN_NAME "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}-${PROJECT_VERSION_MINOR}")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)

add_executable(${BIN_NAME})

add_subdirectory(src)
# add_subdirectory(data)

target_compile_definitions(${BIN_NAME} PRIVATE
	PROGRAM_NAME="${PROJECT_NAME}"
	PROGRAM_TITLE="${PROJECT_NAME} ${PROJECT_VERSION}"
	PROGRAM_APPID="${PROJECT_NAME}.aullidolunar.${BIN_NAME}"
)
target_compile_options(${BIN_NAME} PRIVATE ${GTKMM3_CFLAGS_OTHER})
target_include_directories(${BIN_NAME} PRIVATE ${GTKMM3_INCLUDE_DIRS})
target_link_directories(${BIN_NAME} PRIVATE ${GTKMM3_LIBRARY_DIRS})
target_link_libraries(${BIN_NAME} PRIVATE ${GTKMM3_LIBRARIES})

add_custom_target(run
    COMMAND ${BIN_NAME}
    DEPENDS ${BIN_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(dist
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
	COMMAND ${CMAKE_COMMAND} -E tar cvf "${BIN_NAME}.7z" --format=7zip data/ src/ CMakeLists.txt
)