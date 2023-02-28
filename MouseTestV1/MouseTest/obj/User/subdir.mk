################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v20x_it.c \
../User/lcd.c \
../User/main.c \
../User/mousecontrol.c \
../User/system_ch32v20x.c 

OBJS += \
./User/ch32v20x_it.o \
./User/lcd.o \
./User/main.o \
./User/mousecontrol.o \
./User/system_ch32v20x.o 

C_DEPS += \
./User/ch32v20x_it.d \
./User/lcd.d \
./User/main.d \
./User/mousecontrol.d \
./User/system_ch32v20x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\MRS_DATA\workspace\MouseTest\Debug" -I"C:\MRS_DATA\workspace\MouseTest\Core" -I"C:\MRS_DATA\workspace\MouseTest\User" -I"C:\MRS_DATA\workspace\MouseTest\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

