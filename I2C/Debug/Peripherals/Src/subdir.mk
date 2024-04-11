################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/Src/gpio.c \
../Peripherals/Src/i2c.c \
../Peripherals/Src/lcd.c \
../Peripherals/Src/rcc.c \
../Peripherals/Src/uart2.c 

OBJS += \
./Peripherals/Src/gpio.o \
./Peripherals/Src/i2c.o \
./Peripherals/Src/lcd.o \
./Peripherals/Src/rcc.o \
./Peripherals/Src/uart2.o 

C_DEPS += \
./Peripherals/Src/gpio.d \
./Peripherals/Src/i2c.d \
./Peripherals/Src/lcd.d \
./Peripherals/Src/rcc.d \
./Peripherals/Src/uart2.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/Src/gpio.o: ../Peripherals/Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/I2C/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/I2C/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/I2C/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/i2c.o: ../Peripherals/Src/i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/I2C/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/I2C/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/I2C/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/i2c.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/lcd.o: ../Peripherals/Src/lcd.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/I2C/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/I2C/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/I2C/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/rcc.o: ../Peripherals/Src/rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/I2C/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/I2C/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/I2C/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/rcc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/uart2.o: ../Peripherals/Src/uart2.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/I2C/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/I2C/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/I2C/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/uart2.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

