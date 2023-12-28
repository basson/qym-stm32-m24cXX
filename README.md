# qym-stm32-m24cXX

Stm32 HAL use m24cXX  EEPROM Read/Write Library

#### Example

```cpp
struct ExMem
{
    uint8_t intValue = 10;
    float floatValue = 23.33;
    char str[10] = "Simple";
} exMem;

// Starting address to write/read
uin16_t exMemAddr = 32;

qymos::driver::m24cxx eeprom;

// Set HAL i2c handle struct
eeprom.SetPort(&hi2c2);
// Set i2c eeprom address
eeprom.SetAddress(0xA0);

// Write structure to eeprom
eeprom.WriteData(exMemAddr, (uint8_t*)&exMem, sizeof(ExMem), 100);
// Read structure to eeprom
eeprom.ReadData(exMemAddr, (uint8_t*)&exMem, sizeof(ExMem), 100);

```
