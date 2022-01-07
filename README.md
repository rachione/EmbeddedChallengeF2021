# EmbeddedChallengeF2021

## Abstract
Built a wearable speedometer which can calculate velocity by measuring angular velocities available from the built-in gyroscope (L3GD20) - without a GPS or an accelerometer. In addition, I have achieved seamless data accessibility by implementing the UI system, so that users can record and extract their walking data in any place. 
## Method
- GYRO_DISCO_F429ZI - It drives the Gyroscope on the board, which only works on L3GD20, but the Gyroscope on STM32F429ZI discovery is I3G4250D. Hence, I have modified all the Gyroscope structures and functions in the driver libraries, by replacing the L3GD20 model with the I3G4250D model.
- TS_DISCO_F429ZI - It drives the touch screen module on the board.
- LCD_DISCO_F429ZI - It drives the LCD display on the board.

For data storage, I choose to store data in the flash memory (sectors 5-6) using the TDBStore class, which is the Key-Value storage over a block device. So that the device can store and extract data easily. 

For power supply, I have connected VCC and GND pin to the 9V battery with a 5V Linear Voltage Regulator (L7805CV).
![alt text](https://github.com/rachione/EmbeddedChallengeF2021/blob/main/1.jpg?raw=true)
