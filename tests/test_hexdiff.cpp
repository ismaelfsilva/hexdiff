#include "hexdiff/hexdiff.hpp"

#include <cassert>
#include <cstdint>
#include <vector>

int main() {
    using namespace hexdiff;

    // Identical buffers => empty diff.
    std::vector<uint8_t> x{1, 2, 3};
    assert(diffBytes(x, x).empty());

    // One differing byte => one Diff with right offset/values.
    std::vector<uint8_t> a{1, 2, 3};
    std::vector<uint8_t> b{1, 9, 3};
    auto d = diffBytes(a, b);
    assert(d.size() == 1);
    assert(d[0].off == 1);
    assert(d[0].a == 2);
    assert(d[0].b == 9);

    // Different sizes => diff entries for the tail (missing byte == -1).
    std::vector<uint8_t> s{1, 2};
    std::vector<uint8_t> l{1, 2, 3, 4};
    auto t = diffBytes(s, l);
    assert(t.size() == 2);
    assert(t[0].off == 2 && t[0].a == -1 && t[0].b == 3);
    assert(t[1].off == 3 && t[1].a == -1 && t[1].b == 4);

    // hexDump of {0x41,0x42} contains "41 42" and "AB".
    std::vector<uint8_t> ab{0x41, 0x42};
    std::string dump = hexDump(ab.data(), ab.size());
    assert(dump.find("41 42") != std::string::npos);
    assert(dump.find("AB") != std::string::npos);

    return 0;
}
