#include <Arduino.h>

#include <cstdint>
#include <memory>
#include <ssdui/all.hh>
#include <vector>

#include "esp32-hal-gpio.h"

void setup() {
  using SSDrvConfig = ssdui::context::Config;

  using SSDrvRenderer = ssdui::render::DefaultRenderer;
  // using SSDrvBuilder = ssdui::context::ContextBuilder<SSDrvRenderer>;
  using SSDrvContext = ssdui::context::Context<SSDrvRenderer>;
  using SSDrvInitializer =
      ssdui::command::initializer::DefaultInitializer<SSDrvRenderer>;

  Serial.begin(115200);

  // auto ctx = SSDrvBuilder()
  //                .config(SSDrvConfig())
  //                .renderer(std::make_unique<SSDrvRenderer>(&Wire, 0x3C))
  //                .build();
  // auto ctx = std::make_unique<SSDrvContext>(
  //     SSDrvConfig(), std::make_unique<SSDrvRenderer>(&Wire, 0x3C));

  // ctx->run(SSDrvInitializer());

  // // get current time
  // auto now = std::chrono::system_clock::now();

  // // const auto data = std::vector<uint8_t>(128 * 8, 0xFF);

  // // // fill blank screen for many times
  // for (int i = 0; i < 100; i++) {
  //   if (i % 2 == 0)
  //     ctx->renderer()->data(std::vector<uint8_t>(128 * 8, 0x00));
  //   else
  //     ctx->renderer()->data(std::vector<uint8_t>(128 * 8, 0xFF));

  //   delay(1000);
  // }

  // // // get elapsed time
  // auto elapsed = std::chrono::system_clock::now() - now;

  // // // print elapsed time
  // Serial.print("Elapsed time: ");
  // Serial.println(
  //     std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count());
}

void loop() { delay(100); }
