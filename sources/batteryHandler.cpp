#include "batteryHandler.hpp"

BatteryHandler::BatteryHandler(uint32_t bus, uint8_t i2cAddress)
    : m_i2c{new I2CHandler(bus, i2cAddress)}
{
}

void BatteryHandler::getInfo()
{
    bool successful {false};
    successful |= UpdateParam<std::string, TParamLimits::NameLength>(TBatteryCommands::ManufacturerName, m_battery.ManufacturerName);
    successful |= UpdateParam<std::string, TParamLimits::NameLength>(TBatteryCommands::DeviceName, m_battery.DeviceName);
    successful |= UpdateParam<std::string, TParamLimits::ChemistryLength>(TBatteryCommands::DeviceChemistry, m_battery.DeviceChemistry);
    successful |= UpdateParam<uint16_t>(TBatteryCommands::DesignCapacity, m_battery.DesignCapacity);
    successful |= UpdateParam<uint16_t>(TBatteryCommands::DesignVoltage, m_battery.DesignVoltage);
    successful |= UpdateParam<uint16_t>(TBatteryCommands::ManufactureDate, m_battery.ManufactureDate);
    successful |= UpdateParam<uint16_t>(TBatteryCommands::FullChargeCapacity, m_battery.FullChargeCapacity);
    successful |= UpdateParam<uint16_t>(TBatteryCommands::StateOfCharge, m_battery.StateOfCharge);
    UpdateParam<uint16_t>(TBatteryCommands::Temperature, m_battery.Temperature, [] (const auto& value) { return static_cast<uint16_t>(value / 10); });
    UpdateParam<uint16_t>(TBatteryCommands::RemainingCapacity, m_battery.RemainingCapacity);
    UpdateParam<uint16_t>(TBatteryCommands::ChargingCurrent, m_battery.ChargingCurrent);
    UpdateParam<uint16_t>(TBatteryCommands::ChargingVoltage, m_battery.ChargingVoltage);
    UpdateParam<int16_t>(TBatteryCommands::AverageCurrent, m_battery.AverageCurrent);
    UpdateParam<uint16_t>(TBatteryCommands::Voltage, m_battery.Voltage, [] (const auto& value) { return std::numeric_limits<uint16_t>::max() - value; });
    successful |= UpdateParam<uint16_t>(TBatteryCommands::CycleCount, m_battery.CycleCount);

    if (!successful)
    {
        SPDLOG_ERROR("Failed to read params");
        return;
    }

    SPDLOG_INFO("Battery info: \n{}", m_battery);
}
