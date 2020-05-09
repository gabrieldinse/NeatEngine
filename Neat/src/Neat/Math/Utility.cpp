#include "Neat/Math/Utility.h"


namespace Neat
{
   Float degreesToRadians(Float angleDegrees)
   {
      return angleDegrees * pi / 180.0f;
   }

   Float radiansToDegrees(Float angleRadians)
   {
      return angleRadians * 180.0f / pi;
   }
}