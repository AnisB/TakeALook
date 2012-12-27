################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MathTools/Vector3.cpp \
../MathTools/Vector4.cpp 

OBJS += \
./MathTools/Vector3.o \
./MathTools/Vector4.o 

CPP_DEPS += \
./MathTools/Vector3.d \
./MathTools/Vector4.d 


# Each subdirectory must supply rules for building sources it contributes
MathTools/%.o: ../MathTools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -fpermissive -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


