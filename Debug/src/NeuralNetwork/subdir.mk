################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/NeuralNetwork/NeuralNetwork.cpp \
../src/NeuralNetwork/NeuralNetworkIO.cpp 

OBJS += \
./src/NeuralNetwork/NeuralNetwork.o \
./src/NeuralNetwork/NeuralNetworkIO.o 

CPP_DEPS += \
./src/NeuralNetwork/NeuralNetwork.d \
./src/NeuralNetwork/NeuralNetworkIO.d 


# Each subdirectory must supply rules for building sources it contributes
src/NeuralNetwork/%.o: ../src/NeuralNetwork/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/home/domin/workspace/LightBulb/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


