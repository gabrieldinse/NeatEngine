#pragma once

#include "Neat/Components/Components.hpp"

#include <rfl.hpp>

namespace rfl {
template <Neat::UInt32 N, typename T>
struct Reflector<Neat::Vector<N, T>> {
  struct ReflType {
    std::array<T, N> elements;
  };

  static Neat::Vector<N, T> to(const ReflType &rv) noexcept {
    return Neat::Vector<N, T>{rv.elements};
  }

  static ReflType from(const Neat::Vector<N, T> &v) { return {v.elements}; }
};

template <>
struct Reflector<Neat::TransformComponent> {
  struct ReflType {
    Neat::Vector3F position;
    Neat::Vector3F scaling;
    Neat::Vector3F rotation;
  };

  static Neat::TransformComponent to(const ReflType &reflTransform) noexcept {
    return Neat::TransformComponent{
        reflTransform.position, reflTransform.scaling, reflTransform.rotation};
  }

  static ReflType from(const Neat::TransformComponent &transform) {
    return {transform.position, transform.scaling, transform.rotation};
  }
};
}  // namespace rfl