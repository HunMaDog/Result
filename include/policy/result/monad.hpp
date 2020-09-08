/*
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 */
#ifndef MARKLAR_RESULT_POLICY_FUNCIONALITY_MONAD_HPP
#define MARKLAR_RESULT_POLICY_FUNCIONALITY_MONAD_HPP

// Marklar headers
#include <detail/polyh/crtp_macro.hpp>
#include <detail/polyh/virtual_base.hpp>
#include <result/storage.hpp>
// External library headers
// C++ standard library headers

// Need to move to free function
namespace marklar::result::policy
{
template<typename Result>
struct Monad : detail::polyh::VirtualBase<Result, Monad>
{
    template<typename Function>
    [[nodiscard]] inline constexpr auto value_map(Function && function)
    {
        return CRTP_UNDERLYING.operator bool() ? Result{to_value(function(CRTP_UNDERLYING.value()))} : Result{CRTP_UNDERLYING};
    }

    template<typename Function>
    [[nodiscard]] inline constexpr auto error_map(Function && function)
    {
        return CRTP_UNDERLYING.operator bool() ? Result{CRTP_UNDERLYING} : Result{to_error(function(CRTP_UNDERLYING.error()))};
    }

    [[nodiscard]] inline constexpr auto join() const noexcept
    {
        return CRTP_UNDERLYING.operator bool() ? CRTP_UNDERLYING.value() : CRTP_UNDERLYING.error();
    }
};
} // namespace marklar::result::policy

#endif // MARKLAR_RESULT_POLICY_FUNCIONALITY_MONAD_HPP
