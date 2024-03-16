#pragma once

#include <memory>
#include <optional>

// #include "ssdui/component/concept.hh"
#include "ssdui/context/config.hh"
#include "ssdui/render/concept.hh"

namespace ssdui::context {

template <typename Rnd>
  requires render::IsRenderer<Rnd>
class Context;

template <typename Rnd>
  requires render::IsRenderer<Rnd>
class ContextBuilder;

namespace _helper {

/**
 * @brief Copy of IsComponent concept, to avoid circular dependency
 *
 * @tparam Cmp Component type
 * @tparam Rnd Renderer type
 */
template <typename Cmp, typename Rnd>
concept IsComponent = requires(Cmp comp) {
  { comp(std::shared_ptr<context::Context<Rnd>>{}) };
};

template <typename Rnd>
  requires render::IsRenderer<Rnd>
class BaseComponent {
 public:
  virtual void operator()(std::shared_ptr<context::Context<Rnd>> ctx) = 0;
};

}  // namespace _helper

/**
 * @brief 上下文对象
 *
 * @tparam Rnd Renderer type
 */
template <typename Rnd>
  requires render::IsRenderer<Rnd>
class Context : public std::enable_shared_from_this<Context<Rnd>> {
  friend class ContextBuilder<Rnd>;

 public:
  using Self = Context;

 private:
  // config
  Config m_config;
  // renderer
  // Rnd m_renderer;
  std::unique_ptr<Rnd> m_renderer;
  // buffer
  // mounted components
  std::unique_ptr<_helper::BaseComponent<Rnd>> m_root{nullptr};

  // private constructor
  explicit Context(const Config& cfg, std::unique_ptr<Rnd> renderer)
      : m_config(cfg), m_renderer(std::move(renderer)) {}

 public:
  // Getters
  [[nodiscard]] const Config& config() const { return m_config; }
  [[nodiscard]] Rnd* renderer() const { return m_renderer.get(); }

  template <typename Cmp>
    requires _helper::IsComponent<Cmp, Rnd>
  std::shared_ptr<Self> run(const Cmp& comp) {
    auto shared_this = this->shared_from_this();
    comp(shared_this);
    return shared_this;
  }

  std::shared_ptr<Self> mount(
      std::unique_ptr<_helper::BaseComponent<Rnd>> root) {
    auto shared_this = this->shared_from_this();
    m_root = std::move(root);
    return this->run(*m_root);
  }
};

/**
 * @brief Builder for Context
 *
 * @tparam Rnd Renderer type
 */
template <typename Rnd>
  requires render::IsRenderer<Rnd>
class ContextBuilder {
 public:
  using Self = ContextBuilder;

 private:
  std::optional<Config> m_config{std::nullopt};
  std::unique_ptr<Rnd> m_renderer{nullptr};

 public:
  // Setters
  Self& config(const Config& cfg) {
    m_config = cfg;
    return *this;
  }

  Self& renderer(std::unique_ptr<Rnd> renderer) {
    m_renderer = std::move(renderer);
    return *this;
  }

  // Build
  std::shared_ptr<Context<Rnd>> build() {
    if (!m_config.has_value() || m_renderer == nullptr) {
      throw std::runtime_error("ContextBuilder: missing config or renderer");
    }
    return std::make_shared<Context<Rnd>>(m_config.value(),
                                          std::move(m_renderer));
  }
};

}  // namespace ssdui::context

// Dynamic polymorphism for components
namespace ssdui::component {

// BaseComponent are used only in context, to insert any component as root,
// Use concept IsComponent will cause circular dependency, and will expand the
// template parameter list of Context, so this is a resolution by using dynamic
// polymorphism
template <typename Rnd>
using BaseComponent = context::_helper::BaseComponent<Rnd>;

}  // namespace ssdui::component
