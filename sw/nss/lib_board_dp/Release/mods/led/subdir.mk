################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/mods/led/led.c 

C_DEPS += \
./mods/led/led.d 

OBJS += \
./mods/led/led.o 


# Each subdirectory must supply rules for building sources it contributes
mods/led/led.o: D:/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/mods/led/led.c mods/led/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c99 -D__REDLIB__ -DNDEBUG -D__CODE_RED -DCORE_M0PLUS -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\inc" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\mods" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\inc" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\mods" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\mods" -include"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\mods\chip_sel.h" -include"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\mods\board_sel.h" -Os -gdwarf-4 -pedantic -Wall -Wextra -Wconversion -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-mods-2f-led

clean-mods-2f-led:
	-$(RM) ./mods/led/led.d ./mods/led/led.o

.PHONY: clean-mods-2f-led

