#include <policy/result/monad.hpp>

// Marklar headers
#include <policy/result/monad.hpp>
#include <result/result.hpp>
// External library headers
#include "../../catch.hpp"
// C++ standard library headers
#include <string>

constexpr int forty_and_two{42};
constexpr float pi{3.1415};
static std::string const error_string{"Bad wolf"};

TEST_CASE("marklar::result::policy::monad::value_map should be call the given function if its holds value")
{
    using namespace marklar::result;

    Result<int, std::string, policy::Monad> result{forty_and_two};

    CHECK(forty_and_two == result.value());
    auto result_map = result.value_map([](int value){ return forty_and_two * value; });

    REQUIRE(forty_and_two * forty_and_two == result_map.value());
}

TEST_CASE("marklar::result::policy::monad::value_map shouldn't be call the given function if its holds error")
{
    using namespace marklar::result;

    Result<int, std::string, policy::Monad> result{error_string};

    CHECK(error_string == result.error());
    auto result_map = result.value_map([](int value){ return forty_and_two * value; });

    REQUIRE(error_string == result_map.error());
}

TEST_CASE("marklar::result::policy::monad::join should be return with the stored value if the types are compatible")
{
    using namespace marklar::result;

    Result<int, float, policy::Monad> result_ok{forty_and_two};
    REQUIRE(forty_and_two == result_ok.join());

    Result<int, float, policy::Monad> result_error{pi};
    REQUIRE(pi == result_error.join());
}
