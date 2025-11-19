# Contributing to Sqlpp11 Adapter

Thank you for your interest in contributing to Sqlpp11 Adapter! This document provides guidelines for contributing to the project.

## Getting Started

1. Fork the repository
2. Clone your fork: `git clone https://github.com/YOUR_USERNAME/sqlpp11-adapter.git`
3. Create a new branch: `git checkout -b feature/your-feature-name`

## Development Setup

### Requirements

- C++17 or higher compiler
- CMake 3.19 or higher
- MySQL client library
- [Casbin-CPP](https://github.com/casbin/casbin-cpp)
- [sqlpp11](https://github.com/rbock/sqlpp11)

### Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Running Tests

```bash
cd build
./test
```

## Coding Standards

- Follow the existing code style (we use clang-format with Google style)
- Write clear, self-documenting code
- Add comments for complex logic
- Include Apache 2.0 license header in all new files
- Use C++17 features appropriately

### Code Formatting

Format your code using clang-format:

```bash
clang-format -i <file>
```

## Making Changes

1. Make your changes in your feature branch
2. Add or update tests as needed
3. Ensure all tests pass
4. Commit your changes with clear, descriptive commit messages
5. Push to your fork
6. Submit a pull request

## Pull Request Guidelines

- Provide a clear description of the changes
- Reference any related issues
- Ensure CI passes
- Keep changes focused and atomic
- Update documentation as needed

## License

By contributing to Sqlpp11 Adapter, you agree that your contributions will be licensed under the Apache 2.0 License.

## Questions?

If you have questions, please open an issue for discussion.
