/*
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 */
#ifndef MARKLAR_RESULT_RESULT_HPP
#define MARKLAR_RESULT_RESULT_HPP

// Marklar headers
#include "detail/polyh/crtp_macro.hpp"
#include "storage.hpp"
// External library headers
// C++ standard library headers
#include <type_traits>
#include <variant>

namespace marklar::result
{
template<typename ValueType, typename ErrorType, template<typename...> class... Functionality>
class Result : public Functionality<Result<ValueType, ErrorType, Functionality...>>... {
    CRTP_VARIADIC_FRIEND(Functionality, Functionality<Result>)

public:
    using Value = ValueStorage<ValueType>;
    using Error = ErrorStorage<ErrorType>;
    using UnderlyingData = std::variant<std::monostate, Value, Error>;

    Result() = delete;

    explicit constexpr Result(Result const & other)
        : data_{other.data_}
    {
    }

    explicit constexpr Result(Result && other)
        : data_{std::forward<UnderlyingData>(other.data_)}
    {
    }

    explicit constexpr Result(Value value)
        : data_{std::forward<Value>(value)}
    {
    }

    explicit constexpr Result(Error error)
        : data_{std::forward<Error>(error)}
    {
    }

    explicit constexpr Result(ValueType value, tag::Value = {})
        : data_{to_value(std::forward<ValueType>(value))}
    {
    }

    explicit constexpr Result(ErrorType error, tag::Error = {})
        : data_{to_error(std::forward<ErrorType>(error))}
    {
    }

    constexpr std::remove_reference_t<ValueType> const & value() const
    {
        return std::get<Value>(data_).get();
    }

    constexpr std::remove_reference_t<ErrorType> const & error() const
    {
        return std::get<Error>(data_).get();
    }

    inline constexpr operator bool() const noexcept
    {
        return std::holds_alternative<Value>(data_);
    }

protected:
    ValueType & modify_value()
    {
        return std::get<Value>(data_).get();
    }

    ErrorType & modify_error()
    {
        return std::get<Error>(data_).get();
    }

private:
    UnderlyingData data_;
};

} // namespace marklar::result

#endif // MARKLAR_RESULT_RESULT_HPP
