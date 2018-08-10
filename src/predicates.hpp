#pragma once

#include <sc2api/sc2_typeenums.h>
#include <sc2api/sc2_unit.h>

namespace ares {

struct Is_nullptr {
  template <typename T>
  constexpr bool operator()(T* p) const {
    return p == nullptr;
  }
};

struct Is_unit_type {
  sc2::UNIT_TYPEID type;

  // Cannot be constexpr because toType() is not.
  bool operator()(const sc2::Unit& unit) const {
    return unit.unit_type.ToType() == type;
  }
};

constexpr auto is_unit_scv = Is_unit_type{sc2::UNIT_TYPEID::TERRAN_SCV};

}  // namespace ares
