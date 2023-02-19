################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c \
../tinythreads.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o \
tinythreads.o

OBJS_AS_ARGS +=  \
main.o \
tinythreads.o

C_DEPS +=  \
main.d \
tinythreads.d

C_DEPS_AS_ARGS +=  \
main.d \
tinythreads.d

OUTPUT_FILE_PATH +=lab3_alt2.elf

OUTPUT_FILE_PATH_AS_ARGS +=lab3_alt2.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)F:\microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"F:\microchip studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include"  -O2 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -Wextra -pedantic -mmcu=atmega169p -B "F:\microchip studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega169p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./tinythreads.o: .././tinythreads.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)F:\microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"F:\microchip studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include"  -O2 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -Wextra -pedantic -mmcu=atmega169p -B "F:\microchip studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega169p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)F:\microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="lab3_alt2.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega169p -B "F:\microchip studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega169p"  
	@echo Finished building target: $@
	"F:\microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "lab3_alt2.elf" "lab3_alt2.hex"
	"F:\microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "lab3_alt2.elf" "lab3_alt2.eep" || exit 0
	"F:\microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "lab3_alt2.elf" > "lab3_alt2.lss"
	"F:\microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "lab3_alt2.elf" "lab3_alt2.srec"
	"F:\microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "lab3_alt2.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "lab3_alt2.elf" "lab3_alt2.a" "lab3_alt2.hex" "lab3_alt2.lss" "lab3_alt2.eep" "lab3_alt2.map" "lab3_alt2.srec" "lab3_alt2.usersignatures"
	