#pragma once


namespace Neat
{
   template <typename T = float>
   struct Quaternion
   {
      using Type = Quaternion<T>;
      using ValueType = T;


      // Class data
      union
      {
         struct { T w, x, y, z; };
         struct { T a, b, c, d; };
         struct { T q0, q1, q2, q3; };
         struct { T s; Vector3 v; };
      };


   };
}

#include "TypeQuaternion.inl"