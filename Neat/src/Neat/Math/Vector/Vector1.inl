

namespace Neat
{
   // Default constructor
   template <typename T>
   inline constexpr
   Vector<1, T>::Vector() : x(static_cast<T>(0)) {}


   // Basic Constructors
   template <typename T>
   inline constexpr
   Vector<1, T>::Vector(T scalar) : x(scalar) {}


   // Copy Constructor
   template <typename T>
   inline constexpr
   Vector<1, T>::Vector(const Vector<1, T>& v) : x(v.x) {}


   // Conversion constructors
   template <typename T>
   template <typename U>
   inline constexpr
   Vector<1, T>::Vector(const Vector<1, U>& v) : x(static_cast<T>(v.x)) {}

   template <typename T>
   template <typename U>
   inline constexpr
   Vector<1, T>::Vector(const Vector<4, U>& v) : x(static_cast<T>(v.x)) {}

   template <typename T>
   template <typename U>
   inline constexpr
   Vector<1, T>::Vector(const Vector<3, U>& v) : x(static_cast<T>(v.x)) {}

   template <typename T>
   template <typename U>
   inline constexpr
   Vector<1, T>::Vector(const Vector<2, U>& v) : x(static_cast<T>(v.x)) {}

   template <typename T>
   template <typename X>
   inline constexpr
   Vector<1, T>::Vector(X x) : x(static_cast<T>(x)) {}


   // Assignment operators
   template <typename T>
   inline constexpr
   Vector<1, T>& Vector<1, T>::operator=(T scalar)
   {
      x = scalar;

      return *this;
   }

   template <typename T>
   template <typename U>
   inline constexpr
   Vector<1, T>& Vector<1, T>::operator=(const Vector<1, U>& other)
   {
      x = other.x;

      return *this;
   }


   // Compound assignment operators
   template<typename T>
   template<typename U>
   inline constexpr
   Vector<1, T>& Vector<1, T>::operator+=(const Vector<1, U>& v)
   {
      x += v.x;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vector<1, T>& Vector<1, T>::operator-=(const Vector<1, U>& v)
   {
      x -= v.x;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vector<1, T>& Vector<1, T>::operator*=(const Vector<1, U>& v)
   {
      x *= v.x;


      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vector<1, T>& Vector<1, T>::operator*=(U scalar)
   {
      x *= scalar;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vector<1, T>& Vector<1, T>::operator/=(U scalar)
   {
      x /= scalar;

      return *this;
   }


   template <typename T>
   inline constexpr
   Vector<1, T>::operator bool() const
   {
      return (x > 0);
   }


   template<typename T>
   inline  constexpr
   T& Vector<1, T>::operator[](std::size_t pos)
   {
      switch (pos)
      {
         case static_cast<T>(0): return x;
      }

      throw VecDimensionError();
   }

   template<typename T>
   inline constexpr
   const T& Vector<1, T>::operator[](std::size_t pos) const
   {
      switch (pos)
      {
         case 0: return x;
      }

      throw VecDimensionError();
   }


   // Non member operators
   template <typename T>
   inline constexpr
      Vector<1, T> operator+(const Vector<1, T>& va, const Vector<1, T>& vb)
   {
      return Vector<1, T>(*this) += vb;
   }

   template <typename T>
   inline constexpr
      Vector<1, T> operator-(const Vector<1, T>& v)
   {
      return Vector<1, T>(-v.x);
   }

   template <typename T>
   inline constexpr
      Vector<1, T> operator-(const Vector<1, T>& va, const Vector<1, T>& vb)
   {
      return Vector<1, T>(va) -= vb;
   }

   template <typename T>
   inline constexpr
      Vector<1, T> operator*(const Vector<1, T>& va, const Vector<1, T>& vb)
   {
      return Vector<1, T>(va) *= vb;
   }

   template <typename T>
   inline constexpr
      Vector<1, T> operator*(T scalar, const Vector<1, T>& v)
   {
      return Vector<1, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
      Vector<1, T> operator*(const Vector<1, T>& v, T scalar)
   {
      return Vector<1, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
      Vector<1, T> operator/(const Vector<1, T>& v, T scalar)
   {
      return Vector<1, T>(v) /= scalar;
   }
}