#include "Neat/Math/Trigonometric.h"


namespace Neat
{
   // Default constructor
   template <typename T>
   inline constexpr Quat<T>::Quat()
      : w(one<T>), x(zero<T>), y(zero<T>), z(zero<T>) {}


   // Basic constructors
   template <typename T>
   inline constexpr Quat<T>::Quat(T s, const Vector<3, T>& v)
      : s(s), v(v) {}

   template <typename T>
   inline constexpr Quat<T>::Quat(T w, T x, T y, T z)
      : w(w), x(x), y(y), z(z) {}


   // Copy Constructor
   template <typename T>
   inline constexpr Quat<T>::Quat(const Quat<T>& q)
      : w(q.w), x(q.x), y(q.y), z(q.z) {}


   // Conversion constructors
   template <typename T>
   template <typename U>
   inline constexpr Quat<T>::Quat(const Quat<U>& q)
      : w(static_cast<T>(q.w))
      , x(static_cast<T>(q.x))
      , y(static_cast<T>(q.y))
      , z(static_cast<T>(q.z)) {}


   // Euler angles constructors
   template<typename T>
   inline constexpr Quat<T>::Quat(Vector<3, T> const& eulerAngles)
   {
      Vector<3, T> c = cos(eulerAngles * T(0.5));
      Vector<3, T> s = sin(eulerAngles * T(0.5));

      w = c.x * c.y * c.z + s.x * s.y * s.z;
      x = s.x * c.y * c.z - c.x * s.y * s.z;
      y = c.x * s.y * c.z + s.x * c.y * s.z;
      z = c.x * c.y * s.z - s.x * s.y * c.z;
   }

   template <typename T>
   inline constexpr Quat<T>::Quat(const Matrix<3, 3, T>& rotation)
   {
   }

   template <typename T>
   inline constexpr Quat<T>::Quat(const Matrix<4, 4, T>& rotation)
   {
   }


   // Static factory constructors
   template<typename T>
   inline constexpr Quat<T> Quat<T>::fromAngleAxis(T angleRadians,
      const Vector<3, T>& axis)
   {
      return Quat<T>(cos(angleRadians / 2), sin(angleRadians / 2) * axis);
   }


   // Assignment operators
   template<typename T>
   template<typename U>
   inline constexpr Quat<T>& Quat<T>::operator=(
      const Quat<U>& q)
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
   inline constexpr Quat<T>& Quat<T>::operator+=(
      const Quat<U>& q)
   {
      w += static_cast<T>(q.w);
      x += static_cast<T>(q.x);
      y += static_cast<T>(q.y);
      z += static_cast<T>(q.z);

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Quat<T>& Quat<T>::operator-=(
      const Quat<U>& q)
   {
      w -= static_cast<T>(q.w);
      x -= static_cast<T>(q.x);
      y -= static_cast<T>(q.y);
      z -= static_cast<T>(q.z);

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Quat<T>& Quat<T>::operator*=(
      const Quat<U>& q)
   {
      w = w * q.w - x * q.x - y * q.y - z * q.z;
      x = w * q.x + x * q.w + y * q.z - z * q.y;
      y = w * q.y + y * q.w + z * q.x - x * q.z;
      z = w * q.z + z * q.w + x * q.y - y * q.x;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Quat<T>& Quat<T>::operator*=(U scalar)
   {
      w *= static_cast<T>(scalar);
      x *= static_cast<T>(scalar);
      y *= static_cast<T>(scalar);
      z *= static_cast<T>(scalar);

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Quat<T>& Quat<T>::operator/=(U scalar)
   {
      w /= static_cast<T>(scalar);
      x /= static_cast<T>(scalar);
      y /= static_cast<T>(scalar);
      z /= static_cast<T>(scalar);

      return *this;
   }

   // Explicit conversion operators
   template <typename T>
   inline Quat<T>::operator Matrix<3, 3, T>() const
   {
      // TODO
      return Matrix<3, 3, T>();
   }

   template <typename T>
   inline Quat<T>::operator Matrix<4, 4, T>() const
   {
      // TODO
      return Matrix<4, 4, T>();
   }

   // Elements accessing
   template <typename T>
   inline constexpr T& Quat<T>::operator[](UInt32 pos)
   {
      if (pos >= 4)
         throw QuaternionDimensionError();

      return (&w)[pos];
   }

   template <typename T>
   inline constexpr const T& Quat<T>::operator[](UInt32 pos) const
   {
      if (pos >= 4)
         throw QuaternionDimensionError();

      return (&w)[pos];
   }


   // Non member operators
   template<typename T>
   constexpr Quat<T> operator+(const Quat<T>& qa,
      const Quat<T>& qb)
   {
      return Quat<T>(qa) += qb;
   }

   template<typename T>
   constexpr Quat<T> operator-(const Quat<T>& q)
   {
      return Quat<T>(-q.w, -q.x, -q.y, -q.z);
   }

   template<typename T>
   constexpr Quat<T> operator-(const Quat<T>& qa,
      const Quat<T>& qb)
   {
      return Quat<T>(qa) -= qb;
   }

   template<typename T>
   constexpr Quat<T> operator*(const Quat<T>& qa,
      const Quat<T>& qb)
   {
      return Quat<T>(qa) *= qb;
   }

   template<typename T>
   constexpr Vector<3, T> operator*(const Quat<T>& q,
      const Vector<3, T>& v)
   {
      return Vector<3, T>();
   }

   template<typename T>
   constexpr Vector<3, T> operator*(const Vector<3, T>& v,
      const Quat<T>& q)
   {
      return Vector<3, T>();
   }

   template<typename T>
   constexpr Vector<4, T> operator*(const Quat<T>& q,
      const Vector<4, T>& v)
   {
      return Vector<4, T>();
   }

   template<typename T>
   constexpr Vector<4, T> operator*(const Vector<4, T>& v,
      const Quat<T>& q)
   {
      return Vector<4, T>();
   }

   template<typename T>
   constexpr Quat<T> operator*(const Quat<T>& q, T const& scalar)
   {
      return Quat<T>(q) *= scalar;
   }

   template<typename T>
   constexpr Quat<T> operator*(T const& scalar, const Quat<T>& q)
   {
      return Quat<T>(q) *= scalar;
   }

   template<typename T>
   constexpr Quat<T> operator/(const Quat<T>& q, T const& scalar)
   {
      return Quat<T>(q) /= scalar;
   }

   
   // Relational operators
   template<typename T>
   constexpr bool operator==(const Quat<T>& qa, const Quat<T>& qb)
   {
      return qa.x == qb.x && qa.y == qb.y && qa.z == qb.z && qa.w == qb.w;
   }

   template<typename T>
   constexpr bool operator!=(const Quat<T>& qa, const Quat<T>& qb)
   {
      return !(qa == qb);
   }


   // Quaternion operations
   template<typename T>
   constexpr T dot(const Quat<T>& qa, const Quat<T>& qb)
   {
      return qa.w * qb.w + qa.x * qb.x + qa.y + qb.y + qa.z * qb.z;
   }

   template<typename T>
   constexpr Quat<T> cross(const Quat<T>& qa, const Quat<T>& qb)
   {
      return Quat<T>(
         qa.w * qb.w - qa.x * qb.x - qa.y * qb.y - qa.z * qb.z,
         qa.w * qb.x + qa.x * qb.w + qa.y * qb.z - qa.z * qb.y,
         qa.w * qb.y + qa.y * qb.w + qa.z * qb.x - qa.x * qb.z,
         qa.w * qb.z + qa.z * qb.w + qa.x * qb.y - qa.y * qb.x
      );
   }

   template<typename T>
   constexpr T norm(const Quat<T>& q)
   {  
      return sqrt(dot(q, q));
   }

   template<typename T>
   constexpr Quat<T> normalize(const Quat<T>& q)
   {
      T one_over_norm = one<T> / norm(q);
      return q * one_over_norm;
   }

   template<typename T>
   constexpr Quat<T> conjugate(const Quat<T>& q)
   {
      return Quat<T>(q.w, -q.v);
   }

   template<typename T>
   constexpr Quat<T> inverse(const Quat<T>& q)
   {
      return conjugate(q) / dot(q, q);
   }


   // Ostream operator
   template <typename T>
   std::ostream& operator<<(std::ostream& os, const Quat<T>& q)
   {
      os << "Neat::Quaternion<" << typeid(T).name() << "> (";
      for (UInt32 i = 0; i < q.size(); ++i)
      {
         if (i < q.size() - 1)
         {
            os << std::setw(10) << std::setprecision(6)
               << q[i] << ", ";
            if (i == 0)
               os << "[";
         }
         else
            os << std::setw(10) << std::setprecision(6)
            << q[i];
      }
      os << "])";

      return os;
   }
}