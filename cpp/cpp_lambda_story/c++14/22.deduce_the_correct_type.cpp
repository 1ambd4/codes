#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>

int main()
{
    const std::map<std::string, int> numbers {
        { "one", 1 }, { "two", 2 }, { "three", 3 }
    };

    // print address
    for (auto mit = numbers.cbegin(); mit != numbers.cend(); ++mit) {
        std::cout << &mit->first << ", " << &mit->second << std::endl;
    }

    // each time entry is copied form pair<const stirng, int>
    std::for_each(std::begin(numbers), std::end(numbers),
            [](const std::pair<std::string, int>& entry) {
                std::cout << &entry.first << ", " << &entry.second << ": "
                          << entry.first << " = " << entry.second << std::endl;
            });

    // this time entries are not copied, they have the same address
    std::for_each(std::begin(numbers), std::end(numbers),
            [](const auto& entry) {
                std::cout << &entry.first << ", " << &entry.second << ": "
                          << entry.first << " = " << entry.second << std::endl;
            });
    return 0;
}

