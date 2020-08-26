# Result
Result - Simple monad solution based on C++17 and policy based design

```cpp

    #include "result/result.hpp"

    #include <iostream>

    using Result = Result<int, std::string>;

    constexpr int forty_and_two{42};
    static std::string const error_string{"Bad wolf"};

    Result answer(int answer)
    {
        return forty_and_two == answer ? Result{answer} : Result{error_string};
    }

    int main()
    {
        auto ok_result = answer(forty_and_two);
        
        if(ok_result)
        {
            std::cout << ok_result.get() << '\n';
        }
    
        return 0;
    }

```
{}
