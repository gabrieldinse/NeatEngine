#pragma once

#include <filesystem>

#include "Graphics/Texture2D.hpp"

namespace Neat {
class ContentBrowserPanel {
 public:
  ContentBrowserPanel();

  void update();
  static std::filesystem::path getAssetsPath() { return s_assetsPath; }

 private:
  std::filesystem::path m_currentDirectory;
  Ref<Texture2D> m_directoryIcon;
  Ref<Texture2D> m_fileIcon;

  static const std::filesystem::path s_assetsPath;
};
}  // namespace Neat