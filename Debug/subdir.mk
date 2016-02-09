################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../fs.cpp \
../main.cpp \
../nes.cpp \
../register.cpp \
../vm.cpp 

OBJS += \
./fs.o \
./main.o \
./nes.o \
./register.o \
./vm.o 

CPP_DEPS += \
./fs.d \
./main.d \
./nes.d \
./register.d \
./vm.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


