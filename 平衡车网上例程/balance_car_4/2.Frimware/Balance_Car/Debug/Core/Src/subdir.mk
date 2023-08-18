################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Data_to_Matlab.c \
../Core/Src/Get_digits.c \
../Core/Src/PID.c \
../Core/Src/Speed_Ring_PID.c \
../Core/Src/encoder.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/jy61.c \
../Core/Src/key.c \
../Core/Src/main.c \
../Core/Src/motor.c \
../Core/Src/oled.c \
../Core/Src/oledshow.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/Data_to_Matlab.o \
./Core/Src/Get_digits.o \
./Core/Src/PID.o \
./Core/Src/Speed_Ring_PID.o \
./Core/Src/encoder.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/jy61.o \
./Core/Src/key.o \
./Core/Src/main.o \
./Core/Src/motor.o \
./Core/Src/oled.o \
./Core/Src/oledshow.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/Data_to_Matlab.d \
./Core/Src/Get_digits.d \
./Core/Src/PID.d \
./Core/Src/Speed_Ring_PID.d \
./Core/Src/encoder.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/jy61.d \
./Core/Src/key.d \
./Core/Src/main.d \
./Core/Src/motor.d \
./Core/Src/oled.d \
./Core/Src/oledshow.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Data_to_Matlab.d ./Core/Src/Data_to_Matlab.o ./Core/Src/Data_to_Matlab.su ./Core/Src/Get_digits.d ./Core/Src/Get_digits.o ./Core/Src/Get_digits.su ./Core/Src/PID.d ./Core/Src/PID.o ./Core/Src/PID.su ./Core/Src/Speed_Ring_PID.d ./Core/Src/Speed_Ring_PID.o ./Core/Src/Speed_Ring_PID.su ./Core/Src/encoder.d ./Core/Src/encoder.o ./Core/Src/encoder.su ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/jy61.d ./Core/Src/jy61.o ./Core/Src/jy61.su ./Core/Src/key.d ./Core/Src/key.o ./Core/Src/key.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motor.d ./Core/Src/motor.o ./Core/Src/motor.su ./Core/Src/oled.d ./Core/Src/oled.o ./Core/Src/oled.su ./Core/Src/oledshow.d ./Core/Src/oledshow.o ./Core/Src/oledshow.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

