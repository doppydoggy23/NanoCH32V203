################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v20x_it.c \
../User/lcd.c \
../User/main.c \
../User/system_ch32v20x.c 

S_UPPER_SRCS += \
../User/myasm.S 

OBJS += \
./User/ch32v20x_it.o \
./User/lcd.o \
./User/main.o \
./User/myasm.o \
./User/system_ch32v20x.o 

S_UPPER_DEPS += \
./User/myasm.d 

C_DEPS += \
./User/ch32v20x_it.d \
./User/lcd.d \
./User/main.d \
./User/system_ch32v20x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\MRS_DATA\workspace\asmpong\Debug" -I"C:\MRS_DATA\workspace\asmpong\Core" -I"C:\MRS_DATA\workspace\asmpong\User" -I"C:\MRS_DATA\workspace\asmpong\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
User/%.o: ../User/%.S
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"C:\MRS_DATA\workspace\asmpong\Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

