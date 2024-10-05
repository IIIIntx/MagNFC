################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/crp.c \
../src/mainnfccertification.c 

C_DEPS += \
./src/crp.d \
./src/mainnfccertification.d 

OBJS += \
./src/crp.o \
./src/mainnfccertification.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c99 -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__REDLIB__ -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\inc" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\inc" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\mods" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_nfccertification\mods" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\mods" -I"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\mods" -include"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\app_nfccertification\mods\app_sel.h" -include"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_board_dp\mods\board_sel.h" -include"D:\SchoolTasks\SCuMRobot\magNFC\release_mra2_12_6_nhs3152\sw\nss\lib_chip_nss\mods/chip_sel.h" -Og -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/crp.d ./src/crp.o ./src/mainnfccertification.d ./src/mainnfccertification.o

.PHONY: clean-src

