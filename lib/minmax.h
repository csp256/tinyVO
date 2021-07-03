// min() and max(). Accepts any number of arguments.

template<typename T>
inline T&& min(T&& val)
{
    return std::forward<T>(val);
}

template<typename T0, typename T1, typename... Ts>
inline auto min(T0&& val1, T1&& val2, Ts&&... vs)
{
    return (val1 < val2) ?
      min(val1, std::forward<Ts>(vs)...) :
      min(val2, std::forward<Ts>(vs)...);
}

template<typename T>
inline T&& max(T&& val)
{
    return std::forward<T>(val);
}

template<typename T0, typename T1, typename... Ts>
inline auto max(T0&& val1, T1&& val2, Ts&&... vs)
{
    return (val2 < val1) ?
      max(val1, std::forward<Ts>(vs)...) :
      max(val2, std::forward<Ts>(vs)...);
}