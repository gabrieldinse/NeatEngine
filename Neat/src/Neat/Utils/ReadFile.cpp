#include "NeatPCH.hpp"

#include "Neat/Utils/ReadFile.hpp"

namespace Neat {
std::ostream& operator<<(std::ostream& os, const FileError& err) {
  os << "FileError[" << err.path << "]: ";
  switch (err.code) {
    case FileErrorCode::FileNotFound:
      os << "File not found.";
      break;
    case FileErrorCode::PermissionDenied:
      os << "Permission denied.";
      break;
    case FileErrorCode::NotAFile:
      os << "Not a regular file.";
      break;
    case FileErrorCode::ReadFailure:
      os << "Failed to read file.";
      break;
    case FileErrorCode::FileTooLarge:
      os << "File exceeds size limit.";
      break;
    case FileErrorCode::Unknown:
      os << "Unknown error.";
      break;
  }
  if (!err.message.empty()) {
    os << " (" << err.message << ")";
  }
  return os;
}

std::expected<std::string, FileError> readFile(
    const std::filesystem::path& path) {
  NT_PROFILE_FUNCTION();
  std::error_code error_code;

  if (not std::filesystem::exists(path, error_code)) {
    return std::unexpected{
        FileError{FileErrorCode::FileNotFound, path, error_code.message()}};
  }

  if (not std::filesystem::is_regular_file(path, error_code)) {
    return std::unexpected{
        FileError{FileErrorCode::NotAFile, path, error_code.message()}};
  }

  std::size_t size = std::filesystem::file_size(path, error_code);
  if (error_code) {
    return std::unexpected{
        FileError{FileErrorCode::ReadFailure, path, error_code.message()}};
  }

  if (size > maxFileSize) {
    return std::unexpected{FileError{FileErrorCode::FileTooLarge, path,
                                     "Too big for asset loader."}};
  }

  std::ifstream file(path, std::ios::in | std::ios::binary);
  if (not file) {
    return std::unexpected{FileError{FileErrorCode::PermissionDenied, path,
                                     "Failed to open file."}};
  }

  std::string fileContent{};
  fileContent.resize(size);
  if (not file.read(fileContent.data(), fileContent.size())) {
    return std::unexpected{
        FileError{FileErrorCode::ReadFailure, path, "Stream read failed."}};
  }

  return fileContent;
}
}  // namespace Neat