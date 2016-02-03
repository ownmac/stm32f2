################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

C_SRCS += \
../startup/sysmem.c \
../startup/system_stm32f30x.c 

OBJS += \
./startup/startup_stm32.o \
./startup/sysmem.o \
./startup/system_stm32f30x.o 

C_DEPS += \
./startup/sysmem.d \
./startup/system_stm32f30x.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo %cd%
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -I"C:/Users/Dove/STM32/demo1/inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -DSTM32F3DISCOVERY -DSTM32F303VCTx -DSTM32F3 -DSTM32 -DSTM32F30 -DDEBUG -I"C:/Users/Dove/STM32/demo1/inc" -I"C:/Users/Dove/STM32/demo1/FreeRTOS/include" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


