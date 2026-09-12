// Simple Vector Test File

#include <iostream>
#include "simplevector.h"

int main() {

    ss::Vector<int> name;

    // Add elements
    name.PushBack(12);
    name.PushBack(8);
    name.PushBack(42);

    // Access with operator[]
    std::cout << "name[0] = "
              << name[0]
              << '\n';

    std::cout << "name[1] = "
              << name[1]
              << '\n';

    std::cout << "name[2] = "
              << name[2]
              << '\n';

    // Change an element
    name[1] = 100;

    std::cout << "After modification:\n";

    std::cout << "name[1] = "
              << name[1]
              << '\n';

    // Get / Set
    name.Set(0, 999);

    std::cout << "name.Get(0) = "
              << name.Get(0)
              << '\n';

    // Vector information
    std::cout << "\nSize: "
              << name.GetSize()
              << '\n';

    std::cout << "Capacity: "
              << name.GetCapacity()
              << '\n';

    return 0;
}