################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/Src/gpio.c \
../Peripherals/Src/rcc.c \
../Peripherals/Src/timer3.c 

OBJS += \
./Peripherals/Src/gpio.o \
./Peripherals/Src/rcc.o \
./Peripherals/Src/timer3.o 

C_DEPS += \
./Peripherals/Src/gpio.d \
./Peripherals/Src/rcc.d \
./Peripherals/Src/timer3.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/Src/gpio.o: ../Peripherals/Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/Timer Interrupt/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/Timer Interrupt/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/Timer Interrupt/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/rcc.o: ../Peripherals/Src/rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/Timer Interrupt/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/Timer Interrupt/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/Timer Interrupt/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/rcc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/timer3.o: ../Peripherals/Src/timer3.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/Timer Interrupt/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/Timer Interrupt/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/Timer Interrupt/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/timer3.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

