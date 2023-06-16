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
cube3d.hex \

SECONDARY_LIST += \
cube3d.lst \

SECONDARY_SIZE += \
cube3d.siz \


# All Target
all: cube3d.elf secondary-outputs

# Tool invocations
cube3d.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "C:\MRS_DATA\workspace\cube3d\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"cube3d.map" --specs=nano.specs --specs=nosys.specs -o "cube3d.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
cube3d.hex: cube3d.elf
	@	riscv-none-embed-objcopy -O ihex "cube3d.elf"  "cube3d.hex"
	@	@
cube3d.lst: cube3d.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "cube3d.elf" > "cube3d.lst"
	@	@
cube3d.siz: cube3d.elf
	@	riscv-none-embed-size --format=berkeley "cube3d.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) cube3d.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
