# Tests for CLI argument/option value types. The full CommandLineParser
# depends on AbstractLogger and GlobalValues which transitively pull most of
# utils/ into the test binary — until a library target is extracted from
# src/ (deferred to v15 per the staff review), parser-level tests stay out
# of scope here.
#
# End-to-end CLI behavior (`flameshot --help`, `flameshot --version`,
# subcommand routing) is covered by future per-platform smoke tests
# (story S2.5), which run the real packaged binary as a subprocess.

flameshot_add_unit_test(
    NAME    cli_argument
    SOURCES test_cli_argument.cpp
    EXTRA_SOURCES
        ${CMAKE_SOURCE_DIR}/src/cli/commandargument.cpp
)

flameshot_add_unit_test(
    NAME    cli_option
    SOURCES test_cli_option.cpp
    EXTRA_SOURCES
        ${CMAKE_SOURCE_DIR}/src/cli/commandoption.cpp
        ${CMAKE_SOURCE_DIR}/src/cli/commandargument.cpp
)
