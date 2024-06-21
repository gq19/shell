#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>
#include"smsh.h"
std::string next_cmd(std::string& prompt, std::istream& input) {
    std::cout << prompt;
    std::string buf;
    int c;

    while ((c = input.get()) != EOF) {
        if (c == '\n') {
            break;
        }
        buf.push_back(static_cast<char>(c));
    }

    if (c == EOF && buf.empty()) {
        return "";
    }

    return buf;
}

inline bool is_delim(char x) {
    return x == ' ' || x == '\t';
}

std::vector<std::string> splitline(const std::string& line) {
    std::vector<std::string> args;
    const char* cp = line.c_str();
    const char* start = nullptr;
    int len = 0;
    while (*cp != '\0') {
        while (is_delim(*cp)) {
            cp++;
        }
        if (*cp == '\0') {
            break;
        }

        start = cp;
        len = 1;
        while (*++cp != '\0' && !is_delim(*cp)) {
            len++;
        }

        args.emplace_back(start, len);
    }

    return args;
}

void freelist(std::vector<std::string>& list) {
    list.clear();
}

void* emalloc(size_t n) {
    void* rv = malloc(n);
    if (rv == nullptr) {
        throw std::runtime_error("out of memory");
    }
    return rv;
}

void* erealloc(void* p, size_t n) {
    void* rv = realloc(p, n);
    if (rv == nullptr) {
        throw std::runtime_error("realloc() failed");
    }
    return rv;
}
