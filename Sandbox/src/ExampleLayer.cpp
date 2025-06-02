#include <memory>

#include <Neat.hpp>
#include "ExampleLayer.hpp"


void ExampleLayer::onImGuiRender() {
  auto stats = Neat::Renderer2D::getStats();
  ImGui::Text("Renderer2D stats:");
  ImGui::Text("Draw calls: %d", stats.drawCalls);
  ImGui::Text("Quads: %d", stats.quadCount);
  ImGui::Text("Indexes: %d", stats.getTotalIndexCount());
  ImGui::Text("Vertexes: %d\n", stats.getTotalVertexCount());

  //ImGui::SliderInt("Number of columns", &this->numberOfColumns, 0, 500);
  //ImGui::SliderInt("Number of lines", &this->numberOfLines, 0, 500);

  //ImGui::ColorEdit4("Square Color", this->tint.dataPointer());
}