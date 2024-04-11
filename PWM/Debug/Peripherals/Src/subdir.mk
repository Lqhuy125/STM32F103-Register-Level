################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/Src/adc.c \
../Peripherals/Src/gpio.c \
../Peripherals/Src/interrupt_timer.c \
../Peripherals/Src/pwm.c \
../Peripherals/Src/rcc.c 

OBJS += \
./Peripherals/Src/adc.o \
./Peripherals/Src/gpio.o \
./Peripherals/Src/interrupt_timer.o \
./Peripherals/Src/pwm.o \
./Peripherals/Src/rcc.o 

C_DEPS += \
./Peripherals/Src/adc.d \
./Peripherals/Src/gpio.d \
./Peripherals/Src/interrupt_timer.d \
./Peripherals/Src/pwm.d \
./Peripherals/Src/rcc.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/Src/adc.o: ../Peripherals/Src/adc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/PWM/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/PWM/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/PWM/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/adc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/gpio.o: ../Peripherals/Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/PWM/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/PWM/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/PWM/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/interrupt_timer.o: ../Peripherals/Src/interrupt_timer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/PWM/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/PWM/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/PWM/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/interrupt_timer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/pwm.o: ../Peripherals/Src/pwm.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/PWM/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/PWM/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/PWM/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/pwm.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Peripherals/Src/rcc.o: ../Peripherals/Src/rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Users/Desktop/Learn/STM32 code/PWM/CMSIS/Include" -I"D:/Users/Desktop/Learn/STM32 code/PWM/Core/Inc" -I"D:/Users/Desktop/Learn/STM32 code/PWM/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Peripherals/Src/rcc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

