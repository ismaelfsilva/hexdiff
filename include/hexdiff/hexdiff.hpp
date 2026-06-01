#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace hexdiff {

// Classic hex dump: "OFFSET(8 hex)  16 hex bytes  |ASCII|" per 16-byte row.
std::string hexDump(const uint8_t* data, size_t len);

// A single differing byte. `a`/`b` are byte values, or -1 if that side has no
// byte at this offset (sizes differ).
struct Diff {
    size_t off;
    int a;
    int b;
};

// Byte-level diff of two buffers. Offsets past the end of the shorter buffer
// use -1 for the missing side.
std::vector<Diff> diffBytes(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b);

}  // namespace hexdiff
