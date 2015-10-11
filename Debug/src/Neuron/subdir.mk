################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Neuron/AbstractNeuron.cpp \
../src/Neuron/AbstractThreshold.cpp \
../src/Neuron/BiasNeuron.cpp \
../src/Neuron/Edge.cpp \
../src/Neuron/InputNeuron.cpp \
../src/Neuron/NeuronCompareThreshold.cpp \
../src/Neuron/RBFThreshold.cpp \
../src/Neuron/StandardNeuron.cpp \
../src/Neuron/StandardThreshold.cpp 

OBJS += \
./src/Neuron/AbstractNeuron.o \
./src/Neuron/AbstractThreshold.o \
./src/Neuron/BiasNeuron.o \
./src/Neuron/Edge.o \
./src/Neuron/InputNeuron.o \
./src/Neuron/NeuronCompareThreshold.o \
./src/Neuron/RBFThreshold.o \
./src/Neuron/StandardNeuron.o \
./src/Neuron/StandardThreshold.o 

CPP_DEPS += \
./src/Neuron/AbstractNeuron.d \
./src/Neuron/AbstractThreshold.d \
./src/Neuron/BiasNeuron.d \
./src/Neuron/Edge.d \
./src/Neuron/InputNeuron.d \
./src/Neuron/NeuronCompareThreshold.d \
./src/Neuron/RBFThreshold.d \
./src/Neuron/StandardNeuron.d \
./src/Neuron/StandardThreshold.d 


# Each subdirectory must supply rules for building sources it contributes
src/Neuron/%.o: ../src/Neuron/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/home/domin/workspace/LightBulb/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


