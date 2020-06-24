#pragma once

#include <stdexcept>
#include <string>


namespace Neat
{
   // -------------------------------------------------------------------------
   // Base common exception ---------------------------------------------------
   struct Exception : public std::exception
   {
      Exception(const std::string& msg) : m_msg(msg) {}

      const std::string& msg() const { return m_msg; }
      virtual const char* what() const override { return m_msg.c_str(); }

   private:
      std::string m_msg;
   };
   // -------------------------------------------------------------------------
   // -------------------------------------------------------------------------


   // Timer exceptions --------------------------------------------------
   struct TimerError : Exception
   {
      TimerError(const std::string& msg) : Exception(msg) {}
   };

   struct TimerNotStartedError : public TimerError
   {
      TimerNotStartedError(
         const std::string& msg = "Timer has not been started.")
         : TimerError(msg) {}
   };
   // -------------------------------------------------------------------------


   // Math exceptions ---------------------------------------------------------
   struct MathError : public Exception
   {
      MathError(const std::string& msg) : Exception(msg) {}
   };

   // Vectors
   struct VectorDimensionError : public MathError
   {
      VectorDimensionError(
         const std::string& msg = "Wrong Vector dimension being acessed.")
         : MathError(msg) {}
   };

   // Matrices
   struct MatrixDimensionError : public MathError
   {
      MatrixDimensionError(
         const std::string& msg = "Wrong Matrix dimension being acessed.")
         : MathError(msg) {}
   };

   // Quaternion
   struct QuaternionDimensionError : public MathError
   {
      QuaternionDimensionError(
         const std::string& msg = "Wrong Quaternion dimension being acessed.")
         : MathError(msg) {}
   };

   struct QuaternionLogUndefined : public MathError
   {
      QuaternionLogUndefined(
         const std::string& msg = "Log of Quaternion is undefined")
         : MathError(msg) {}
   };

   struct QuaternionLerpStepError : public MathError
   {
      QuaternionLerpStepError(
         const std::string& msg = "Lerp step parameter t must be in "
            "range [0, 1]")
         : MathError(msg) {}
   };
   // -------------------------------------------------------------------------


   // Camera exceptions -------------------------------------------------------
   struct CameraError : public Exception
   {
      CameraError(const std::string& msg) : Exception(msg) {}
   };

   struct CameraTypeHasNotBeenSettedError : public CameraError
   {
      CameraTypeHasNotBeenSettedError(
         const std::string& msg = "Camera type was not setted yet. "
         "Use Camera::setOrthographic or Camera::setPerspective methods "
         "before using camera functionalities.")
         : CameraError(msg) {}
   };

   struct WrongCameraTypeError : public CameraError
   {
      WrongCameraTypeError(
         const std::string& msg = "The camera type you are using does not"
            "support this method.")
         : CameraError(msg) {}
   };
   // -------------------------------------------------------------------------

   // Event exceptions --------------------------------------------------------
   struct EventError : public Exception
   {
      EventError(const std::string& msg) : Exception(msg) {}
   };

   // Event subscriptions
   struct EventListenerError : public EventError
   {
      EventListenerError(
         const std::string& msg = "EventListener is not connected to Event.")
         : EventError(msg) {}
   };
   // -------------------------------------------------------------------------


   // ECS exceptions ----------------------------------------------------------
   struct ECSError : public Exception
   {
      ECSError(const std::string& msg) : Exception(msg) {}
   };

   // Entities
   struct EntityError : public ECSError
   {
      EntityError(const std::string& msg) : ECSError(msg) {}
   };

   struct InvalidEntityError : public EntityError
   {
      InvalidEntityError(
         const std::string& msg = "Acessed Entity is invalid.")
         : EntityError(msg) {}
   };
   
   struct InvalidEntityIdIndexError : public InvalidEntityError
   {
      InvalidEntityIdIndexError(
         const std::string& msg = "Entity::Id outside Entity vector range.")
         : InvalidEntityError(msg) {}
   };

   struct InvalidEntityIdVersionError : public InvalidEntityError
   {
      InvalidEntityIdVersionError(
         const std::string& msg = "Attempt to access Entity via a stale"
            " Entity::Id.")
         : InvalidEntityError(msg) {}
   };

   struct ComponentAlreadyAddedError : public EntityError
   {
      ComponentAlreadyAddedError(
         const std::string& msg = "Component already added to Entity.")
         : EntityError(msg) {}
   };

   struct ComponentNotPresentError : public EntityError
   {
      ComponentNotPresentError(
         const std::string& msg = "Component is not present in the Entity.")
         : EntityError(msg) {}
   };

   // Components
   struct ComponentError : public ECSError
   {
      ComponentError(const std::string& msg) : ECSError(msg) {}
   };

   struct BadComponentAllocationError : public ComponentError
   {
      BadComponentAllocationError(
         const std::string& msg = "You should not delete components directly. "
         "Use Entity::destroyEntity() instead.")
         : ComponentError(msg) {}
   };

   struct InvalidComponentError : public ComponentError
   {
      InvalidComponentError(
         const std::string& msg = "Acessed component is invalid.")
         : ComponentError(msg) {}
   };

   struct MaximumNumberOfComponentsError : public ComponentError
   {
      MaximumNumberOfComponentsError(
         const std::string& msg = "Maximum number of components reached.")
         : ComponentError(msg) {}
   };
   
   // Systems
   struct SystemError : public ECSError
   {
      SystemError(const std::string& msg) : ECSError(msg) {}
   };

   struct SystemManagerNotInitializedError : public SystemError
   {
      SystemManagerNotInitializedError(
         const std::string& msg = "SystemManager::init() not called.")
         : SystemError(msg) {}
   };

   struct InvalidSystemError : public SystemError
   {
      InvalidSystemError(const std::string& msg = "System does not exist.")
         : SystemError(msg) {}
   };
   // -------------------------------------------------------------------------
}