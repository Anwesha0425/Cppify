# C++ Shortcuts and Tricks for Competitive Programming

This document summarizes the very useful shortcuts and topics from the Codeforces blog post [C++ Tricks](https://codeforces.com/blog/entry/15643).

## 1. Container Initialization with Initializer Lists `{}`
Instead of using `make_pair` or multiple `push_back`s, you can initialize containers using `{}`:
```cpp
pair<int, int> p = {3, 4};
vector<int> v = {4, 5, 2};
set<int> s = {4, 6, 2, 7, 4};
deque<vector<pair<int, int>>> d = {{{3, 4}, {5, 6}}, {{1, 2}, {3, 4}}};
tuple<int, int, char> t = {3, 4, 'f'};
```

## 2. Stringification in Macros (`#`)
You can use the `#` sign to get the exact name of an argument passed to a macro:
```cpp
#define what_is(x) cerr << #x << " is " << x << endl;

int a_variable = 376;
what_is(a_variable); // prints "a_variable is 376"
```

## 3. The Master Header File
Instead of including many different headers, you can include this one which contains almost all standard libraries:
```cpp
#include <bits/stdc++.h>
```

## 4. Useful Built-in Functions
- `__gcd(a, b)`: Returns the greatest common divisor of `a` and `b`.
- `__builtin_ffs(x)`: Returns 1 + the index of the least significant 1-bit of `x`.
- `__builtin_clz(x)`: Returns the number of leading 0-bits of `x`.
- `__builtin_ctz(x)`: Returns the number of trailing 0-bits of `x`.
- `__builtin_popcount(x)`: Returns the number of 1-bits (set bits) of `x`.
*(Append `l` or `ll` for `long` and `long long` data types, e.g., `__builtin_popcountll`)*

## 5. Variadic Functions and Macros
Use variadic templates to accept any number of arguments of different types:
```cpp
int sum() { return 0; }
template<typename T, typename... Args>
auto sum(T a, Args... args) { return a + sum(args...); }

// Debugging macro:
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << endl;
	err(++it, args...);
}
```

## 6. Range-based For-loops
Iterate through containers elegantly:
```cpp
vector<int> v = {8, 2, 3, 1};
for (auto it: v) cout << it << ' '; // read-only
for (auto &it: v) it *= 2;          // modify by reference
```

## 7. The Power of `auto`
Let the compiler infer the type:
```cpp
auto it = s.begin();
// Much easier than set<pair<int, pair<int, int> > >::iterator it = s.begin();
```

## 8. `tie` and `emplace_back`
- **`emplace_back`** constructs the object in-place at the end of the container (faster than `push_back`).
- **`tie`** unpacks a tuple into variables. You can use `ignore` to skip values.
```cpp
int a, b, c;
tie(a, b, c) = make_tuple(1, 2, 3);
tie(a, b) = make_tuple(b, a); // swap(a, b)

tuple<int, int, int, char> t (3, 4, 5, 'g');
tie(b, ignore, a, ignore) = t;
```

## 9. Lambda Functions
Anonymous functions for short inline logic:
```cpp
auto f = [](int a, int b) -> int { return a + b; };
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
```

## 10. `move` Semantics
Avoid copying large containers by moving them:
```cpp
vector<int> v = {1, 2, 3, 4};
vector<int> w = move(v); // 'v' is now empty, 'w' has the elements
```

## 11. Raw Strings
Define strings that preserve all whitespace and ignore escape characters:
```cpp
string r_str = R"(Hello\tWorld\n)"; // Stores literal backslashes and 't'/'n'
string multi_line = R"(First line
Second line)";
```

## 12. Regular Expressions (regex)
C++11 includes built-in regular expression support:
```cpp
regex email_pattern(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
bool is_valid = regex_match("[email protected]", email_pattern);
```

## 13. User-defined Literals
Define custom suffixes for literal values:
```cpp
long long operator "" _km(unsigned long long literal) {
	return literal * 1000;
}
cout << 12_km << " meters \n"; // Prints 12000 meters
```
