################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/Src/i2c.c \
../Peripherals/Src/rcc.c \
../Peripherals/Src/uart.c 

OBJS += \
./Peripherals/Src/i2c.o \
./Peripherals/Src/rcc.o \
./Peripherals/Src/uart.o 

C_DEPS += \
./Peripherals/Src/i2c.d \
./Peripherals/Src/rcc.d \
./Peripherals/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/Src/i2c.o: ../Peripherals/Src/i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/I2C_SOFT/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/I2C_SOFT/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/I2C_SOFT/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/i2c.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/rcc.o: ../Peripherals/Src/rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/I2C_SOFT/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/I2C_SOFT/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/I2C_SOFT/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/rcc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/uart.o: ../Peripherals/Src/uart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/I2C_SOFT/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/I2C_SOFT/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/I2C_SOFT/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/uart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

