################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Objects/StaticObjects/Map.cpp \
../Objects/StaticObjects/Tree.cpp 

OBJS += \
./Objects/StaticObjects/Map.o \
./Objects/StaticObjects/Tree.o 

CPP_DEPS += \
./Objects/StaticObjects/Map.d \
./Objects/StaticObjects/Tree.d 


# Each subdirectory must supply rules for building sources it contributes
Objects/StaticObjects/%.o: ../Objects/StaticObjects/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -fpermissive -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


