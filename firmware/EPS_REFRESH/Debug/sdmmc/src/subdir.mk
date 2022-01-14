################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sdmmc/src/fsl_mmc.c \
../sdmmc/src/fsl_sd.c \
../sdmmc/src/fsl_sdmmc_common.c \
../sdmmc/src/fsl_sdspi.c 

OBJS += \
./sdmmc/src/fsl_mmc.o \
./sdmmc/src/fsl_sd.o \
./sdmmc/src/fsl_sdmmc_common.o \
./sdmmc/src/fsl_sdspi.o 

C_DEPS += \
./sdmmc/src/fsl_mmc.d \
./sdmmc/src/fsl_sd.d \
./sdmmc/src/fsl_sdmmc_common.d \
./sdmmc/src/fsl_sdspi.d 


# Each subdirectory must supply rules for building sources it contributes
sdmmc/src/%.o: ../sdmmc/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL02Z16VFM4 -DCPU_MKL02Z16VFM4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../fatfs -I../fatfs/fatfs_include -I../sdmmc/inc -I../startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


