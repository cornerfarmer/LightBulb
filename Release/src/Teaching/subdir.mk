################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Teaching/AbstractTeachingLesson.cpp \
../src/Teaching/Teacher.cpp \
../src/Teaching/TeachingLessonBooleanInput.cpp \
../src/Teaching/TeachingLessonLinearInput.cpp 

OBJS += \
./src/Teaching/AbstractTeachingLesson.o \
./src/Teaching/Teacher.o \
./src/Teaching/TeachingLessonBooleanInput.o \
./src/Teaching/TeachingLessonLinearInput.o 

CPP_DEPS += \
./src/Teaching/AbstractTeachingLesson.d \
./src/Teaching/Teacher.d \
./src/Teaching/TeachingLessonBooleanInput.d \
./src/Teaching/TeachingLessonLinearInput.d 


# Each subdirectory must supply rules for building sources it contributes
src/Teaching/%.o: ../src/Teaching/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/home/domin/workspace/LightBulb/src" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


