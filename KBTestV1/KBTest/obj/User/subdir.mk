################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v20x_it.c \
../User/kbcontrol.c \
../User/lcd.c \
../User/main.c \
../User/system_ch32v20x.c 

OBJS += \
./User/ch32v20x_it.o \
./User/kbcontrol.o \
./User/lcd.o \
./User/main.o \
./User/system_ch32v20x.o 

C_DEPS += \
./User/ch32v20x_it.d \
./User/kbcontrol.d \
./User/lcd.d \
./User/main.d \
./User/system_ch32v20x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\MRS_DATA\workspace\KBTest\Debug" -I"C:\MRS_DATA\workspace\KBTest\Core" -I"C:\MRS_DATA\workspace\KBTest\User" -I"C:\MRS_DATA\workspace\KBTest\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

