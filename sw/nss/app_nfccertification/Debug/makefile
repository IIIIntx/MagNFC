################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := app_nfccertification
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: app_nfccertification.axf

# Tool invocations
app_nfccertification.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\Debug" -L"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\Debug" -Xlinker -Map="app_nfccertification.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0plus -mthumb -T app_nfccertification_Debug.ld -o "app_nfccertification.axf" $(OBJS) $(USER_OBJS) $(LIBS) -llib_board_dp -llib_chip_nss
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) app_nfccertification.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "app_nfccertification.axf" ; arm-none-eabi-objcopy -v -O binary "app_nfccertification.axf" "app_nfccertification.bin" ; arm-none-eabi-objcopy -v -O ihex "app_nfccertification.axf" "app_nfccertification.hex" ; # checksum -p NHS3100 -d "app_nfccertification.bin"
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
