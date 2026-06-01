# hexdiff

Hex dump and byte-level binary diff CLI (C++17).

## Build

```sh
cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

## Usage

Hex dump a file (`OFFSET  16 hex bytes  |ASCII|` per row):

```sh
hexdiff <file>
```

Byte-level diff of two files (differing offsets with both byte values, then a summary):

```sh
hexdiff <a> <b>
```

## Library

`include/hexdiff/hexdiff.hpp`:

- `std::string hexDump(const uint8_t* data, size_t len)`
- `struct Diff { size_t off; int a; int b; }`
- `std::vector<Diff> diffBytes(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b)` — uses `-1` for a missing byte when sizes differ.

## License

MIT
