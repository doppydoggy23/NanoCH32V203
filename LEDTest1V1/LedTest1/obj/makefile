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
LedTest1.hex \

SECONDARY_LIST += \
LedTest1.lst \

SECONDARY_SIZE += \
LedTest1.siz \


# All Target
all: LedTest1.elf secondary-outputs

# Tool invocations
LedTest1.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "C:\MRS_DATA\workspace\LedTest1\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"LedTest1.map" --specs=nano.specs --specs=nosys.specs -o "LedTest1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
LedTest1.hex: LedTest1.elf
	@	riscv-none-embed-objcopy -O ihex "LedTest1.elf"  "LedTest1.hex"
	@	@
LedTest1.lst: LedTest1.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "LedTest1.elf" > "LedTest1.lst"
	@	@
LedTest1.siz: LedTest1.elf
	@	riscv-none-embed-size --format=berkeley "LedTest1.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) LedTest1.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
