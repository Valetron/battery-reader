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

    template<typename OStream>
    friend OStream& operator<<(OStream& os, const BatteryInfo& to_log)
    {
        fmt::format_to(std::ostream_iterator<char>(os), "\nTemperature - {} K", to_log.Temperature);
        fmt::format_to(std::ostream_iterator<char>(os), "\nRemainingCapacity - {} mAh", to_log.RemainingCapacity);
        fmt::format_to(std::ostream_iterator<char>(os), "\nFullChargeCapacity - {} mAh", to_log.FullChargeCapacity);
        fmt::format_to(std::ostream_iterator<char>(os), "\nStateOfCharge - {} %", to_log.StateOfCharge);
        fmt::format_to(std::ostream_iterator<char>(os), "\nChargingCurrent - {} mA", to_log.ChargingCurrent);
        fmt::format_to(std::ostream_iterator<char>(os), "\nChargingVoltage - {} mV", to_log.ChargingVoltage);
        fmt::format_to(std::ostream_iterator<char>(os), "\nAverageCurrent - {} mA", to_log.AverageCurrent);
        fmt::format_to(std::ostream_iterator<char>(os), "\nVoltage - {} mV", to_log.Voltage);
        fmt::format_to(std::ostream_iterator<char>(os), "\nCycleCount - {}", to_log.CycleCount);
        fmt::format_to(std::ostream_iterator<char>(os), "\nDesignCapacity - {} mAh", to_log.DesignCapacity);
        fmt::format_to(std::ostream_iterator<char>(os), "\nDesignVoltage - {} mV", to_log.DesignVoltage);
        fmt::format_to(std::ostream_iterator<char>(os), "\nManufactureDate - {}", FormatDate(to_log.ManufactureDate));
        fmt::format_to(std::ostream_iterator<char>(os), "\nSerialNumber - {}", to_log.SerialNumber);
        fmt::format_to(std::ostream_iterator<char>(os), "\nManufacturerName - {}", to_log.ManufacturerName);
        fmt::format_to(std::ostream_iterator<char>(os), "\nDeviceName - {}", to_log.DeviceName);
        fmt::format_to(std::ostream_iterator<char>(os), "\nDeviceChemistry - {}", to_log.DeviceChemistry);

        return os;
    }
};


#endif // BATTERY_HPP
