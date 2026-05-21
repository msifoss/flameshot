# Helper that wires up a Qt Test executable with the conventions every unit
# test in this tree follows: AUTOMOC for Q_OBJECT, Qt Test link, registration
# with ctest, and a uniform per-test name prefix.
#
# Usage:
#   flameshot_add_unit_test(
#       NAME    sanity
#       SOURCES test_sanity.cpp
#   )
#
# To pull in production sources (e.g. ConfigHandler) for testing, list them in
# EXTRA_SOURCES with paths relative to ${CMAKE_SOURCE_DIR}. The test executable
# compiles those .cpp files into its own translation unit. For the scaffold,
# no test does this yet — the first one will arrive with story S2.2.
function(flameshot_add_unit_test)
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES EXTRA_SOURCES LINK)
    cmake_parse_arguments(FUT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT FUT_NAME)
        message(FATAL_ERROR "flameshot_add_unit_test: NAME is required")
    endif()
    if(NOT FUT_SOURCES)
        message(FATAL_ERROR "flameshot_add_unit_test(${FUT_NAME}): SOURCES is required")
    endif()

    set(_target "test_${FUT_NAME}")
    add_executable(${_target} ${FUT_SOURCES} ${FUT_EXTRA_SOURCES})

    set_target_properties(${_target} PROPERTIES
        AUTOMOC ON
        AUTORCC ON
    )

    target_include_directories(${_target} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
    )

    target_link_libraries(${_target} PRIVATE
        Qt${QT_VERSION_MAJOR}::Test
        Qt${QT_VERSION_MAJOR}::Core
        ${FUT_LINK}
    )

    add_test(
        NAME flameshot.${FUT_NAME}
        COMMAND ${_target}
    )
endfunction()

add_subdirectory(sanity)
