################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/mods/compress/heatshrink/heatshrink_decoder.c \
D:/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/mods/compress/heatshrink/heatshrink_encoder.c 

C_DEPS += \
./mods/compress/heatshrink/heatshrink_decoder.d \
./mods/compress/heatshrink/heatshrink_encoder.d 

OBJS += \
./mods/compress/heatshrink/heatshrink_decoder.o \
./mods/compress/heatshrink/heatshrink_encoder.o 


# Each subdirectory must supply rules for building sources it contributes
mods/compress/heatshrink/heatshrink_decoder.o: D:/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/mods/compress/heatshrink/heatshrink_decoder.c mods/compress/heatshrink/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c99 -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__REDLIB__ -D"SW_MAJOR_VERSION=$(shell busybox date +%y%V)" -DSW_MINOR_VERSION=19 -D"APP_BUILD_TIMESTAMP=$(shell busybox date +%s)" -DMIME=\"t/demo.nhs.nxp\" -DAPP_NO_MEASUREMENT_IN_NFC_FIELD -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_demo_dp_tlogger\inc" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\inc" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\inc" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\mods" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_demo_dp_tlogger\mods" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\mods" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\mods" -include"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_demo_dp_tlogger\mods\app_sel.h" -include"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\mods\board_sel.h" -include"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\mods\chip_sel.h" -Og -fno-common -g3 -gdwarf-4 -Wall -Wextra -Wconversion -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mods/compress/heatshrink/heatshrink_encoder.o: D:/SchoolTasks/SCuMRobot/magNFC/release_mra2_12_6_nhs3152/sw/nss/mods/compress/heatshrink/heatshrink_encoder.c mods/compress/heatshrink/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c99 -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__REDLIB__ -D"SW_MAJOR_VERSION=$(shell busybox date +%y%V)" -DSW_MINOR_VERSION=19 -D"APP_BUILD_TIMESTAMP=$(shell busybox date +%s)" -DMIME=\"t/demo.nhs.nxp\" -DAPP_NO_MEASUREMENT_IN_NFC_FIELD -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_demo_dp_tlogger\inc" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\inc" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\inc" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\mods" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_demo_dp_tlogger\mods" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\mods" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\mods" -include"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_demo_dp_tlogger\mods\app_sel.h" -include"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\mods\board_sel.h" -include"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\mods\chip_sel.h" -Og -fno-common -g3 -gdwarf-4 -Wall -Wextra -Wconversion -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-mods-2f-compress-2f-heatshrink

clean-mods-2f-compress-2f-heatshrink:
	-$(RM) ./mods/compress/heatshrink/heatshrink_decoder.d ./mods/compress/heatshrink/heatshrink_decoder.o ./mods/compress/heatshrink/heatshrink_encoder.d ./mods/compress/heatshrink/heatshrink_encoder.o

.PHONY: clean-mods-2f-compress-2f-heatshrink
