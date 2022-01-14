################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fatfs/fatfs_source/diskio.c \
../fatfs/fatfs_source/ff.c \
../fatfs/fatfs_source/fsl_mmc_disk.c \
../fatfs/fatfs_source/fsl_ram_disk.c \
../fatfs/fatfs_source/fsl_sd_disk.c \
../fatfs/fatfs_source/fsl_sdspi_disk.c 

OBJS += \
./fatfs/fatfs_source/diskio.o \
./fatfs/fatfs_source/ff.o \
./fatfs/fatfs_source/fsl_mmc_disk.o \
./fatfs/fatfs_source/fsl_ram_disk.o \
./fatfs/fatfs_source/fsl_sd_disk.o \
./fatfs/fatfs_source/fsl_sdspi_disk.o 

C_DEPS += \
./fatfs/fatfs_source/diskio.d \
./fatfs/fatfs_source/ff.d \
./fatfs/fatfs_source/fsl_mmc_disk.d \
./fatfs/fatfs_source/fsl_ram_disk.d \
./fatfs/fatfs_source/fsl_sd_disk.d \
./fatfs/fatfs_source/fsl_sdspi_disk.d 


# Each subdirectory must supply rules for building sources it contributes
fatfs/fatfs_source/%.o: ../fatfs/fatfs_source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL02Z16VFM4 -DCPU_MKL02Z16VFM4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../fatfs -I../fatfs/fatfs_include -I../sdmmc/inc -I../startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


