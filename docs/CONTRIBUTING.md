# Contributing Guide

Thank you for helping build Abyssforge! This document outlines expectations for contributors.

## Workflow

1. Fork the repository and create a feature branch.
2. Run `cmake -S . -B build` and `cmake --build build` before submitting changes.
3. Execute the deterministic test suite with `ctest --test-dir build`.
4. Update or add documentation for user-facing changes.
5. Submit a pull request describing the motivation, implementation details, and validation evidence.

## Coding standards

- Use C++20 with `clang-format` (config forthcoming) and `clang-tidy`.
- Ensure deterministic RNG usage; avoid `std::random_device`.
- Favor descriptive naming and document interfaces with Doxygen comments.
- Avoid exceptions across module boundaries; prefer `expected`-style return objects.

## Tests

- Unit tests live in `tests/` and use the Doctest framework.
- Performance benchmarks belong in `benchmarks/`.
- Add regression tests for bug fixes where possible.

## Commit messages

Follow the Conventional Commits style:

- `feat:` new features
- `fix:` bug fixes
- `docs:` documentation updates
- `refactor:` structural changes
- `test:` test-related updates

## Communication

Join the (upcoming) `#abyssforge-dev` channel on the community Discord for coordination. Major decisions are tracked in GitHub Discussions.

## Code of conduct

All contributors must follow the [Code of Conduct](CODE_OF_CONDUCT.md).
