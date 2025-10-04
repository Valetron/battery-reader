#ifndef BATTERY_HPP
#define BATTERY_HPP

#include <string>
#include <cstdint>

#include <spdlog/fmt/ostr.h>

namespace
{
std::string FormatDate(uint16_t date)
{
    const uint8_t day = (date >> 12) & 0x0F;
    const uint8_t month = (date >> 8) & 0x0F;
    const uint8_t year = date & 0xFF;
    const uint16_t yearRes = year + 1980;

    std::string res {std::to_string(day)
                        .append(".")
                        .append(std::to_string(month))
                        .append(".")
                        .append(std::to_string(yearRes))};

    return res;
}
}

struct BatteryInfo
{
    uint16_t Temperature {0};
    uint16_t RemainingCapacity {0};
    uint16_t FullChargeCapacity {0};
    uint16_t StateOfCharge {0};
    uint16_t ChargingCurrent {0};
    uint16_t ChargingVoltage {0};
    int16_t AverageCurrent {0};
    uint16_t Voltage {0};
    uint16_t CycleCount {0};
    uint16_t DesignCapacity {0};
    uint16_t DesignVoltage {0};
    uint16_t ManufactureDate {0};
    uint16_t SerialNumber {0};
    std::string ManufacturerName {};
    std::string DeviceName {};
    std::string DeviceChemistry {};
};

template <>
struct fmt::formatter<BatteryInfo>
{
    constexpr auto parse(fmt::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const BatteryInfo& bat, FormatContext& ctx) const
    {
        fmt::format_to(ctx.out(), "Temperature - {} K", bat.Temperature);
        fmt::format_to(ctx.out(), "\nRemainingCapacity - {} mAh", bat.RemainingCapacity);
        fmt::format_to(ctx.out(), "\nFullChargeCapacity - {} mAh", bat.FullChargeCapacity);
        fmt::format_to(ctx.out(), "\nStateOfCharge - {} %", bat.StateOfCharge);
        fmt::format_to(ctx.out(), "\nChargingCurrent - {} mA", bat.ChargingCurrent);
        fmt::format_to(ctx.out(), "\nChargingVoltage - {} mV", bat.ChargingVoltage);
        fmt::format_to(ctx.out(), "\nAverageCurrent - {} mA", bat.AverageCurrent);
        fmt::format_to(ctx.out(), "\nVoltage - {} mV", bat.Voltage);
        fmt::format_to(ctx.out(), "\nCycleCount - {}", bat.CycleCount);
        fmt::format_to(ctx.out(), "\nDesignCapacity - {} mAh", bat.DesignCapacity);
        fmt::format_to(ctx.out(), "\nDesignVoltage - {} mV", bat.DesignVoltage);
        fmt::format_to(ctx.out(), "\nManufactureDate - {}", FormatDate(bat.ManufactureDate));
        fmt::format_to(ctx.out(), "\nSerialNumber - {}", bat.SerialNumber);
        fmt::format_to(ctx.out(), "\nManufacturerName - {}", bat.ManufacturerName);
        fmt::format_to(ctx.out(), "\nDeviceName - {}", bat.DeviceName);
        fmt::format_to(ctx.out(), "\nDeviceChemistry - {}", bat.DeviceChemistry);

        return ctx.out();
    }
};

#endif // BATTERY_HPP
