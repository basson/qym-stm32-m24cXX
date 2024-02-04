#include "../include/drivers/m24cxx.hpp"

namespace qymos
{
    namespace driver
    {
        void M24cxx::SetPort(I2C_HandleTypeDef *i2cPort)
        {
            _i2cPort = i2cPort;
        }
        void M24cxx::SetAddress(uint8_t address)
        {
            _address = address;
        }
        bool M24cxx::Initialize()
        {
            return true;
        }
        bool M24cxx::DeInitialize()
        {
            return true;
        }
        bool M24cxx::WriteData(uint16_t address, uint8_t *data, uint16_t len, uint16_t delayUs)
        {
            uint32_t historySpeed = _i2cPort->Init.ClockSpeed;
            _i2cPort->Init.ClockSpeed = 100000;
            HAL_I2C_Init(_i2cPort);

            if (!delayUs)
                delayUs = (uint16_t)HAL_MAX_DELAY;

            uint8_t blockStart = 0;
            uint8_t blockSize = 32;
            while (len > 0)
            {
                if (len < 32)
                    blockSize = len;
                if (HAL_I2C_Mem_Write(_i2cPort, _address, address, I2C_MEMADD_SIZE_16BIT, data + blockStart, blockSize, delayUs) != HAL_OK)
                    return false;
                HAL_Delay(10);
                if (len < 32)
                    break;
                blockStart += 32;
                len -= 32;
                address += 32;
            }
            _i2cPort->Init.ClockSpeed = historySpeed;
            HAL_I2C_Init(_i2cPort);
            return true;
        }
        bool M24cxx::ReadData(uint16_t address, uint8_t *data, uint16_t len, uint16_t delayUs)
        {
            uint8_t waitTry = 3;
            HAL_StatusTypeDef status;
            bool ret = false;

            if (!delayUs)
                delayUs = (uint16_t)HAL_MAX_DELAY;

            for (;;)
            {
                status = HAL_I2C_IsDeviceReady(_i2cPort, _address, 1, delayUs);
                if (status == HAL_OK)
                    break;
                else
                {
                    waitTry--;
                    if (waitTry <= 0)
                        return false;
                }
            }
            uint32_t historySpeed = _i2cPort->Init.ClockSpeed;
            _i2cPort->Init.ClockSpeed = 100000;
            HAL_I2C_Init(_i2cPort);
            if (HAL_I2C_Mem_Read(_i2cPort, _address, address, I2C_MEMADD_SIZE_16BIT, data, len, delayUs) == HAL_OK)
            {
                ret = true;
            }
            _i2cPort->Init.ClockSpeed = historySpeed;
            HAL_I2C_Init(_i2cPort);
            return ret;
        }
        
    } // namespace driver

} // namespace qymos
