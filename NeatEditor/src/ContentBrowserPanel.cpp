#include "ContentBrowserPanel.hpp"

#include "Core/Log.hpp"

#include <ImGui/imgui.h>

namespace Neat {
const std::filesystem::path ContentBrowserPanel::s_assetsPath =
    "NeatEditorAssets/Resources";

ContentBrowserPanel::ContentBrowserPanel()
    : m_currentDirectory(s_assetsPath),
      m_directoryIcon(Texture2D::create(
          "NeatEditorAssets/Resources/Icons/ContentBrowser/DirectoryIcon.png")),
      m_fileIcon(Texture2D::create(
          "NeatEditorAssets/Resources/Icons/ContentBrowser/FileIcon.png")) {}

void ContentBrowserPanel::onUpdate() {
  ImGui::Begin("Content Browser");

  if (m_currentDirectory != std::filesystem::path(s_assetsPath)) {
    if (ImGui::Button("<-")) {
      m_currentDirectory = m_currentDirectory.parent_path();
    }
  }

  const float padding = 16.0f;
  const float thumbnailSize = 64.0f;

  float cellSize = thumbnailSize + padding;

  float panelWidth = ImGui::GetContentRegionAvail().x;
  int columnCount = static_cast<int>(panelWidth / cellSize);
  if (columnCount < 1) {
    columnCount = 1;
  }

  ImGui::Columns(columnCount, 0, false);

  for (const auto &directoryEntry :
       std::filesystem::directory_iterator(m_currentDirectory)) {
    const auto &entryPath = directoryEntry.path();
    const auto relativePath =
        std::filesystem::relative(entryPath, s_assetsPath);
    const auto relativePathStr = relativePath.string();
    const std::string filename = relativePath.filename().string();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

    Ref<Texture2D> icon =
        directoryEntry.is_directory() ? m_directoryIcon : m_fileIcon;
    ImGui::ImageButton(filename.c_str(),
                       static_cast<ImTextureID>(icon->getRendererID()),
                       {thumbnailSize, thumbnailSize}, {0, 1}, {1, 0});

    if (ImGui::BeginDragDropSource()) {
      const char *itemPath = relativePathStr.c_str();
      ImGui::SetDragDropPayload("Content Browser Item", itemPath,
                                strlen(itemPath) + 1);
      ImGui::EndDragDropSource();
    }

    ImGui::PopStyleColor();

    if (ImGui::IsItemHovered() and
        ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
      if (directoryEntry.is_directory()) {
        m_currentDirectory /= entryPath.filename();
      }
    }

    ImGui::TextWrapped("%s", filename.c_str());

    ImGui::NextColumn();
  }

  ImGui::Columns(1);

  ImGui::End();
}
}  // namespace Neat
