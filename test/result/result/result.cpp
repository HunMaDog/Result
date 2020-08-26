#include "result/result.hpp"

// Marklar headers
// External library headers
#include "../catch.hpp"
// C++ standard library headers
#include <string>

constexpr int forty_and_two{42};
static std::string const error_string{"Bad wolf"};

TEST_CASE("marklar::result::Result should be create from storaged type if both side has different type")
{
    using namespace marklar::result;

    Result<int, std::string> result_error{error_string};
    REQUIRE(error_string == result_error.error()); // Should be true because it holds a value
}

TEST_CASE("marklar::result::Result { to_value } should be create using value helper function")
{
    using namespace marklar::result;

    Result<int, int> result{to_value(forty_and_two)};
    REQUIRE(result.operator bool()); // Should be true because it holds a value
}

TEST_CASE("marklar::result::Result.value() should be return with value if it is holds a value")
{
    using namespace marklar::result;

    Result<int, std::string> result{to_value(forty_and_two)};
    REQUIRE(forty_and_two == result.value()); // Should be return with setted value
}

TEST_CASE("marklar::result::Result.error() should be return with error if it is holds an error")
{
    using namespace marklar::result;

    Result<int, std::string> result{to_error(error_string)};
    REQUIRE(error_string == result.error()); // Should be return with setted error
}

TEST_CASE("marklar::result::Result.value() should be throw exception if it is not holds a value")
{
    using namespace marklar::result;

    Result<int, std::string> result{to_error(error_string)};
    REQUIRE_THROWS(result.value()); // Should be return with setted value
}

TEST_CASE("marklar::result::Result.error() should be throw exception if it is holds an error")
{
    using namespace marklar::result;

    Result<int, std::string> result{to_value(forty_and_two)};
    REQUIRE_THROWS(result.error()); // Should be return with setted error
}
