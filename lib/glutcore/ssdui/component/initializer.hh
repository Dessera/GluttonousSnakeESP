#pragma once

#include <memory>

#include "esp32-hal.h"
#include "ssdui/component/address.hh"
#include "ssdui/component/fundamental.hh"
#include "ssdui/component/hardware.hh"
#include "ssdui/context/config.hh"
#include "ssdui/context/core.hh"

namespace ssdui::command::initializer {

template <typename Rnd>
  requires render::IsRenderer<Rnd>
class DefaultInitializer {
 public:
  static inline constexpr uint8_t INIT_DELAY = 100;

  void operator()(std::shared_ptr<context::Context<Rnd>> ctx) const {
    using namespace command;
    const context::Config& cfg = ctx->config();

    delay(INIT_DELAY);

    ctx->run(fundamental::SetDisplay<Rnd>(false))
        ->run(hardware::SetClockRatioAndFrequency<Rnd>(cfg.clock_ratio,
                                                       cfg.clock_frequency))
        ->run(hardware::SetMultiplexRatio<Rnd>(cfg.multiplex_ratio))
        ->run(hardware::SetDisplayOffset<Rnd>(cfg.display_offset))
        ->run(address::SetAddressingMode<Rnd>(cfg.addressing_mode))
        ->run(hardware::SetDisplayStartLine<Rnd>(cfg.start_line))
        ->run(hardware::SetSegmentRemap<Rnd>(cfg.horizontal_flip))
        ->run(hardware::SetComOutputScanDirection<Rnd>(cfg.vertical_flip))
        ->run(hardware::SetComPinsHardwareConfiguration<Rnd>(cfg.com_pins))
        ->run(hardware::SetPrechargePeriod<Rnd>(cfg.precharge_phase1,
                                                cfg.precharge_phase2))
        ->run(hardware::SetVCOMH<Rnd>(cfg.vcomh_level))
        ->run(fundamental::SetEntireDisplay<Rnd>(cfg.entire_display_on))
        ->run(fundamental::SetInvert<Rnd>(cfg.inverse_display))
        ->run(hardware::SetChargePump<Rnd>(cfg.charge_pump_enable))
        ->run(address::SetPageAddress<Rnd>(cfg.page_start, cfg.page_end))
        ->run(address::SetColumnAddress<Rnd>(cfg.column_start, cfg.column_end))
        ->run(fundamental::SetDisplay<Rnd>(cfg.display_on));
  }
};

}  // namespace ssdui::command::initializer