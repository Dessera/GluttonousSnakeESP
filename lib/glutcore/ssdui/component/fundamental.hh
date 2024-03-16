#pragma once

#include <cstdint>

#include "ssdui/component/concept.hh"

namespace ssdui::command::fundamental {

template <typename Rnd>
  requires render::IsRenderer<Rnd>
class Nop {
 public:
  static inline constexpr uint8_t COMMAND_CODE = 0xE3;

  void operator()(std::shared_ptr<context::Context<Rnd>> ctx) const {
    ctx->renderer()->command({COMMAND_CODE});
  }
};

template <typename Rnd>
  requires render::IsRenderer<Rnd>
class SetDisplay {
 public:
  static inline constexpr uint8_t COMMAND_DISPLAY_ON = 0xAF;
  static inline constexpr uint8_t COMMAND_DISPLAY_OFF = 0xAE;

 private:
  bool m_state;

 public:
  explicit SetDisplay(bool state) : m_state(state) {}

  void operator()(std::shared_ptr<context::Context<Rnd>> ctx) const {
    ctx->renderer()->command(
        {m_state ? COMMAND_DISPLAY_ON : COMMAND_DISPLAY_OFF});
  }
};

template <typename Rnd>
  requires render::IsRenderer<Rnd>
class SetContrast {
 public:
  static inline constexpr uint8_t COMMAND_SET_CONTRAST = 0x81;

 private:
  uint8_t m_contrast;

 public:
  explicit SetContrast(uint8_t contrast) : m_contrast(contrast) {}

  void operator()(std::shared_ptr<context::Context<Rnd>> ctx) const {
    ctx->renderer()->command({COMMAND_SET_CONTRAST, m_contrast});
  }
};

template <typename Rnd>
  requires render::IsRenderer<Rnd>
class SetInvert {
 public:
  static inline constexpr uint8_t COMMAND_INVERT_ON = 0xA7;
  static inline constexpr uint8_t COMMAND_INVERT_OFF = 0xA6;

 private:
  bool m_state;

 public:
  explicit SetInvert(bool state) : m_state(state) {}

  void operator()(std::shared_ptr<context::Context<Rnd>> ctx) const {
    ctx->renderer()->command(
        {m_state ? COMMAND_INVERT_ON : COMMAND_INVERT_OFF});
  }
};

template <typename Rnd>
  requires render::IsRenderer<Rnd>
class SetEntireDisplay {
 public:
  static inline constexpr uint8_t COMMAND_ENTIRE_DISPLAY_ON = 0xA5;
  static inline constexpr uint8_t COMMAND_ENTIRE_DISPLAY_OFF = 0xA4;

 private:
  bool m_state;

 public:
  explicit SetEntireDisplay(bool state) : m_state(state) {}

  void operator()(std::shared_ptr<context::Context<Rnd>> ctx) const {
    ctx->renderer()->command(
        {m_state ? COMMAND_ENTIRE_DISPLAY_ON : COMMAND_ENTIRE_DISPLAY_OFF});
  }
};

}  // namespace ssdui::command::fundamental
