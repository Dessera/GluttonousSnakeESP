#include <Arduino.h>

#include <memory>
#include <ssdui/all.hh>

void write_command(uint8_t cmd) {
  Wire.beginTransmission(0x3C);
  Wire.write(0x00);
  Wire.write(cmd);
  Wire.endTransmission();
}

void setup() {
  delay(100);

  using SSDrvConfig = ssdui::context::Config;
  using SSDrvRenderer = ssdui::render::DefaultRenderer;
  using SSDrvBuilder = ssdui::context::ContextBuilder<SSDrvRenderer>;
  using SSDrvInitializer =
      ssdui::command::initializer::DefaultInitializer<SSDrvRenderer>;

  auto ctx = SSDrvBuilder()
                 .config(SSDrvConfig())
                 .renderer(std::make_unique<SSDrvRenderer>(&Wire, 0x3C))
                 .build()
                 ->run(SSDrvInitializer());

  for (int i = 0; i < 128 * 8; i++) {
    ctx->renderer()->data({0xFF});
  }

  write_command(0x21);  // set column address
  write_command(0x00);  // column start address
  write_command(0x7F);  // column end address
  write_command(0x22);  // set page address
  write_command(0x00);  // page start address
  write_command(0x07);  // page end address

  for (int i = 0; i < 128 * 8; i++) {
    ctx->renderer()->data({0x00});
    delay(10);
  }
}

void loop() { delay(1000); }
