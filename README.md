# Result
Result - Simple monad solution based on C++17 and policy based design

```cpp

    #include "result/result.hpp"

    #include <iostream>

    using marklar::result::Result;

    constexpr int forty_and_two{42};
    static std::string const error_string{"Bad wolf"};

    Result<int, std::string> answer(int answer)
    {
        return forty_and_two == answare ? {answare} : {error_string};
    }

    int main()
    {
        auto ok_answer = answer(forty_and_two);
        if(ok_answer)
        {
            std::cout << ok_answer.value() << '\n';
        }

        return 0;
    }

```
