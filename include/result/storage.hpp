/*
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 */
#ifndef MARKLAR_RESULT_STORAGE_HPP
#define MARKLAR_RESULT_STORAGE_HPP

// Marklar headers
// External library headers
// C++ standard library headers
#include <type_traits>
#include <variant>

namespace marklar::result::tag
{
struct Value
{
};
struct Error
{
};

} // namespace marklar::result::tag

namespace marklar::result
{
template<typename StoredType, typename Tag>
class Storage {
public:
    Storage() = delete;

    explicit constexpr Storage(StoredType const & value)
        : value_{value}
    {
    }

    template<typename Type = StoredType, typename = std::enable_if_t<!std::is_reference<Type>::value>>
    explicit constexpr Storage(Type && value)
        : value_{std::forward<Type>(value)}
    {
    }

    [[nodiscard]] inline constexpr StoredType & get()
    {
        return value_;
    }

    [[nodiscard]] inline constexpr std::remove_reference_t<StoredType> const & get() const
    {
        return value_;
    }

    using ref = Storage<StoredType &, Tag>;
    [[nodiscard]] inline operator ref()
    {
        return ref(value_);
    }

private:
    StoredType value_;
};

template<typename Type>
using ValueStorage = Storage<Type, tag::Value>;

template<typename Type>
using ErrorStorage = Storage<Type, tag::Error>;

template<typename Type>
[[nodiscard]] inline constexpr ValueStorage<Type>
to_value(Type const & value)
{
    return ValueStorage<Type>{value};
}

template<typename Type, typename = std::enable_if_t<!std::is_reference_v<Type>>>
[[nodiscard]] inline constexpr ValueStorage<Type>
to_value(Type && value)
{
    return ValueStorage<Type>{std::forward<Type>(value)};
}

template<typename Type>
[[nodiscard]] inline constexpr ErrorStorage<Type>
to_error(Type const & value)
{
    return ErrorStorage<Type>{value};
}

template<typename Type, typename = std::enable_if_t<!std::is_reference_v<Type>>>
[[nodiscard]] inline constexpr ErrorStorage<Type>
to_error(Type && value)
{
    return ErrorStorage<Type>{std::forward<Type>(value)};
}

} // namespace marklar::result

#endif // MARKLAR_RESULT_STORAGE_HPP
