################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/OneDrive\ -\ HKUST\ (Guangzhou)/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/mods/ndeft2t/ndeft2t.c 

C_DEPS += \
./mods/ndeft2t/ndeft2t.d 

OBJS += \
./mods/ndeft2t/ndeft2t.o 


# Each subdirectory must supply rules for building sources it contributes
mods/ndeft2t/ndeft2t.o: D:/OneDrive\ -\ HKUST\ (Guangzhou)/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/mods/ndeft2t/ndeft2t.c mods/ndeft2t/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c99 -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__REDLIB__ -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\inc" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\inc" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\mods" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_example_dp_ndeft2t\mods" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\mods" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\mods" -include"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\mods\chip_sel.h" -include"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\mods\board_sel.h" -include"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_example_dp_ndeft2t\mods\app_sel.h" -Og -g3 -gdwarf-4 -pedantic -Wall -Wextra -Wconversion -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-mods-2f-ndeft2t

clean-mods-2f-ndeft2t:
	-$(RM) ./mods/ndeft2t/ndeft2t.d ./mods/ndeft2t/ndeft2t.o

.PHONY: clean-mods-2f-ndeft2t

