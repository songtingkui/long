#
# Auto-Generated file. Do not edit!
#

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../libc/errno/errno.c

OBJS += \
./libc/errno/errno.o

C_DEPS += \
./libc/errno/errno.d

# Each subdirectory must supply rules for building sources it contributes
libc/errno/%.o: ../libc/errno/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SDE Lite C Compiler'
	D:/LoongIDE/mips-2011.03/bin/mips-sde-elf-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1c101 -DOS_NONE  -Os -g -Wall -c -fmessage-length=0 -pipe  -I"../" -I"../include" -I"../core/mips" -I"../core/include" -I"../driver/include" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

