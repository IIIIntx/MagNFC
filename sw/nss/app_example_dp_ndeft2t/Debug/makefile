################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include mods/uarttx/subdir.mk
-include mods/ndeft2t/subdir.mk
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


BUILD_ARTIFACT_NAME := app_example_dp_ndeft2t
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: app_example_dp_ndeft2t.axf

dependents:
	-cd D:/OneDrive\ -\ HKUST\ (Guangzhou)/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/lib_board_dp/Debug && $(MAKE) all
	-cd D:/OneDrive\ -\ HKUST\ (Guangzhou)/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/lib_chip_nss/Debug && $(MAKE) all

# Tool invocations
app_example_dp_ndeft2t.axf: $(OBJS) $(USER_OBJS) D:/OneDrive\ -\ HKUST\ (Guangzhou)/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/lib_board_dp/Debug/liblib_board_dp.a D:/OneDrive\ -\ HKUST\ (Guangzhou)/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/lib_chip_nss/Debug/liblib_chip_nss.a makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\Debug" -L"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\Debug" -Xlinker -Map="app_example_dp_ndeft2t.map" -Xlinker --gc-sections -mcpu=cortex-m0plus -mthumb -T app_example_dp_ndeft2t_Debug.ld -o "app_example_dp_ndeft2t.axf" $(OBJS) $(USER_OBJS) $(LIBS) -llib_board_dp -llib_chip_nss
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) app_example_dp_ndeft2t.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "app_example_dp_ndeft2t.axf" ; arm-none-eabi-objcopy -v -O binary "app_example_dp_ndeft2t.axf" "app_example_dp_ndeft2t.bin" ; arm-none-eabi-objcopy -v -O ihex "app_example_dp_ndeft2t.axf" "app_example_dp_ndeft2t.hex" ; # checksum -p Generic_M0plus -d "app_example_dp_ndeft2t.bin"
	-@echo ' '

.PHONY: all clean dependents main-build post-build
D:/OneDrive\ -\ HKUST\ (Guangzhou)/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/lib_board_dp/Debug/liblib_board_dp.a:
D:/OneDrive\ -\ HKUST\ (Guangzhou)/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/lib_chip_nss/Debug/liblib_chip_nss.a:

-include ../makefile.targets
