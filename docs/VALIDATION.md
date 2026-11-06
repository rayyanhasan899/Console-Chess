# Validation and limitations

## Observed locally — 6 November 2026

- CMake configure/build succeeded on Windows with MSVC 19.50.35730 and C++17.
- CTest: 2/2 executables passed (`input_test`, `rules_test`), including invalid coordinates, malformed input, basic movement/blocking and missing-king handling.
- Tests keep assertions enabled, including Release configurations.
- The source still has compiler warnings and a custom rule variant. These focused checks do not establish full chess-rule compliance, checkmate correctness, or a complete interactive game session.

Run: `cmake -S . -B build`, `cmake --build build --config Debug`, then `ctest --test-dir build -C Debug --output-on-failure`.

Changes bound user input, initialize validation state, guard missing board state and bound castling-offset access. They do not add or replace chess rules.
