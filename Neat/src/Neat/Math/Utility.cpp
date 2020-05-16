#include "Neat/Math/Utility.h"


namespace Neat
{
   float degreesToRadians(float angleDegrees)
   {
      return angleDegrees * NT_PI / 180.0f;
   }

   float radiansToDegrees(float angleRadians)
   {
      return angleRadians * 180.0f / NT_PI;
   }
}