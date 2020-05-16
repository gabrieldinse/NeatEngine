

namespace Neat
{
   // Default constructor
   template <typename T>
   constexpr
   Vec<1, T>::Vec() : x(static_cast<T>(0)) {}


   // Basic Constructors
   template <typename T>
   constexpr
   Vec<1, T>::Vec(T scalar) : x(scalar) {}


   // Copy Constructor
   template <typename T>
   constexpr
   Vec<1, T>::Vec(const Vec<1, T>& v) : x(v.x) {}


   // Conversion constructors
   template <typename T>
   template <typename U>
   constexpr
   Vec<1, T>::Vec(const Vec<1, U>& v) : x(static_cast<T>(v.x)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vec<1, T>::Vec(const Vec<4, U>& v) : x(static_cast<T>(v.x)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vec<1, T>::Vec(const Vec<3, U>& v) : x(static_cast<T>(v.x)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vec<1, T>::Vec(const Vec<2, U>& v) : x(static_cast<T>(v.x)) {}

   template <typename T>
   template <typename X>
   constexpr
   Vec<1, T>::Vec(X x) : x(static_cast<T>(x)) {}


   // Assignment operators
   template <typename T>
   constexpr
   Vec<1, T>& Vec<1, T>::operator=(T scalar)
   {
      x = scalar;

      return *this;
   }

   template <typename T>
   constexpr
   Vec<1, T>& Vec<1, T>::operator=(const Vec<4, T>& other)
   {
      x = other.x;

      return *this;
   }

   template <typename T>
   constexpr
   Vec<1, T>& Vec<1, T>::operator=(const Vec<3, T>& other)
   {
      x = other.x;

      return *this;
   }

   template <typename T>
   constexpr
   Vec<1, T>& Vec<1, T>::operator=(const Vec<2, T>& other)
   {
      x = other.x;

      return *this;
   }

   template <typename T>
   constexpr
   Vec<1, T>& Vec<1, T>::operator=(const Vec<1, T>& other)
   {
      x = other.x;

      return *this;
   }

   // Compound assignment operators
   template<typename T>
   template<typename U>
   inline constexpr Vec<1, T>& Vec<1, T>::operator+=(const Vec<1, U>& v)
   {
      x += v.x;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vec<1, T>& Vec<1, T>::operator-=(const Vec<1, U>& v)
   {
      x -= v.x;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vec<1, T>& Vec<1, T>::operator*=(const Vec<1, U>& v)
   {
      x *= v.x;


      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vec<1, T>& Vec<1, T>::operator*=(U scalar)
   {
      x *= scalar;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vec<1, T>& Vec<1, T>::operator/=(U scalar)
   {
      x /= scalar;

      return *this;
   }


   template <typename T>
   inline constexpr
      Vec<1, T>::operator bool() const
   {
      return (x > 0);
   }


   template<typename T>
   inline  constexpr
   T& Vec<1, T>::operator[](std::size_t pos)
   {
      switch (pos)
      {
         case static_cast<T>(0): return x;
      }

      throw VecDimensionError();
   }

   template<typename T>
   inline constexpr
   const T& Vec<1, T>::operator[](std::size_t pos) const
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
      Vec<1, T> operator+(const Vec<1, T>& va, const Vec<1, T>& vb)
   {
      return Vec<1, T>(*this) += vb;
   }

   template <typename T>
   inline constexpr
      Vec<1, T> operator-(const Vec<1, T>& v)
   {
      return Vec<1, T>(-v.x);
   }

   template <typename T>
   inline constexpr
      Vec<1, T> operator-(const Vec<1, T>& va, const Vec<1, T>& vb)
   {
      return Vec<1, T>(va) -= vb;
   }

   template <typename T>
   inline constexpr
      Vec<1, T> operator*(const Vec<1, T>& va, const Vec<1, T>& vb)
   {
      return Vec<1, T>(va) *= vb;
   }

   template <typename T>
   inline constexpr
      Vec<1, T> operator*(T scalar, const Vec<1, T>& v)
   {
      return Vec<1, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
      Vec<1, T> operator*(const Vec<1, T>& v, T scalar)
   {
      return Vec<1, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
      Vec<1, T> operator/(const Vec<1, T>& v, T scalar)
   {
      return Vec<1, T>(v) /= scalar;
   }
}