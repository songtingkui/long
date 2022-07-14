#
# Auto-Generated file. Do not edit!
#

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../libc/stdlib/atoi.c \
../libc/stdlib/atol.c \
../libc/stdlib/strtol.c \
../libc/stdlib/strtoul.c

OBJS += \
./libc/stdlib/atoi.o \
./libc/stdlib/atol.o \
./libc/stdlib/strtol.o \
./libc/stdlib/strtoul.o

C_DEPS += \
./libc/stdlib/atoi.d \
./libc/stdlib/atol.d \
./libc/stdlib/strtol.d \
./libc/stdlib/strtoul.d

# Each subdirectory must supply rules for building sources it contributes
libc/stdlib/%.o: ../libc/stdlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SDE Lite C Compiler'
	D:/LoongIDE/mips-2011.03/bin/mips-sde-elf-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1c101 -DOS_NONE  -O1 -g -Wall -c -fmessage-length=0 -pipe -I"../" -I"../include" -I"../core/mips" -I"../core/include" -I"../driver/include" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

