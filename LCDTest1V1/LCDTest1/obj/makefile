################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
LCDTest1.hex \

SECONDARY_LIST += \
LCDTest1.lst \

SECONDARY_SIZE += \
LCDTest1.siz \


# All Target
all: LCDTest1.elf secondary-outputs

# Tool invocations
LCDTest1.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "C:\MRS_DATA\workspace\LCDTest1\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"LCDTest1.map" --specs=nano.specs --specs=nosys.specs -o "LCDTest1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
LCDTest1.hex: LCDTest1.elf
	@	riscv-none-embed-objcopy -O ihex "LCDTest1.elf"  "LCDTest1.hex"
	@	@
LCDTest1.lst: LCDTest1.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "LCDTest1.elf" > "LCDTest1.lst"
	@	@
LCDTest1.siz: LCDTest1.elf
	@	riscv-none-embed-size --format=berkeley "LCDTest1.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) LCDTest1.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
