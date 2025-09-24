#ifndef I2CHANDLER_HPP
#define I2CHANDLER_HPP

#include <string>
#include <cstdint>

class I2CHandler
{
public:
    I2CHandler(uint32_t bus, uint8_t i2cAddress);
    ~I2CHandler();
    bool openBus();
    void closeBus();
    bool readBlock(uint8_t cmd, void* dst, uint32_t size) const;

private:
    bool checkConnection();

private:
    const uint8_t m_mcuI2cAddress {0};
    const std::string m_i2cFilepath {};
    int32_t m_i2cBus {-1};
};

#endif // I2CHANDLER_HPP
