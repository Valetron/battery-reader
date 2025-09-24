#ifndef BATTERYPROTOCOL_HPP
#define BATTERYPROTOCOL_HPP

#include <cstdint>

enum TParamLimits : uint32_t
{
    NameLength = 21,
    ChemistryLength = 5
};

enum class TBatteryCommands : uint8_t
{
    Temperature = 0x08,
    RemainingCapacity = 0x0F,
    FullChargeCapacity = 0x10,
    StateOfCharge = 0x0D,
    ChargingCurrent = 0x14,
    ChargingVoltage = 0x15,
    AverageCurrent = 0x0B,
    Voltage = 0x09,
    CycleCount = 0x17,
    DesignCapacity = 0x18,
    DesignVoltage = 0x19,
    ManufactureDate = 0x1B,
    SerialNumber = 0x1C,
    ManufacturerName = 0x20,
    DeviceName = 0x21,
    DeviceChemistry = 0x22
};

#endif // BATTERYPROTOCOL_HPP
