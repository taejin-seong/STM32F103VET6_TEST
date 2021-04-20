################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hw/driver/led.c 

OBJS += \
./src/hw/driver/led.o 

C_DEPS += \
./src/hw/driver/led.d 


# Each subdirectory must supply rules for building sources it contributes
src/hw/driver/led.o: ../src/hw/driver/led.c src/hw/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -c -I"C:/STM32 Coding files/exam_fw103VET6/exam_arm/stm32f103ve_fw/src" -I"C:/STM32 Coding files/exam_fw103VET6/exam_arm/stm32f103ve_fw/src/ap" -I"C:/STM32 Coding files/exam_fw103VET6/exam_arm/stm32f103ve_fw/src/bsp" -I"C:/STM32 Coding files/exam_fw103VET6/exam_arm/stm32f103ve_fw/src/common" -I"C:/STM32 Coding files/exam_fw103VET6/exam_arm/stm32f103ve_fw/src/hw" -I"C:/STM32 Coding files/exam_fw103VET6/exam_arm/stm32f103ve_fw/src/lib" -I"C:/STM32 Coding files/exam_fw103VET6/exam_arm/stm32f103ve_fw/src/common/hw/include" -I"C:/STM32 Coding files/exam_fw103VET6/exam_arm/stm32f103ve_fw/src/common/core" -I"C:/STM32 Coding files/exam_fw103VET6/exam_arm/stm32f103ve_fw/src/lib/cube_f103ve/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/STM32 Coding files/exam_fw103VET6/exam_arm/stm32f103ve_fw/src/lib/cube_f103ve/Drivers/CMSIS/Include" -I"C:/STM32 Coding files/exam_fw103VET6/exam_arm/stm32f103ve_fw/src/lib/cube_f103ve/Drivers/STM32F1xx_HAL_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/driver/led.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

