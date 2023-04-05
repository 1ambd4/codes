#include <iostream>
#include <vector>

using namespace std;

#define LOG(x) \
    cout << __func__ << " " << __LINE__ << ": " << x << endl;


// Chapter 1
// A Crash Course in C++ and the Standard Library


#include <cmath>
#include <limits>
void func1()
{
    cout << (1<<12) << endl;
    // cout << std::format("There are {} ways I love you.", 233) << endl;
    cout << numeric_limits<int>::max() << endl;
    cout << numeric_limits<int>::min() << endl;

    cout << numeric_limits<bool>::max() << endl;
    cout << numeric_limits<bool>::min() << endl;

    cout << numeric_limits<double>::max() << endl;
    cout << numeric_limits<double>::min() << endl;

    float myFloat {};
    cout << myFloat << endl;

    // isinf() isnan()
    // NaN: Not a Number
    cout << std::isinf(numeric_limits<double>::infinity()) << endl;

    enum class piece_type : unsigned int
    {
        king = 1,
        queen,
        rook = 10,
        pawn
    };
    cout << static_cast<int>(piece_type::pawn) << endl;
    // error: no match for 'operator!=' (operand types are 'main()::piece_type' and 'int')
    // if (piece_type::king != 2) {
    //     cout << "not equal" << endl;
    // }

    // Every function has a local perdifined variable __func__
    // which containing the name of current function.
    cout << __func__ << endl;
}


// Since C++11, there is a standardlizd support for attributes.
//
// The [[nodiscard]] attribute can be used on a function returning a value
// to let the compiler issue a warning when that function is called
// without doing something with the retured value.
[[nodiscard]] int func2()
// Starting with C++20, a reason can be provied for the [[nodiscard]] attribute.
// [[nodiscard("Test [[nodiscard]] attribute")]] int func2()
{
    return 233;
}
// The [[maybe_unused]] attribute can be used on a function
// which own something maybe unused without compiler warning.
void func3([[maybe_unused]]int a, int b)
{
    // variable a and b not be used.
}
// The [[noreturn]] attribute can be used on a function
// which never returns control to the call site.
// Typically, the function either causes some kind of termination
// or throws an exception.
[[noreturn]]void func4()
// void func4()
// Without [[noreturn]] attribute compile will raise a warning like
// control reaches end of non-void function
{
    std::exit(1);
}
bool func5(bool check)
{
    if (check) {
        func4();
    } else {
        return true;
    }
}
// The [[likely]] and [[unlikely]] attribute can be used to help compiler
// in optimizing code about branch predication.
void func6()
{
    if (true) [[likely]] {
        cout << "True" << endl;
    } else [[unlikely]] {
        cout << "False" << endl;
    }
}

void attribute_test()
{
    // func2();
    // func3(1, 2);
    func5(false);
    func6();
}


// The arrays is a thin wrapper around C-style arrays
// which is a type of fixed-size contailer.
#include <array>
void array_test()
{
    std::array<int, 3> arr { 1, 2, 3 };
    cout << "size = " << arr.size() << ", arr[0] = " << arr[0] << endl;

    // CATD: class template argument deduction
    // Allow you to difine container without specific the calss template argument.
    std::array arr2 { 1, 3, 5, 7 };
}


// The C++ Standard Library also provides a non-fixed-size contains named vector.
#include <vector>
void vector_test()
{
    std::vector<int> vec { 1, 2, 3 };
    cout << "size = " << vec.size() << ", vec[0] = " << vec[0] << endl;
    vec.push_back(6);
    vec.push_back(9);
    cout << "size = " << vec.size() << ", vec[0] = " << vec[0] << endl;
}

// The std::pair class groups together two values.
#include <utility>
void pair_test()
{
    std::pair<int, int> pii { 1, 2 };
    cout << "first = " << pii.first << ", second = " << pii.second << endl;
}


// The std::optional is a template class which holds a value of specific type, or nothing
// If used as return type then can both return something or nothing.
#include <optional>
optional<int> get_data(bool check)
{
    if (check) {
        return 42;
    } else {
        return {};
    }
}
void optional_test()
{
    optional<int> data { get_data(false) };
    if (data.has_value()) {
    // Also can be write like
    // if (data) {
        cout << "Has value " << data.value() << endl;
        // cout << "Has value " << *data << endl;
    } else {
        cout << "Not have value" << endl;
    }

    // value_or() can be used to return either the value of an optional
    // or another value when the optional is empty;
    cout << "The value of data is " << data.value_or(233) << endl;
}


// Structured Bindings
// Structured bindings allow to declare multiple variables
// that are initialized with elements from.
void structed_binding_func()
{
    array arr { 11, 22, 33 };
    auto [x, y, z] { arr };
    cout << x << " " << y << " " << z << endl;

    // The common place use Structured Bindings perhaps was in decomposing pair.
    pair<int, int> pii { 4, 2 };
    auto [m, n] { pii };
    cout << m << " " << n << endl;
}


// Initializers for Range-Based for Loops, but seems useless?
void initializers_for_ranged_based_test()
{
    for (array arr { 1, 2, 3, 4, 5 }; int i : arr) {
        cout << i << " ";
    }
    cout << endl;
}


// Initializer Lists: allow a variable number of arguments.
// like non-fixed length parameter?
#include <initializer_list>
int make_sum(initializer_list<int> values)
{
    int total { 0 };
    for (int value : values) {
        total += value;
    }
    return total;
}
void initializer_list_test()
{
    cout << make_sum({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) << endl;
}

// There are two way to work with string in C++:
//   1、The C Style: Representing strings as arrays of characters.
//   2、The C++ style: wrapping a C-style representation in an easier-to-use and
//   safer string type.


// Uniform Initialization, C++11
struct circles_struct
{
    int x, y;
    double radius;
};
class circles_class
{
public:
    int x, y;
    double radius;
};

void uniform_initialization_test()
{
    circles_struct circle1 = { 1, 2, 3.5 };
    // In pre-C++11, should use function notation (...) to call constructor
    // not uniform with usage of struct
    // circles_class circle2 (1, 2, 2.5);

    // Since C++11, can more uniformly use the {...} syntax to initialize types
    circles_class circle2 = { 1, 2, 2.5 };

    // And, the use of the equal sign is optional
    // so, the following are identical
    circles_struct circle3 { 1, 2, 3.5 };
    circles_class circle4 {1, 2, 3.5};

    // Also, uniform initialization can be used to
    // perform zero-initialization of variable
    // just specify an empy set of curly braces.
    circles_class circle { };
    cout << circle.x << " " << circle.y << " " << circle.radius << endl;

    // A benefit of using uniform initialization is that
    // it pervents narrowing
    int x = 3.14;       // Not even a warning
    // int y { 3.14 };  // error: narrowing conversion 
    auto func = [](int v) {
        cout << v << endl;
    };
    // func({3.14});    // error: narrowing conversion
    func(3.14);         // OK
}

void dynamically_allocated_arrays_test()
{
    // The pointer variable reside on the stack,
    // while the array that was dynamically created on the free store.
    int array_size { 8 };
    int *parr { new int[array_size] };

    delete[] parr;
    parr = nullptr;
}

const int get_array_size()
{
    return 37;
}

// Declaring a function as constexpr impose a lot of restrictions on
// what the function can do.
// Such as a funciton is not allowed to have any side effects.
constexpr int get_array_size_constexpr()
{
    return 42;
}

class Rect
{
public:
    // By defining a constexpr constructor, can create constant-expression variables
    // of user-defined types.
    constexpr Rect(size_t width, size_t height)
        : m_width { width }, m_height { height } { }

    constexpr size_t get_area() const { return m_width * m_height; };

private:
    size_t m_width { 0 }, m_height { 0 };
};

void constexpr_test()
{
    // PROCPP 5th said that the followin piece of code is not valid in C++,
    // but, practically, can be compiled successfully.
    // int arr[get_array_size()];
    int arr[get_array_size_constexpr()];
    // Since using keyward constexpr is a better choise.
    // The constexpr keyword specifies that a function could be executed at compile time,
    // but it does not gurrantee compile-tiem execution.
    arr[1] = 233;
    cout << arr[1] << endl;

    constexpr Rect r { 4, 2 };
    int arr1[r.get_area()];
}


void reference_test()
{
    // Reference to pointer
    // Looks a little strange, but the semantics are straightforward,
    // ref2ptr is a reference to pointer.
    int *ptr { nullptr };
    int *& ref2ptr { ptr };
    ref2ptr = new int;
    *ref2ptr = 42;
    LOG(*ptr);

    // Pointer to reference just like pointer to common variable.
    // Note that you cannot declare a reference to a reference or a pinter to a reference.
    // That means, neithor int && nor int &* is allowed.
    int x { 58 };
    int &ref2x { x };
    int *ptr2ref { &ref2x };
    *ptr2ref = 42;
    LOG(x);
}


// Deciding between reference and pointers
// Note: Prefer reference over pointer; that is
// use a pointer only if a reference is not possible.

// The C way, pass-by-pointer.  
void separate_odds_and_evens(const int arr[], size_t size,
        int **odds, size_t *odds_cnt, int **evens, size_t *evens_cnt)
{
    *odds_cnt = *evens_cnt = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            ++(*evens_cnt);
        } else {
            ++(*odds_cnt);
        }
    }

    *odds = new int[*odds_cnt];
    *evens = new int[*evens_cnt];

    for (size_t po = 0, pa = 0, i = 0; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            (*odds)[pa++] = arr[i];
        } else {
            (*evens)[po++] = arr[i];
        }
    }
}

// Use reference make code cleaner.
void separate_odds_and_evens(const int arr[], size_t size,
        int *&odds, size_t &odds_cnt, int *&evens, size_t &evens_cnt)
{
    odds = evens = 0;
    for (size_t i { 0 }; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            ++evens_cnt;
        } else {
            ++odds_cnt;
        }
    }

    odds = new int[odds_cnt];
    evens = new int[evens_cnt];

    for (size_t po { 0 }, pa { 0 }, i { 0 }; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            evens[pa++] = arr[i];
        } else {
            odds[po++] = arr[i];
        }
    }
}

// Even though using reference parameters is already much cleaner than using pointers,
// it is recommended that you avoid dynamically allocate arrays as much as possible.
#include <vector>
void separate_odds_and_evens(const vector<int>& arr,
        vector<int>& odds, vector<int>& evens)
{
    for (int num : arr) {
        if (num % 2 == 0) {
            evens.push_back(num);
        } else {
            odds.push_back(num);
        }
    }
}

// But, remember, it should just return it instead of using output parameters.
// Dont't warry about efficiency with RVO and NRVO.
// (RVO: return value optimization, NRVO: named return value optimization)
using pvii = pair<vector<int>, vector<int>>;
// struct vii { vector<int> odds, evens };
pvii separate_odds_and_evens(const vector<int>& arr)
{
    vector<int> odds, evens;
    for (int num : arr) {
        if (num % 2 == 0) {
            evens.push_back(num);
        } else {
            evens.push_back(num);
        }
    }

    return pvii { odds, evens };
    // return vii { .odds = odds, .evens = evens };  // C++20 designated initializers
}

void reference_and_pointer_test()
{
    int unsplit[] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int *odd_nums { nullptr };
    int *even_nums { nullptr };
    size_t odds_cnt { 0 }, evens_cnt { 0 };

    separate_odds_and_evens(unsplit, std::size(unsplit),
            &odd_nums, &odds_cnt, &even_nums, &evens_cnt);
    separate_odds_and_evens(unsplit, std::size(unsplit),
            odd_nums, odds_cnt, even_nums, evens_cnt);

    delete[] odd_nums;
    odd_nums = nullptr;
    delete[] even_nums;
    even_nums = nullptr;
}


double exception_test(double numerator, double denominator)
{
    if (denominator == 0) {
        throw invalid_argument { "Denominator cannot be 0."};
    } else {
        return numerator / denominator;
    }
}

void try_catch_test()
{
    try {
        LOG(exception_test(2, 5));
        LOG(exception_test(4, 0));
    } catch (const invalid_argument & exception) {
        LOG(exception.what());
    }
}


// Type aliases C++11
// The most common use for type is to provide manageable names
// when the real type declarations become too unwieldy.
// An example from the STL itself is std::basic_string<T> to represent string.
//   using string = basic_string<char>;
//
// Before C++11, use typedefs to accomplish some thing similar with type aliases.
//   typedef basic_string<char> string;
// Always prefer type alies over typedefs.


void type_deduce_test()
{
    // Noticed that auto stripe alway reference and const qualifiers
    // and thus creates a copy.

    // You want a pointer to const, and code like below,
    // but in fact, the type is const pointer.
    int val = 42;
    const auto pi1 { &val };
    *pi1 = 58;
    LOG(*pi1);
    auto const pi2 { &val };
    *pi2 = 42;
    LOG(*pi2);

    const auto* pi3 { &val };   // const int* pi3
    // *pi3 = 58;   // error    
    auto* const pi4 { &val };   // int* const pi4
    *pi4 = 42;
}

void list_initialization_test()
{
    // In combanation with auto type deduction, since C++17,
    // there is a important difference between copy and direct list initialization
    auto a = { 1 };             // copy list initialization
    LOG(typeid(a).name());      // deduce as initialization_list<int>
    auto b = { 1, 2 };          // copy list initialization
    LOG(typeid(b).name());      // deduce as initialization_list<int>

    auto c { 1 };               // direct list initialization
    LOG(typeid(c).name());      // deduce as int
    // auto d { 1, 2 };         // direct list initialization
    // LOG(typeid(d).name());   // error, too many elements
    
    // In earlier version of standard (C++11/14),
    // both copy and direct list initialization would deduce an initializers_list<>.
}


int main()
{
    // attribute_test();
    // array_test();
    // vector_test();
    // pair_test();
    optional_test();
    structed_binding_func();
    initializers_for_ranged_based_test();
    initializer_list_test();
    uniform_initialization_test();
    dynamically_allocated_arrays_test();
    constexpr_test();
    reference_test();
    try_catch_test();
    type_deduce_test();
    list_initialization_test();
    return 0;
}
