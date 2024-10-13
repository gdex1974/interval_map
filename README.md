# Interval Map

This project implements an `interval_map` class in C++ along with a suite of unit tests to ensure its correctness.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
- [Usage](#usage)
- [Running Tests](#running-tests)
- [Contributing](#contributing)
- [License](#license)

## Overview

The `interval_map` class works like std::map but instead of simple key-value mapping it associates a value with a 
semi-open interval of keys [first, last) -> value.
The intervals are stored in optimized way inside the underlying std::map container.
The assign method tries to simplify the intervals by merging them if possible.

## Features

- log(N) complexity for insert and lookup operations.
- Automatic interval simplification on insertions.

## Prerequisites

- C++11 or later
- CMake 3.9 or later
- Google Test for unit tests

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/gdex1974/interval_map.git
   ```
2. Add path to cloned repository to CMakeLists.txt in your project:
   ```cmake
   add_subdirectory(path/to/interval_map)
   target_link_libraries(your_project interval_map)
   ```

## Usage

To use the `interval_map` class in your C++ code, include the header file and create an instance of the class:

```cpp
#include "interval_map.h"

int main() {
    interval_map<int, int> map(0);

    // Insert intervals
    map.insert(1, 5, 10);
    map.insert(3, 7, 20);

    // Query values
    auto r = map[4]; // == 20
    ...
    return 0;
}
```

## Running Tests

To run the unit tests, navigate to the build directory and execute the test binary:

```sh
cmake -B build -S .
cmake --build build --target all
ctest --test-dir build/tests/
```

The output will show the results of each test case.

## Contributing

Contributions are welcome!

## License

This project is licensed under the BSD 3-Clause License - see the [LICENSE](LICENSE) file for details.
