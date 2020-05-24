#include "Neat/Math/Utility.h"


namespace Neat
{
   float degreesToRadians(float angleDegrees)
   {
      return (float)((angleDegrees / 180.0) * NT_PI);
   }

   float radiansToDegrees(float angleRadians)
   {
      return (float)((angleRadians / NT_PI) * 180.0);
   }

   double degreesToRadiansD(double angleDegrees)
   {
      return (angleDegrees / 180.0) * NT_PI;
   }

   double radiansToDegreesD(double angleRadians)
   {
      return (angleRadians / NT_PI) * 180.0;
   }
}