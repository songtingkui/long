#
# Auto-Generated file. Do not edit!
#

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../yaffs2/direct/yaffs_hweight.c \
../yaffs2/direct/yaffs_qsort.c \
../yaffs2/direct/yaffsfs.c

OBJS += \
./yaffs2/direct/yaffs_hweight.o \
./yaffs2/direct/yaffs_qsort.o \
./yaffs2/direct/yaffsfs.o

C_DEPS += \
./yaffs2/direct/yaffs_hweight.d \
./yaffs2/direct/yaffs_qsort.d \
./yaffs2/direct/yaffsfs.d

# Each subdirectory must supply rules for building sources it contributes
yaffs2/direct/%.o: ../yaffs2/direct/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SDE Lite C Compiler'
	D:/LoongIDE/mips-2011.03/bin/mips-sde-elf-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1B -DOS_RTTHREAD  -O0 -g -Wall -c -fmessage-length=0 -pipe -I"../" -I"../include" -I"../RTT4/include" -I"../RTT4/port/include" -I"../RTT4/port/mips" -I"../RTT4/components/finsh" -I"../RTT4/components/dfs/include" -I"../RTT4/components/drivers/include" -I"../RTT4/components/libc/time" -I"../RTT4/bsp-ls1x" -I"../ls1x-drv/include" -I"../yaffs2/direct" -I"../yaffs2/port" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

