#include "ssdui/render/default.hh"

#ifdef ARDUINO

#include <cstddef>
#include <numeric>

namespace ssdui::render {

std::size_t DefaultRenderer::command(const std::vector<uint8_t>& data) {
  std::lock_guard<std::mutex> lock(m_mtx);
  std::size_t bytes = std::accumulate(
      data.begin(), data.end(), 0, [this](std::size_t acc, uint8_t byte) {
        m_wire->beginTransmission(m_address);
        m_wire->write(COMMAND_PREFIX);
        m_wire->write(byte);
        return acc + static_cast<std::size_t>(m_wire->endTransmission() == 0);
      });
  return bytes;
}

std::size_t DefaultRenderer::data(const std::vector<uint8_t>& data) {
  std::lock_guard<std::mutex> lock(m_mtx);
  std::size_t bytes = std::accumulate(
      data.begin(), data.end(), 0, [this](std::size_t acc, uint8_t byte) {
        m_wire->beginTransmission(m_address);
        m_wire->write(DATA_PREFIX);
        m_wire->write(byte);
        return acc + static_cast<std::size_t>(m_wire->endTransmission() == 0);
      });
  return bytes;
}

}  // namespace ssdui::render

#endif
