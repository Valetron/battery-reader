#ifndef BATTERYHANDLER_HPP
#define BATTERYHANDLER_HPP

#include <memory>
#include <functional>
#include <type_traits>

#include <spdlog/spdlog.h>

#include "batteryProtocol.hpp"
#include "I2CHandler.hpp"
#include "battery.hpp"

namespace
{
const auto s_maxArrSize = 21;
}

class BatteryHandler
{
public:
    BatteryHandler(uint32_t bus, uint8_t i2cAddress);
    void getInfo();

private:

    template <typename T, uint32_t TSize = (true == std::is_trivial_v<T>) ? sizeof(T) : 0>
    requires ((std::is_trivial_v<T> || std::is_same_v<T, std::string>) && TSize > 0 && TSize <= s_maxArrSize && TSize <= (true == (std::is_trivial_v<T>) ? sizeof(T) : s_maxArrSize ))
    std::pair<bool, T> ReadDataBlock(TBatteryCommands cmd)
    {
        std::array<uint8_t, s_maxArrSize> blockData {};
        bool result = m_i2c->readBlock(uint8_t(cmd), blockData.data(), TSize);
        if (result)
        {
            if constexpr (std::is_same_v<T, std::string>)
            {
                const auto length = blockData.at(0);
                if (length > TSize)
                {
                    return std::make_pair(false, T{});
                }
                return std::make_pair(true, std::string(reinterpret_cast<const char*>(std::next(blockData.cbegin())), length));
            }
            else if constexpr (std::is_same_v<T, uint16_t> || std::is_same_v<T, int16_t>)
            {
                return std::make_pair(true, ((blockData.at(1) << 8) | blockData.at(0)));
            }
        }
        else
        {
            SPDLOG_ERROR("Error reading cmd = {}", static_cast<uint32_t>(cmd));
            if constexpr (std::is_same_v<T, std::string>)
            {
                return std::make_pair(false, T{});
            }
            else if constexpr (std::is_same_v<T, uint16_t>)
            {
                return std::make_pair(false, std::numeric_limits<T>::max());
            }
        }
        SPDLOG_ERROR("Unexpected type");
        return std::make_pair(false, T{});
    }

    template <typename T, uint32_t TSize = (std::is_trivial_v<T> == true) ? sizeof(T) : 0>
    bool UpdateParam(TBatteryCommands cmd, T& param, std::function<T(const T&)>&& formula = [] (const T& val) { return val; })
    {
        bool isChanged = false;
        const auto&& [result, value] = ReadDataBlock<T, TSize>(cmd);
        if (result)
        {
            auto calculated = formula(value);
            if (param != calculated)
            {
                param = calculated;
                isChanged = true;
            }
        }
        return isChanged;
    }

private:
    BatteryInfo m_battery;
    std::unique_ptr<I2CHandler> m_i2c {nullptr};
};

#endif // BATTERYHANDLER_HPP
