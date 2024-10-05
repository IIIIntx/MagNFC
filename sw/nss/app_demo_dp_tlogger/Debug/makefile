################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include mods/tmeas/subdir.mk
-include mods/storage/subdir.mk
-include mods/ndeft2t/subdir.mk
-include mods/msg/subdir.mk
-include mods/event/subdir.mk
-include mods/compress/heatshrink/subdir.mk
-include mods/compress/subdir.mk
-include mods/batimp/subdir.mk
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


BUILD_ARTIFACT_NAME := app_demo_dp_tlogger
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: app_demo_dp_tlogger.axf

dependents:
	-cd D:/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/lib_board_dp/Release && $(MAKE) clean all
	-cd D:/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/lib_chip_nss/Release && $(MAKE) clean all

# Tool invocations
app_demo_dp_tlogger.axf: $(OBJS) $(USER_OBJS) D:/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/lib_board_dp/Release/liblib_board_dp.a D:/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/lib_chip_nss/Release/liblib_chip_nss.a makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\Release" -L"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\Release" -Xlinker -Map="app_demo_dp_tlogger.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0plus -mthumb -T app_demo_dp_tlogger_Debug.ld -o "app_demo_dp_tlogger.axf" $(OBJS) $(USER_OBJS) $(LIBS) -llib_board_dp -llib_chip_nss
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) app_demo_dp_tlogger.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size --totals $(OBJS) ; arm-none-eabi-size "app_demo_dp_tlogger.axf" ; arm-none-eabi-objcopy -v -O binary "app_demo_dp_tlogger.axf" "app_demo_dp_tlogger.bin" ; arm-none-eabi-objcopy -v -O ihex "app_demo_dp_tlogger.axf" "app_demo_dp_tlogger.hex" ; # checksum -p NHS3100 -d "app_demo_dp_tlogger.bin"
	-@echo ' '

.PHONY: all clean dependents main-build post-build
D:/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/lib_board_dp/Release/liblib_board_dp.a:
D:/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/lib_chip_nss/Release/liblib_chip_nss.a:

-include ../makefile.targets
