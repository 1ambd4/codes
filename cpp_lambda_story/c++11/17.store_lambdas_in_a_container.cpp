#include <iostream>
#include <vector>
#include <functional>

int main()
{
    // 把lambda存放到数组里（一系列连贯的操作
    using func = void (* )(int& );
    std::vector<func> pfunc;
    pfunc.push_back([](int& x) {
            std::cout << x << std::endl;
            });
    pfunc.push_back([](int& x) {
            x *= 2;
            });
    pfunc.push_back(pfunc[0]);

    int x = 10;
    for (const auto& entry : pfunc) {
        entry(x);
    }

    // 缺点是只有无状态（捕获列表为空）的lambda可以这么写
    //
    // 可以使用用途更广但开销略大的std::function

    int removed_space_counter = 0;
    std::vector<std::function<std::string(const std::string& )>> funcvec;
    const auto remove_space = [&removed_space_counter](const std::string& str) {
        std::string tmp;
        std::copy_if(str.begin(), str.end(), std::back_inserter(tmp),
                [](char ch){ return !isspace(ch); });
        removed_space_counter += str.length() - tmp.length();
        return tmp;
    };

    const auto make_upper_case = [](const std::string& str) {
        std::string tmp = str;
        std::transform(tmp.begin(), tmp.end(), tmp.begin(),
                [](unsigned char c) { return std::toupper(c); });
        return tmp;
    };

    funcvec.emplace_back(remove_space);
    funcvec.emplace_back([](const std::string& x) {
            return x + " Amazing";
        });
    funcvec.emplace_back([](const std::string& x) {
            return x + " Modern";
        });
    funcvec.emplace_back([](const std::string& x) {
            return x + " C++";
        });
    funcvec.emplace_back([](const std::string& x) {
            return x + " World!";
        });
    funcvec.emplace_back(make_upper_case);

    const std::string str = " H e l l o     ";
    auto temp = str;
    for (const auto& entry: funcvec) {
        temp = entry(temp);
    }
    std::cout << temp << std::endl;
    std::cout << "removed space: " << removed_space_counter << std::endl;
    return 0;
}
