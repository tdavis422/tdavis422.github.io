################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32/bin/arm-none-eabi-gcc-7.2.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=soft -DDeviceFamily_CC3220 -DNORTOS_SUPPORT -I"C:/Users/tdavi/workspace_v10/ProjectOne" -I"C:/Users/tdavi/workspace_v10/ProjectOne/Debug" -I"C:/ti/simplelink_cc32xx_sdk_7_10_00_13/source" -I"C:/ti/simplelink_cc32xx_sdk_7_10_00_13/kernel/nortos" -I"C:/ti/simplelink_cc32xx_sdk_7_10_00_13/kernel/nortos/posix" -I"C:/ti/ccs1011/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32/arm-none-eabi/include/newlib-nano" -I"C:/ti/ccs1011/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32/arm-none-eabi/include" -O3 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/tdavi/workspace_v10/ProjectOne/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1558634063: ../gpiointerrupt.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.19.0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_7_10_00_13/.metadata/product.json" --script "C:/Users/tdavi/workspace_v10/ProjectOne/gpiointerrupt.syscfg" -o "syscfg" --compiler gcc
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-1558634063 ../gpiointerrupt.syscfg
syscfg/ti_drivers_config.h: build-1558634063
syscfg/ti_utils_build_linker.cmd.genlibs: build-1558634063
syscfg/syscfg_c.rov.xs: build-1558634063
syscfg/: build-1558634063

syscfg/%.o: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32/bin/arm-none-eabi-gcc-7.2.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=soft -DDeviceFamily_CC3220 -DNORTOS_SUPPORT -I"C:/Users/tdavi/workspace_v10/ProjectOne" -I"C:/Users/tdavi/workspace_v10/ProjectOne/Debug" -I"C:/ti/simplelink_cc32xx_sdk_7_10_00_13/source" -I"C:/ti/simplelink_cc32xx_sdk_7_10_00_13/kernel/nortos" -I"C:/ti/simplelink_cc32xx_sdk_7_10_00_13/kernel/nortos/posix" -I"C:/ti/ccs1011/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32/arm-none-eabi/include/newlib-nano" -I"C:/ti/ccs1011/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32/arm-none-eabi/include" -O3 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"syscfg/$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/tdavi/workspace_v10/ProjectOne/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-187999553: ../image.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.19.0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_7_10_00_13/.metadata/product.json" --script "C:/Users/tdavi/workspace_v10/ProjectOne/image.syscfg" -o "syscfg" --compiler gcc
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_net_wifi_config.json: build-187999553 ../image.syscfg
syscfg/: build-187999553


