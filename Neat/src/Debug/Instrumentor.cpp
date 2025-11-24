#include "NeatPCH.hpp"

#include "Instrumentor.hpp"

#include "Core/Log.hpp"

namespace Neat {
void Instrumentor::beginSession(const std::string &name,
                                const std::string outputFilepath) {
  std::lock_guard lock{m_mutex};
  NT_CORE_INFO("Instrumentor::beginSession('{0}').", name);
  if (m_currentSession) {
    // In case the logger is not initialized yet
    if (Log::getCoreLogger()) {
      NT_CORE_ERROR(
          "Instrumentor::beginSession('{0}') when session '{1}' already "
          "open.",
          name, m_currentSession->name);
    }
    endCurrentSession();
  }
  m_outputStream.open(outputFilepath);
  if (m_outputStream.is_open()) {
    m_currentSession = makeScope<InstrumentationSession>(name);
    writeHeader();
  } else {
    if (Log::getCoreLogger()) {
      NT_CORE_ERROR("Instrumentor could not open results file '{0}'.",
                    outputFilepath);
    }
  }
}

void Instrumentor::writeProfile(const ProfileResult &result) {
  std::stringstream json;

  json << std::setprecision(3) << std::fixed;
  json << ",{";
  json << "\"cat\":\"function\",";
  json << "\"dur\":" << result.elapsedTime << ',';
  json << "\"name\":\"" << result.name << "\",";
  json << "\"ph\":\"X\",";
  json << "\"pid\":0,";
  json << "\"tid\":" << result.threadID << ",";
  json << "\"ts\":" << result.startTime;
  json << "}";

  std::lock_guard lock{m_mutex};
  if (m_currentSession) {
    m_outputStream << json.str();
    m_outputStream.flush();
  }
}

Instrumentor &Instrumentor::get() {
  static Instrumentor instance;
  return instance;
}

void Instrumentor::endSession() {
  std::lock_guard lock{m_mutex};
  endCurrentSession();
}

void Instrumentor::writeHeader() {
  m_outputStream << "{\"otherData\": {},\"traceEvents\":[{}";
  m_outputStream.flush();
}

void Instrumentor::writeFooter() {
  m_outputStream << "]}";
  m_outputStream.flush();
}

void Instrumentor::endCurrentSession() {
  if (m_currentSession) {
    NT_CORE_INFO("Instrumentor::endSession('{0}').", m_currentSession->name);
    writeFooter();
    m_outputStream.close();
    m_currentSession.reset();
  }
}
}  // namespace Neat