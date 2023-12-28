#pragma once

#include "stdint.h"

#include "stm32f1xx_hal.h"

namespace qymos
{
    namespace driver
    {
        /**
         * @brief M24 Write/Read any data
         *
         */
        class M24cxx
        {
        private:
            uint8_t _address = 0xA0;     ///< I2c address
            I2C_HandleTypeDef *_i2cPort; ///< I2c HAL handle struct

        public:
            /**
             * @brief Set the HAL handle i2c struct
             *
             * @param i2cPort HAL handle i2c struct
             */
            void SetPort(I2C_HandleTypeDef *i2cPort);
            /**
             * @brief Set the i2c Address m24cxx
             *
             * @param address i2c address
             */
            void SetAddress(uint8_t address);

            /**
             * @brief Initiailize driver
             *
             * @return true Done
             * @return false Error
             */
            bool Initialize();
            /**
             * @brief De initialize driver
             *
             * @return true Done
             * @return false Error
             */
            bool DeInitialize();
            /**
             * @brief Write any data
             *
             * @param address Address to start write
             * @param data Data
             * @param len  Length data
             * @param delayUs Delay write us
             * @return true Done
             * @return false Error
             */
            bool WriteData(uint16_t address, uint8_t *data, uint16_t len, uint16_t delayUs = 0);
            /**
             * @brief Read any data
             *
             * @param address Address to start read
             * @param data Data
             * @param len Length data
             * @param delayUs Delay read us
             * @return true Done
             * @return false Error
             */
            bool ReadData(uint16_t address, uint8_t *data, uint16_t len, uint16_t delayUs = 0);
        };
        
    } // namespace driver

} // namespace qymos
