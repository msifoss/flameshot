# Proof-of-life test. Exists to verify the test framework wiring itself works
# (CMake → ctest → Qt Test runner → reported pass), independent of any
# production code. Real subsystem tests live in sibling directories.

flameshot_add_unit_test(
    NAME    sanity
    SOURCES test_sanity.cpp
)
