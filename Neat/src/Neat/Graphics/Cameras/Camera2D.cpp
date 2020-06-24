#include "Neat/Graphics/Cameras/Camera2D.h"


namespace Neat
{
   Camera2D::Camera2D(float size, KeepAspect keepAspect)
      : m_camera(Camera())
      , m_size(size)
      , m_keepAspect(keepAspect)
   {
      setSize(m_size);
   }


   void Camera2D::setSize(float size, KeepAspect keepAspect)
   {
      m_keepAspect = keepAspect;
      m_size = size;
      updateProjection();
   }

   void Camera2D::setSize(float size)
   {
      m_size = size;
      updateProjection();
   }

   void Camera2D::setZoomLevel(float zoomLevel)
   {
      m_zoomLevel = zoomLevel;
      updateProjection();
   }


   void Camera2D::updateProjection()
   {
      switch (m_keepAspect)
      {
         case KeepAspect::Height:
            m_camera.setOrthographic(-m_size * m_zoomLevel, m_size * m_zoomLevel,
               -m_zoomLevel, m_zoomLevel);
            break;

         case KeepAspect::Width:
            m_camera.setOrthographic(-m_zoomLevel, m_zoomLevel,
               -m_size * m_zoomLevel, m_size * m_zoomLevel);
            break;
      }
   }
}