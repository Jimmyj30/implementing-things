# Readme

## Running program

First time setup:

```sh
cmake -S . -B build
```

To build and run the project:

```sh
cmake --build build
./build/order-book
```

## Running tests

```sh
cmake --build build && ctest --test-dir build --output-on-failure
```
