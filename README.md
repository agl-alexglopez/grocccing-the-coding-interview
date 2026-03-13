# GroCCCing the Coding Interview

This repository contains coding interview practice problems in C, specifically to test my [C Container Collection (CCC)](https://github.com/agl-alexglopez/ccc).

## Rationale

Why prepare for coding interviews in languages like Python, Java, or C++? Who needs helpful standard libraries or robust web browser interfaces? Success has two C's for a reason. A C compiler is all you need.

> "If you want a nine figure offer from Meta, plus options, LeetCode in C."
>
> -- Brian W. Kernighan and Dennis M. Ritchie (1978)

## About

This project serves as a testbed for my C Container Collection. By solving interview-style problems in C, I simultaneously verify container correctness, build real usage examples, and avoid the soul crushing boredom that comes with logging on to LeetCode.

Check back for updates as the repository matures. Right now it’s a personal development helper, but proper build instructions and usage examples will arrive as things stabilize.

## Build Tips

A `CMakePresets.json` file is provided. I recommend setting up a `CMakeUserPresets.json` file for your own compiler and build system preferences. Here is a sample.

```json
{
    "version": 3,
    "cmakeMinimumRequired": {
        "major": 3,
        "minor": 23,
        "patch": 0
    },
    "configurePresets": [
        {
            "name": "my-gcc-debug",
            "inherits": ["default-debug"],
            "generator": "Ninja",
            "cacheVariables": {
                "CMAKE_C_COMPILER": "gcc-15.2"
            }
        },
        {
            "name": "my-gcc-release",
            "inherits": ["default-release"],
            "generator": "Ninja",
            "cacheVariables": {
                "CMAKE_C_COMPILER": "gcc-15.2"
            }
        },
        {
            "name": "my-clang-debug",
            "inherits": ["default-debug"],
            "generator": "Ninja",
            "cacheVariables": {
                "CMAKE_C_COMPILER": "clang-22"
            }
        },
        {
            "name": "my-clang-release",
            "inherits": ["default-release"],
            "generator": "Ninja",
            "cacheVariables": {
                "CMAKE_C_COMPILER": "clang-22"
            }
        },
        {
            "name": "my-sanitize-debug",
            "inherits": ["gcc-sanitize-debug"],
            "generator": "Ninja",
            "cacheVariables": {
                "CMAKE_C_COMPILER": "gcc-15.2"
            }
        },
        {
            "name": "my-sanitize-release",
            "inherits": ["gcc-sanitize-release"],
            "generator": "Ninja",
            "cacheVariables": {
                "CMAKE_C_COMPILER": "gcc-15.2"
            }
        }
    ]
}
```
