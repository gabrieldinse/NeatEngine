#pragma once

#include <stdexcept>


namespace Neat
{
   // Base common exception
   struct Exception : public std::runtime_error
   {
      Exception(const char* msg) : std::runtime_error(msg) {}
   };


   // Math exceptions ---------------------------------------------------------
   struct MathError : public Exception
   {
      MathError(const char* msg) : Exception(msg) {}
   };

   struct VecDimensionError : public MathError
   {
      VecDimensionError(const char* msg = "Wrong Vec dimension being acessed.")
         : MathError(msg) {}
   };

   struct MatDimensionError : public MathError
   {
      MatDimensionError(const char* msg = "Wrong Mat dimension being acessed.")
         : MathError(msg) {}
   };
   // -------------------------------------------------------------------------

   // ECS exceptions ----------------------------------------------------------
   struct ECSError : public Exception
   {
      ECSError(const char* msg) : Exception(msg) {}
   };

   struct BadComponentAllocationError : public ECSError
   {
      BadComponentAllocationError(
         const char* msg = "You should not delete components directly. "
                           "Use Entity::destroy() instead.")
         : ECSError(msg) {}
   };

   struct InvalidEntityError : public ECSError
   {
      InvalidEntityError(const char* msg = "Acessed entity is invalid.")
         : ECSError(msg) {}
   };

   struct InvalidComponentError : public ECSError
   {
      InvalidComponentError(const char* msg = "Acessed component is invalid.")
         : ECSError(msg) {}
   };

   struct MaximumNumberOfComponentsError : public ECSError
   {
      MaximumNumberOfComponentsError(
         const char* msg = "Maximum number of components reached.")
         : ECSError(msg) {}
   };

   struct EventSubscriptionError : public ECSError
   {
      EventSubscriptionError(const char* msg = "Event is not subscribed.")
         : ECSError(msg) {}
   };

   struct SystemManagerNotInitializedError : public ECSError
   {
      SystemManagerNotInitializedError(
         const char* msg = "SystemManager::init() not called.")
         : ECSError(msg) {}
   };

   struct InvalidSystemError : public ECSError
   {
      InvalidSystemError(const char* msg = "System does not exist.")
         : ECSError(msg) {}
   };
   
   // -------------------------------------------------------------------------
}