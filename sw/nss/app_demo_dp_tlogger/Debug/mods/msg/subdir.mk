################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/OneDrive\ -\ HKUST\ (Guangzhou)/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/mods/msg/msg.c 

C_DEPS += \
./mods/msg/msg.d 

OBJS += \
./mods/msg/msg.o 


# Each subdirectory must supply rules for building sources it contributes
mods/msg/msg.o: D:/OneDrive\ -\ HKUST\ (Guangzhou)/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/mods/msg/msg.c mods/msg/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c99 -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__REDLIB__ -D"SW_MAJOR_VERSION=$(shell busybox date +%y%V)" -DSW_MINOR_VERSION=19 -D"APP_BUILD_TIMESTAMP=$(shell busybox date +%s)" -DMIME=\"t/demo.nhs.nxp\" -DAPP_NO_MEASUREMENT_IN_NFC_FIELD -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_demo_dp_tlogger\inc" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\inc" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\inc" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\mods" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_demo_dp_tlogger\mods" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\mods" -I"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\mods" -include"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_demo_dp_tlogger\mods\app_sel.h" -include"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\mods\board_sel.h" -include"D:\OneDrive - HKUST (Guangzhou)\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\mods\chip_sel.h" -Og -fno-common -g3 -gdwarf-4 -Wall -Wextra -Wconversion -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-mods-2f-msg

clean-mods-2f-msg:
	-$(RM) ./mods/msg/msg.d ./mods/msg/msg.o

.PHONY: clean-mods-2f-msg

