#include "I2CHandler.hpp"

extern "C"
{
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <i2c/smbus.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
}

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

I2CHandler::I2CHandler(uint32_t bus, uint8_t i2cAddress)
    : m_mcuI2cAddress(i2cAddress)
    , m_i2cFilepath(fmt::format("/dev/i2c-{}", bus))
{
}

I2CHandler::~I2CHandler()
{
    closeBus();
}

bool I2CHandler::openBus()
{
    m_i2cBus = open(m_i2cFilepath.c_str(), O_RDWR);
    if (m_i2cBus < 0)
    {
        SPDLOG_ERROR("Failed to open i2c bus");
        return false;
    }

    if (ioctl(m_i2cBus, I2C_SLAVE, m_mcuI2cAddress) < 0)
    {
        SPDLOG_ERROR("Failed to set mcu slave address");
        close(m_i2cBus);
        return false;
    }

    SPDLOG_DEBUG("Bus opened");

    return true;
}

void I2CHandler::closeBus()
{
    if(m_i2cBus >= 0)
    {
        close(m_i2cBus);
        m_i2cBus = -1;
    }

    SPDLOG_DEBUG("Bus closed");
}

bool I2CHandler::readBlock(uint8_t cmd, void* dst, uint32_t size) const
{
    if (!dst)
    {
        SPDLOG_ERROR("Null pointer");
        return false;
    }

    if (size > I2C_SMBUS_BLOCK_MAX)
    {
        SPDLOG_ERROR("Requested size {} > I2C_SMBUS_BLOCK_MAX", size);
        return false;
    }

    if (m_i2cBus < 0)
    {
        SPDLOG_ERROR("Attempt to read on closed bus");
        return false;
    }

    const auto readBytes = i2c_smbus_read_i2c_block_data(m_i2cBus, cmd, size, static_cast<uint8_t*>(dst));
    if ((readBytes < 0) || (readBytes != int(size)))
    {
        SPDLOG_ERROR("Error reading errno = {}", std::strerror(errno));
        return false;
    }

    return true;
}

bool I2CHandler::checkConnection()
{
    if (m_i2cBus < 0 && !openBus())
        return false;

    if (ioctl(m_i2cBus, I2C_SLAVE, m_mcuI2cAddress) < 0)
    {
        if (EBUSY == errno)
            return true;
        else
            SPDLOG_DEBUG("Error at address {}: ", m_mcuI2cAddress, std::strerror(errno));
    }

    return (i2c_smbus_read_byte(m_i2cBus) > 0);
}
