#pragma once

#include <ostream>

#include "Neat/Core/Types.hpp"
#include "Neat/Core/Limits.hpp"

namespace Neat {
class EntityManager;

class EntityId {
  public:
  EntityId() : m_id(0) {}
  EntityId(UInt32 index, UInt32 version)
      : m_id(UInt64(index) | UInt64(version) << 32) {}
  explicit EntityId(UInt64 id) : m_id(id) {}

  UInt64 id() const { return m_id; }
  UInt32 index() const { return (UInt32)(m_id & UInt64(UInt32Max)); }
  UInt32 version() const { return (UInt32)(m_id >> 32); }

  bool operator==(const EntityId &other) const { return m_id == other.m_id; }
  bool operator!=(const EntityId &other) const { return m_id != other.m_id; }
  bool operator<(const EntityId &other) const { return m_id < other.m_id; }

  private:
  friend class EntityManager;

  private:
  UInt64 m_id;
};

std::ostream &operator<<(std::ostream &os, const EntityId &id);
}  // namespace Neat