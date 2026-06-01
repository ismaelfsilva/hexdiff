#include "hexdiff/hexdiff.hpp"

#include <algorithm>

namespace hexdiff {

namespace {
const char kHex[] = "0123456789abcdef";

void appendByte(std::string& s, uint8_t b) {
    s += kHex[b >> 4];
    s += kHex[b & 0xf];
}
}  // namespace

std::string hexDump(const uint8_t* data, size_t len) {
    std::string out;
    for (size_t i = 0; i < len; i += 16) {
        for (int shift = 28; shift >= 0; shift -= 4)
            out += kHex[(i >> shift) & 0xf];
        out += "  ";
        std::string ascii;
        for (size_t j = 0; j < 16; ++j) {
            if (j) out += ' ';
            if (i + j < len) {
                uint8_t b = data[i + j];
                appendByte(out, b);
                ascii += (b >= 0x20 && b <= 0x7e) ? static_cast<char>(b) : '.';
            } else {
                out += "  ";
            }
        }
        out += "  |";
        out += ascii;
        out += "|\n";
    }
    return out;
}

std::vector<Diff> diffBytes(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b) {
    std::vector<Diff> diffs;
    size_t n = std::max(a.size(), b.size());
    for (size_t i = 0; i < n; ++i) {
        int av = i < a.size() ? a[i] : -1;
        int bv = i < b.size() ? b[i] : -1;
        if (av != bv) diffs.push_back({i, av, bv});
    }
    return diffs;
}

}  // namespace hexdiff
