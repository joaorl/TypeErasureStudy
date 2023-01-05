# Any
A lightweight header-only library for type-erased values in C++.
The type-erased `Any` class allows for storing and manipulating values of any type, with the type of the value being known only at runtime. It includes methods for constructing an `Any` object, copying the value held by an  `Any` object, and retrieving the type and value of the object.

This library is a case of study and has the same purpose of std::any class introduced in C++17. 

## Dependencies
This library depends on the following libraries:

* `std`: the C++ standard library

## Build
To build follow the instructions below:
```
mkdir build
cd build
cmake ..
```

# Usage
To use the library, simply include the `Any.h` header file in your project.
```
#include "Any.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

int main()
{

    Any a = 1;
    Any b = string("hello");
    Any c = vector<int>{1, 2, 3};
    Any d = map<string, Any> { 
            {string("a"), 1}, 
            {string("b"), string("hello")} 
        };

    cout << a.Get<int>() << endl;
    cout << b.Get<string>() << endl;
    cout << c.Get<vector<int>>().size() << endl;

    for (auto& x : c.Get<vector<int>>())
    { 
        cout << x << " "; 
    } 
    cout << endl;

    for (auto& [key, value] : d.Get<map<string, Any>>())
    {
        try
        {
            auto v = value.Get<int>();
            cout << key << ": " << v << endl; 
        }
        catch (std::bad_cast& e)
        {
            auto v = value.Get<string>();
            cout << key << ": " << v << endl; 
        }
    }

    return 0;
}
````
## API

```
Any()
```
Constructs an empty Any object.


```
Any(const T& value)
```
Constructs an Any object that holds a copy of value.


```
Any(const Any& other)
```
Constructs an Any object that holds a copy of the value held by other.


```
Any& operator=(const Any& other)
```
Assigns the value held by other to the current Any object.


```
const std::type_info& Type() const
```
Returns the type of the value held by the Any object.


```
template <typename T> T& Get()
```
If the type of the value held by the Any object is the same as T, returns the value reference. Otherwise, returns generate an exception.
