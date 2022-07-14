#
# Auto-Generated file. Do not edit!
#

# Add inputs and outputs from these tool invocations to the build variables
ASM_SRCS += \
../core/mips_timer.S \
../core/start.S

C_SRCS += \
../core/bsp_start.c \
../core/clock.c \
../core/exception.c \
../core/irq.c

STARTO += ./core/start.o

OBJS += \
./core/bsp_start.o \
./core/clock.o \
./core/exception.o \
./core/irq.o \
./core/mips_timer.o \

ASM_DEPS += \
./core/mips_timer.d \
./core/start.d

C_DEPS += \
./core/bsp_start.d \
./core/clock.d \
./core/exception.d \
./core/irq.d

# Each subdirectory must supply rules for building sources it contributes
core/%.o: ../core/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: SDE Lite C Compiler'
	C:/LoongIDE/mips-2011.03/bin/mips-sde-elf-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1c101 -DOS_NONE  -O1 -g -Wall -c -fmessage-length=0 -pipe -I"../" -I"../include" -I"../core/mips" -I"../core/include" -I"../driver/include" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

core/%.o: ../core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SDE Lite C Compiler'
	C:/LoongIDE/mips-2011.03/bin/mips-sde-elf-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1c101 -DOS_NONE  -O1 -g -Wall -c -fmessage-length=0 -pipe -I"../" -I"../include" -I"../core/mips" -I"../core/include" -I"../driver/include" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

