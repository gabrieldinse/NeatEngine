#pragma once

#include "Components/Components.hpp"

#include <rfl.hpp>

namespace rfl {
template <Neat::UInt32 M, Neat::UInt32 N, typename T>
struct Reflector<Neat::Matrix<M, N, T>> {
  struct ReflType {
    std::array<T, M * N> elements;
  };

  static Neat::Matrix<M, N, T> to(const ReflType &reflMatrix) noexcept {
    return Neat::Matrix<M, N, T>{reflMatrix.elements};
  }

  static ReflType from(const Neat::Matrix<M, N, T> &matrix) {
    return {matrix.elements};
  }
};

template <Neat::UInt32 N, typename T>
struct Reflector<Neat::Vector<N, T>> {
  struct ReflType {
    std::array<T, N> elements;
  };

  static Neat::Vector<N, T> to(const ReflType &reflVector) noexcept {
    return Neat::Vector<N, T>{reflVector.elements};
  }

  static ReflType from(const Neat::Vector<N, T> &vector) {
    return {vector.elements};
  }
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

template <>
struct Reflector<Neat::RenderableSpriteComponent> {
  struct ReflType {
    std::string textureFilepath;
    Neat::Vector4F color;
    float tilingFactor;
  };

  static Neat::RenderableSpriteComponent to(
      const ReflType &reflSprite) noexcept {
    if (reflSprite.textureFilepath.empty()) {
      return Neat::RenderableSpriteComponent{reflSprite.color};
    }
    auto texture = Neat::Texture2D::create(reflSprite.textureFilepath);
    return Neat::RenderableSpriteComponent{texture, reflSprite.color,
                                           reflSprite.tilingFactor};
  }

  static ReflType from(const Neat::RenderableSpriteComponent &sprite) {
    return {sprite.getTextureFilepath(), sprite.color, sprite.tilingFactor};
  }
};

template <>
struct Reflector<Neat::CameraComponent> {
  struct ReflType {
    Neat::CameraType type;
    Neat::OrthographicProperties orthographicProperties;
    Neat::PerspectiveProperties perspectiveProperties;
    Neat::Matrix4F projectionMatrix;
  };

  static Neat::CameraComponent to(const ReflType &reflCamera) noexcept {
    switch (reflCamera.type) {
      case Neat::CameraType::Orthographic:
        return Neat::CameraComponent{reflCamera.orthographicProperties};
        break;
      case Neat::CameraType::Perspective:
        return Neat::CameraComponent{reflCamera.perspectiveProperties};
        break;
    }

    return Neat::CameraComponent{};
  }

  static ReflType from(const Neat::CameraComponent &camera) {
    return {camera.getType(), camera.getOrthographicProperties(),
            camera.getPerspectiveProperties(), camera.getProjection()};
  }
};

template <>
struct Reflector<Neat::OrthographicProperties> {
  struct ReflType {
    float left;
    float right;
    float bottom;
    float top;
    float near;
    float far;
  };

  static Neat::OrthographicProperties to(
      const ReflType &reflOrthographic) noexcept {
    return Neat::OrthographicProperties{
        reflOrthographic.left, reflOrthographic.right, reflOrthographic.bottom,
        reflOrthographic.top,  reflOrthographic.near,  reflOrthographic.far};
  }

  static ReflType from(const Neat::OrthographicProperties &orthographic) {
    return {orthographic.left, orthographic.right, orthographic.bottom,
            orthographic.top,  orthographic.near,  orthographic.far};
  }
};

template <>
struct Reflector<Neat::PerspectiveProperties> {
  struct ReflType {
    float fov;
    float aspectRatio;
    float near;
    float far;
  };

  static Neat::PerspectiveProperties to(
      const ReflType &reflPerspective) noexcept {
    return Neat::PerspectiveProperties{
        reflPerspective.fov, reflPerspective.aspectRatio, reflPerspective.near,
        reflPerspective.far};
  }

  static ReflType from(const Neat::PerspectiveProperties &perspective) {
    return {perspective.fov, perspective.aspectRatio, perspective.near,
            perspective.far};
  }
};
}  // namespace rfl