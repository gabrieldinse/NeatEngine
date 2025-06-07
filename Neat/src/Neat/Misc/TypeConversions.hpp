
namespace Neat {
template <typename E>
constexpr typename std::enable_if<std::is_enum<E>::value,
                                  std::underlying_type_t<E>>::type
enumToInt(E e) {
  return static_cast<std::underlying_type_t<E>>(e);
}
}  // namespace Neat