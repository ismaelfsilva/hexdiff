#include "hexdiff/hexdiff.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

namespace {
std::vector<uint8_t> readFile(const char* path, bool& ok) {
    std::ifstream f(path, std::ios::binary);
    if (!f) {
        ok = false;
        return {};
    }
    ok = true;
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(f)),
                                std::istreambuf_iterator<char>());
}

std::string byteStr(int v) {
    if (v < 0) return "--";
    static const char kHex[] = "0123456789abcdef";
    std::string s;
    s += kHex[(v >> 4) & 0xf];
    s += kHex[v & 0xf];
    return s;
}
}  // namespace

int main(int argc, char** argv) {
    if (argc == 2) {
        bool ok = false;
        auto data = readFile(argv[1], ok);
        if (!ok) {
            std::cerr << "error: cannot open " << argv[1] << "\n";
            return 1;
        }
        std::cout << hexdiff::hexDump(data.data(), data.size());
        return 0;
    }
    if (argc == 3) {
        bool oka = false, okb = false;
        auto a = readFile(argv[1], oka);
        auto b = readFile(argv[2], okb);
        if (!oka) {
            std::cerr << "error: cannot open " << argv[1] << "\n";
            return 1;
        }
        if (!okb) {
            std::cerr << "error: cannot open " << argv[2] << "\n";
            return 1;
        }
        auto diffs = hexdiff::diffBytes(a, b);
        for (const auto& d : diffs)
            std::printf("%08zx  %s  %s\n", d.off, byteStr(d.a).c_str(), byteStr(d.b).c_str());
        std::cout << diffs.size() << " differing byte(s)\n";
        std::cout << argv[1] << ": " << a.size() << " bytes, " << argv[2] << ": " << b.size()
                  << " bytes\n";
        if (a.size() != b.size())
            std::cout << (a.size() < b.size() ? argv[1] : argv[2]) << " is smaller\n";
        return diffs.empty() ? 0 : 1;
    }
    std::cerr << "usage: hexdiff <file> | hexdiff <a> <b>\n";
    return 1;
}
