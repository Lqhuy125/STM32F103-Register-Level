################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/Src/gpio.c \
../Peripherals/Src/rcc.c 

OBJS += \
./Peripherals/Src/gpio.o \
./Peripherals/Src/rcc.o 

C_DEPS += \
./Peripherals/Src/gpio.d \
./Peripherals/Src/rcc.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/Src/gpio.o: ../Peripherals/Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/Register/STM32F103-Register-Level/2.EXTI_BUTTON/Peripherals/Inc" -I"D:/Users/Desktop/Learn/Register/STM32F103-Register-Level/2.EXTI_BUTTON/CMSIS/Include" -I"D:/Users/Desktop/Learn/Register/STM32F103-Register-Level/2.EXTI_BUTTON/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/rcc.o: ../Peripherals/Src/rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/Register/STM32F103-Register-Level/2.EXTI_BUTTON/Peripherals/Inc" -I"D:/Users/Desktop/Learn/Register/STM32F103-Register-Level/2.EXTI_BUTTON/CMSIS/Include" -I"D:/Users/Desktop/Learn/Register/STM32F103-Register-Level/2.EXTI_BUTTON/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/rcc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

