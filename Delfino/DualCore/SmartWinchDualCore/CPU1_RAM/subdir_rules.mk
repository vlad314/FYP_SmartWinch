################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FM25W256.obj: ../FM25W256.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="FM25W256.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ModbusMaster.obj: ../ModbusMaster.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="ModbusMaster.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

MotionProfile.obj: ../MotionProfile.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="MotionProfile.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RoboClaw.obj: ../RoboClaw.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="RoboClaw.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

autonomous_mode.obj: ../autonomous_mode.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="autonomous_mode.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

buffered_serial.obj: ../buffered_serial.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="buffered_serial.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

buffered_serial_B.obj: ../buffered_serial_B.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="buffered_serial_B.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

buffered_serial_C.obj: ../buffered_serial_C.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="buffered_serial_C.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

device_init.obj: ../device_init.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="device_init.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

intermediate_waypoints.obj: ../intermediate_waypoints.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="intermediate_waypoints.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

interrupt_handlers.obj: ../interrupt_handlers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="interrupt_handlers.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

interwinch_comms.obj: ../interwinch_comms.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="interwinch_comms.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

kinematics.obj: ../kinematics.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="kinematics.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

modbusRTU.obj: ../modbusRTU.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="modbusRTU.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

modbus_regs.obj: ../modbus_regs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="modbus_regs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

motion_buffer.obj: ../motion_buffer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="motion_buffer.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

motor_driver.obj: ../motor_driver.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="motor_driver.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

safety_routines.obj: ../safety_routines.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="safety_routines.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

task_scheduler.obj: ../task_scheduler.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore" --include_path="C:/Users/VladCosmin/Desktop/helloVlad/FYP_SmartWinch-master1/FYP_SmartWinch-master/Delfino/DualCore/SmartWinchDualCore/device" --include_path="C:/ti/c2000/C2000Ware_1_00_03_00/driverlib/f2837xd/driverlib" --include_path="C:/Z/Games/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="task_scheduler.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


