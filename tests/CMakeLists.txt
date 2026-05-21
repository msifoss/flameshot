# Test tree entry point. Only included from the top-level CMakeLists.txt when
# BUILD_TESTING=ON. enable_testing() has already been called by the parent.
#
# Layout convention:
#   tests/unit/<subsystem>/   — fast, hermetic Qt Test executables
#   tests/integration/        — slower tests that touch the filesystem / display
#
# See docs/CONTRIBUTING.md for the test-writing workflow.

find_package(
    Qt${QT_VERSION_MAJOR}
    CONFIG
    REQUIRED
    Test
)

add_subdirectory(unit)
