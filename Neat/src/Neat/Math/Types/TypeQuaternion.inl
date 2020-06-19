#include "Neat/Math/Trigonometric.h"
#include "Neat/Math/Types/TypeMatrixMxN.h"
#include "TypeQuaternion.h"


namespace Neat
{
   // Default constructor
   template <typename T>
   inline constexpr Quaternion<T>::Quaternion()
      : w(zero<T>), x(zero<T>), y(zero<T>), z(zero<T>) {}


   // Basic constructors
   template <typename T>
   inline constexpr Quaternion<T>::Quaternion(T s, const Vector<3, T>& v)
      : s(s), v(v) {}

   template <typename T>
   inline constexpr Quaternion<T>::Quaternion(T w, T x, T y, T z)
      : w(w), x(x), y(y), z(z) {}


   // Copy Constructor
   template <typename T>
   inline constexpr Quaternion<T>::Quaternion(const Quaternion<T>& q)
      : w(q.w), x(q.x), y(q.y), z(q.z) {}

   // Conversion constructors
   template <typename T>
   template <typename U>
   inline constexpr Quaternion<T>::Quaternion(const Quaternion<U>& q)
      : w(static_cast<T>(q.w))
      , x(static_cast<T>(q.x))
      , y(static_cast<T>(q.y))
      , z(static_cast<T>(q.z)) {}

   // Euler angles constructors
   template<typename T>
   inline constexpr Quaternion<T>::Quaternion(Vector<3, T> const& eulerAngles)
   {
      vec<3, T, Q> c = cos(eulerAngles * T(0.5));
      vec<3, T, Q> s = sin(eulerAngles * T(0.5));

      w = c.x * c.y * c.z + s.x * s.y * s.z;
      x = s.x * c.y * c.z - c.x * s.y * s.z;
      y = c.x * s.y * c.z + s.x * c.y * s.z;
      z = c.x * c.y * s.z - s.x * s.y * c.z;
   }

   template<typename T>
   inline constexpr Quaternion<T>::Quaternion(Matrix<3, 3, T> const& rotation)
   {
   }

   template<typename T>
   inline constexpr Quaternion<T>::Quaternion(Matrix<4, 4, T> const& rotation)
   {
   }


   // Assignment operators
   template<typename T>
   template<typename U>
   inline constexpr Quaternion<T>& Quaternion<T>::operator=(
      const Quaternion<U>& q)
   {
      w = static_cast<T>(q.w);
      x = static_cast<T>(q.x);
      y = static_cast<T>(q.y);
      z = static_cast<T>(q.z);

      return *this;
   }


   // Compound assignment operators
   template<typename T>
   template<typename U>
   inline constexpr Quaternion<T>& Quaternion<T>::operator+=(
      const Quaternion<U>& q)
   {
      w += static_cast<T>(q.w);
      x += static_cast<T>(q.x);
      y += static_cast<T>(q.y);
      z += static_cast<T>(q.z);

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Quaternion<T>& Quaternion<T>::operator-=(
      const Quaternion<U>& q)
   {
      w -= static_cast<T>(q.w);
      x -= static_cast<T>(q.x);
      y -= static_cast<T>(q.y);
      z -= static_cast<T>(q.z);

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Quaternion<T>& Quaternion<T>::operator*=(
      const Quaternion<U>& q)
   {
      w = w * q.w - x * q.x - y * q.y - z * q.z;
      x = w * q.x + x * q.w + y * q.z - z * q.y;
      y = w * q.y + y * q.w + z * q.x - x * q.z;
      z = w * q.z + z * q.w + x * q.y - y * q.x;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Quaternion<T>& Quaternion<T>::operator*=(U scalar)
   {
      w *= static_cast<T>(scalar);
      x *= static_cast<T>(scalar);
      y *= static_cast<T>(scalar);
      z *= static_cast<T>(scalar);

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Quaternion<T>& Quaternion<T>::operator/=(U scalar)
   {
      w /= static_cast<T>(scalar);
      x /= static_cast<T>(scalar);
      y /= static_cast<T>(scalar);
      z /= static_cast<T>(scalar);

      return *this;
   }

   // Explicit conversion operators
   template <typename T>
   inline Quaternion<T>::operator Matrix<3, 3, T>() const
   {
      // TODO
      return Matrix<3, 3, T>();
   }

   template <typename T>
   inline Quaternion<T>::operator Matrix<4, 4, T>() const
   {
      // TODO
      return Matrix<4, 4, T>();
   }


   // Elements accessing
   template <typename T>
   inline constexpr T& Quaternion<T>::operator[](UInt32 pos)
   {
      if (pos >= 3)
         throw QuaternionDimensionError();

      return (&w)[pos];
   }

   template <typename T>
   inline constexpr const T& Quaternion<T>::operator[](UInt32 pos) const
   {
      if (pos >= 3)
         throw QuaternionDimensionError();

      return (&w)[pos];
   }


   // Non member operators
   template<typename T>
   constexpr Quaternion<T> operator+(const Quaternion<T>& qa,
      const Quaternion<T>& qb)
   {
      return Quaternion<T>(qa) += qb;
   }

   template<typename T>
   constexpr Quaternion<T> operator-(const Quaternion<T>& q)
   {
      return Quaternion<T>(-q.w, -q.x, -q.y, -q.z);
   }

   template<typename T>
   constexpr Quaternion<T> operator-(const Quaternion<T>& qa,
      const Quaternion<T>& qb)
   {
      return Quaternion<T>(qa) -= qb;
   }

   template<typename T>
   constexpr Quaternion<T> operator*(const Quaternion<T>& qa,
      const Quaternion<T>& qb)
   {
      return Quaternion<T>(qa) *= qb;
   }

   template<typename T>
   constexpr Vector<3, T> operator*(const Quaternion<T>& q,
      const Vector<3, T>& v)
   {
      return Vector<3, T>();
   }

   template<typename T>
   constexpr Vector<3, T> operator*(const Vector<3, T>& v,
      const Quaternion<T>& q)
   {
      return Vector<3, T>();
   }

   template<typename T>
   constexpr Vector<4, T> operator*(const Quaternion<T>& q,
      const Vector<4, T>& v)
   {
      return Vector<4, T>();
   }

   template<typename T>
   constexpr Vector<4, T> operator*(const Vector<4, T>& v,
      const Quaternion<T>& q)
   {
      return Vector<4, T>();
   }

   template<typename T>
   constexpr Quaternion<T> operator*(const Quaternion<T>& q, T const& scalar)
   {
      return Quaternion<T>(q) *= scalar;
   }

   template<typename T>
   constexpr Quaternion<T> operator*(T const& scalar, const Quaternion<T>& q)
   {
      return Quaternion<T>(q) *= scalar;
   }

   template<typename T>
   constexpr Quaternion<T> operator/(const Quaternion<T>& q, T const& scalar)
   {
      return Quaternion<T>(q) /= scalar;
   }

   
   // Relational operators
   template<typename T>
   constexpr bool operator==(const Quaternion<T>& qa, const Quaternion<T>& qb)
   {
      return qa.x == qb.x && qa.y == qb.y && qa.z == qb.z && qa.w == qb.w;
   }

   template<typename T>
   constexpr bool operator!=(const Quaternion<T>& qa, const Quaternion<T>& qb)
   {
      return !(qa == qb);
   }


   // Quaternion operations
   template<typename T>
   constexpr T dot(const Quaternion<T>& qa, const Quaternion<T>& qb)
   {
      return qa.w * qb.w + qa.x * qb.x + qa.y + qb.y + qa.z * qb.z;
   }

   template<typename T>
   constexpr T norm(const Quaternion<T>& q)
   {  
      return sqrt(dot(q, q));
   }

   template<typename T>
   constexpr Quaternion<T> normalize(const Quaternion<T>& q)
   {
      T one_over_norm = one<T> / norm(q);
      return q * one_over_norm;
   }

   template<typename T>
   constexpr Quaternion<T> conjugate(const Quaternion<T>& q)
   {
      return Quaternion<T>(q.w, -q.x, -q.y, -q.z);
   }

   template<typename T>
   constexpr Quaternion<T> inverse(const Quaternion<T>& q)
   {
      return conjugate(q) / norm(q);
   }
}