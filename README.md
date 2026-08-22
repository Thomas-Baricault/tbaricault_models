# tbaricault/models

[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-blue)

## Description

This is a C++23 library providing tools to create data models with custom fields and validation policies. Loading and saving models in JSON format is handled using  `nlohmann/json`.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
    - [Download and install](#download-and-install)
    - [Uninstall](#uninstall)
    - [CMake](#cmake)
    - [Include](#include)
    - [Environment](#environment)
- [Documentation](#documentation)
- [Examples](#examples)
    - [Simple model](#simple-model)
    - [Model inheritance](#model-inheritance)
    - [Model saving](#model-saving)
- [License](#license)

## Features

- Custom validation policies
- Auto-validation
- Flexible model pattern
- Compile-time constraints and options

## Requirements

- C++23 or later
- CMake 3.20 or later
- [nlohmann/json](https://github.com/nlohmann/json)
- [tbaricault/templates](https://github.com/Thomas-Baricault/tbaricault_templates)
- [tbaricault/uniconvert](https://github.com/Thomas-Baricault/tbaricault_uniconvert)

## Usage

### Download and install

```bash
git clone https://github.com/Thomas-Baricault/tbaricault_models.git
cd tbaricault_models
make install
```

### Uninstall

```bash
make uninstall
```

### CMake

Add the library to your project:

```cmake
find_package(tbaricault_models REQUIRED)

target_link_libraries(
    my_target
    PRIVATE
        tbaricault::models
)
```

### Include

```cpp
#include <tbaricault/models.hpp>
```

### Environment

If you have a custom C++ installation, you can edit the `ENV` variable in the `Makefile` to specify your environment path.

Example on Windows with MSYS2/MinGW64:

```makefile
ENV = C:/msys64/mingw64
```

## Documentation

Read the complete documentation at [https://docs.thomas-baricault.fr/models](https://docs.thomas-baricault.fr/models).

## Examples

### Simple model

```cpp
#include <iostream>
#include <tbaricault/models.hpp>


char abc[4] = "abc";


struct Test
    : tbaricault::models::Model<
        tbaricault::models::BaseModel, Test,
        tbaricault::models::FieldInfo<
            "i",
            tbaricault::models::Field<
                int,
                tbaricault::models::constraints::Policy<>,
                tbaricault::models::options::Policy<
                    tbaricault::models::options::Default<73>
                >
            >
        >,
        tbaricault::models::FieldInfo<
            "s",
            tbaricault::models::Field<
                std::string,
                tbaricault::models::constraints::Policy<>,
                tbaricault::models::options::Policy<
                    tbaricault::models::options::Default<abc>
                >
            >
        >
    >
{};


int main(int argc, char** argv)
{
    Test test;

    auto& i = test.get<"i">();
    auto& s = test.get<"s">();

    std::cout
        << "i: " << i << std::endl
        << "s: " << s.get() << std::endl;

    i = std::any(42);

    std::cout
        << "i: " << i << std::endl
        << "s: " << s.get() << std::endl;

    return (0);
}
```

Output:

```text
i: 73
s: abc
i: 42
s: abc
```

### Model inheritance

```cpp
#include <iostream>
#include <tbaricault/models.hpp>


struct A
    : tbaricault::models::Model<
        tbaricault::models::BaseModel, A,
        tbaricault::models::FieldInfo<
            "i",
            tbaricault::models::Field<
                int,
                tbaricault::models::constraints::Policy<>,
                tbaricault::models::options::Policy<
                    tbaricault::models::options::Default<73>
                >
            >
        >
    >
{};


struct B
    : tbaricault::models::Model<
        A, B,
        tbaricault::models::FieldInfo<
            "j",
            tbaricault::models::Field<
                int,
                tbaricault::models::constraints::Policy<>,
                tbaricault::models::options::Policy<
                    tbaricault::models::options::Default<42>
                >
            >
        >
    >
{};


int main(int argc, char** argv)
{
    B b;

    auto& i = b.get<"i">();
    auto& j = b.get<"j">();

    std::cout
        << "i: " << i << std::endl
        << "j: " << j << std::endl;

    return (0);
}
```

Output:

```text
i: 73
j: 42
```

### Model saving

```cpp
#include <tbaricault/models.hpp>


struct Test
    : tbaricault::models::Model<
        tbaricault::models::BaseModel, Test,
        tbaricault::models::FieldInfo<
            "i",
            tbaricault::models::Field<
                int,
                tbaricault::models::constraints::Policy<>,
                tbaricault::models::options::Policy<
                    tbaricault::models::options::Default<73>
                >
            >
        >,
        tbaricault::models::FieldInfo<
            "j",
            tbaricault::models::Field<
                int,
                tbaricault::models::constraints::Policy<>,
                tbaricault::models::options::Policy<
                    tbaricault::models::options::Default<42>
                >
            >
        >
    >
{};


int main(int argc, char** argv)
{
    Test test;

    test.save("test.json");

    return (0);
}
```

```console
$ ./my_program
$ cat test.json
{
    "i": 73,
    "j": 42
}
```

## Roadmap

- `List`, `Set` and `Map` types to wrap containers behavior
- Support `Field` as map key

## License

This project is licensed under the MIT License.

See [LICENSE](LICENSE) for details.
