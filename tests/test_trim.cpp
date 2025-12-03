#include "../src/core/Utils.hpp"
#include <iostream>
#include <cassert>

int main() {
    // Test 1: Normal string
    assert(Core::Utils::trim("hello") == "hello");

    // Test 2: Leading spaces
    assert(Core::Utils::trim("   hello") == "hello");

    // Test 3: Trailing spaces
    assert(Core::Utils::trim("hello   ") == "hello");

    // Test 4: Both
    assert(Core::Utils::trim("   hello   ") == "hello");

    // Test 5: Empty
    assert(Core::Utils::trim("") == "");

    // Test 6: Only spaces
    assert(Core::Utils::trim("     ") == "");

    // Test 7: Newlines and tabs
    assert(Core::Utils::trim("\t\n hello \r\v") == "hello");

    std::cout << "All trim tests passed!" << std::endl;
    return 0;
}
