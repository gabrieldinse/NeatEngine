#pragma once

#include <mutex>
#include <fstream>

#include "InstrumentationSession.hpp"
#include "ProfileResult.hpp"

#include "Core/Types.hpp"

namespace Neat {
class Instrumentor {
 public:
  Instrumentor(const Instrumentor &) = delete;
  Instrumentor(Instrumentor &&) = delete;

  void beginSession(const std::string &name, const std::string outputFilepath =
                                                 "instrumentor_results.json");
  void writeProfile(const ProfileResult &result);
  static Instrumentor &get();

  void endSession();

 private:
  Instrumentor() = default;
  ~Instrumentor() { endSession(); }

  void writeHeader();
  void writeFooter();
  void endCurrentSession();

 private:
  std::mutex m_mutex;
  Scope<InstrumentationSession> m_currentSession;
  std::ofstream m_outputStream;
};
}  // namespace Neat