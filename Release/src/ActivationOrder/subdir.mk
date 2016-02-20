################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ActivationOrder/AbstractActivationOrder.cpp \
../src/ActivationOrder/AsynchronousOrder.cpp \
../src/ActivationOrder/SynchronousOrder.cpp \
../src/ActivationOrder/TopologicalOrder.cpp 

OBJS += \
./src/ActivationOrder/AbstractActivationOrder.o \
./src/ActivationOrder/AsynchronousOrder.o \
./src/ActivationOrder/SynchronousOrder.o \
./src/ActivationOrder/TopologicalOrder.o 

CPP_DEPS += \
./src/ActivationOrder/AbstractActivationOrder.d \
./src/ActivationOrder/AsynchronousOrder.d \
./src/ActivationOrder/SynchronousOrder.d \
./src/ActivationOrder/TopologicalOrder.d 


# Each subdirectory must supply rules for building sources it contributes
src/ActivationOrder/%.o: ../src/ActivationOrder/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/home/domin/workspace/LightBulb/src" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


