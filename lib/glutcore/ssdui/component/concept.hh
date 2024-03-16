#pragma once

#include <memory>
#include <tuple>
#include <type_traits>

#include "ssdui/context/core.hh"

#define CHECK_COMPONENT(Cmp, Rnd)                        \
  static_assert(ssdui::component::IsComponent<Cmp, Rnd>, \
                "Cmp is not a component")

namespace ssdui::component {

template <typename Cmp, typename Rnd>
concept IsComponent = requires(Cmp comp) {
  { comp(std::shared_ptr<context::Context<Rnd>>{}) };
};

// maybe another wat to impl
template <typename Cmp, typename Rnd, typename Event>
concept IsEventComponent = requires(Cmp comp) {
  requires std::is_enum_v<Event>;
  requires IsComponent<Cmp, Rnd>;
  { comp.on_event(std::shared_ptr<context::Context<Rnd>>{}, Event{}) };
  { comp.flush(std::shared_ptr<context::Context<Rnd>>{}) };
};

// deprecated: Children should be managed by component itself
template <typename Cmp, typename Rnd, typename... Chils>
concept IsStaticTreeComponent = requires(Cmp comp) {
  requires IsComponent<Cmp, Rnd>;
  { comp.children } -> common::SameAs<std::tuple<Chils...>>;
};

// deprecated
template <typename Cmp, typename Rnd>
concept IsDynamicTreeComponent = requires(Cmp comp) {
  requires IsComponent<Cmp, Rnd>;
  { comp.children } -> common::SameAs<std::vector<BaseComponent<Rnd>>>;
};

}  // namespace ssdui::component
