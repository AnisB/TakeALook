################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Rendering/Renderer.cpp 

OBJS += \
./Rendering/Renderer.o 

CPP_DEPS += \
./Rendering/Renderer.d 


# Each subdirectory must supply rules for building sources it contributes
Rendering/%.o: ../Rendering/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -fpermissive -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


