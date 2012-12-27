################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Objects/MovableObjects/Camera.cpp \
../Objects/MovableObjects/Light.cpp \
../Objects/MovableObjects/MovableObject.cpp 

OBJS += \
./Objects/MovableObjects/Camera.o \
./Objects/MovableObjects/Light.o \
./Objects/MovableObjects/MovableObject.o 

CPP_DEPS += \
./Objects/MovableObjects/Camera.d \
./Objects/MovableObjects/Light.d \
./Objects/MovableObjects/MovableObject.d 


# Each subdirectory must supply rules for building sources it contributes
Objects/MovableObjects/%.o: ../Objects/MovableObjects/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -fpermissive -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


