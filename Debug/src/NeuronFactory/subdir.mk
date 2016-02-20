################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/NeuronFactory/AbstractNeuronFactory.cpp \
../src/NeuronFactory/DifferentFunctionsNeuronFactory.cpp \
../src/NeuronFactory/SameFunctionsNeuronFactory.cpp 

OBJS += \
./src/NeuronFactory/AbstractNeuronFactory.o \
./src/NeuronFactory/DifferentFunctionsNeuronFactory.o \
./src/NeuronFactory/SameFunctionsNeuronFactory.o 

CPP_DEPS += \
./src/NeuronFactory/AbstractNeuronFactory.d \
./src/NeuronFactory/DifferentFunctionsNeuronFactory.d \
./src/NeuronFactory/SameFunctionsNeuronFactory.d 


# Each subdirectory must supply rules for building sources it contributes
src/NeuronFactory/%.o: ../src/NeuronFactory/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/home/domin/workspace/LightBulb/src" -O0 -g3 -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


