################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Examples/AbstractTile.cpp \
../src/Examples/Animal.cpp \
../src/Examples/EarthTile.cpp \
../src/Examples/FunctionDrawer.cpp \
../src/Examples/FunctionSimulator.cpp \
../src/Examples/Nature.cpp \
../src/Examples/NatureDrawer.cpp \
../src/Examples/Network.cpp \
../src/Examples/NetworkDrawer.cpp \
../src/Examples/NetworkSimulator.cpp \
../src/Examples/Position.cpp \
../src/Examples/RockTile.cpp \
../src/Examples/TicTacToe.cpp \
../src/Examples/TicTacToeDrawer.cpp \
../src/Examples/TicTacToeKI.cpp 

OBJS += \
./src/Examples/AbstractTile.o \
./src/Examples/Animal.o \
./src/Examples/EarthTile.o \
./src/Examples/FunctionDrawer.o \
./src/Examples/FunctionSimulator.o \
./src/Examples/Nature.o \
./src/Examples/NatureDrawer.o \
./src/Examples/Network.o \
./src/Examples/NetworkDrawer.o \
./src/Examples/NetworkSimulator.o \
./src/Examples/Position.o \
./src/Examples/RockTile.o \
./src/Examples/TicTacToe.o \
./src/Examples/TicTacToeDrawer.o \
./src/Examples/TicTacToeKI.o 

CPP_DEPS += \
./src/Examples/AbstractTile.d \
./src/Examples/Animal.d \
./src/Examples/EarthTile.d \
./src/Examples/FunctionDrawer.d \
./src/Examples/FunctionSimulator.d \
./src/Examples/Nature.d \
./src/Examples/NatureDrawer.d \
./src/Examples/Network.d \
./src/Examples/NetworkDrawer.d \
./src/Examples/NetworkSimulator.d \
./src/Examples/Position.d \
./src/Examples/RockTile.d \
./src/Examples/TicTacToe.d \
./src/Examples/TicTacToeDrawer.d \
./src/Examples/TicTacToeKI.d 


# Each subdirectory must supply rules for building sources it contributes
src/Examples/%.o: ../src/Examples/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/home/domin/workspace/LightBulb/src" -O0 -g3 -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


