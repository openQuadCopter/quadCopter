add_custom_target(quadcopterbin DEPENDS RTIMULib)

##add_dependencies(quadcopterbin RTIMU)

SET( quadCode_SRCS 
	${quadCopter_SOURCE_DIR}/src/quadCopter.cpp
	${quadCopter_SOURCE_DIR}/src/quad_Motor.cpp
	${quadCopter_SOURCE_DIR}/src/quad_MotorManager.cpp
	${quadCopter_SOURCE_DIR}/src/main.cpp	
	${quadCopter_SOURCE_DIR}/src/quad_PIDRoll.cpp
	${quadCopter_SOURCE_DIR}/src/quad_PIDPitch.cpp
	${quadCopter_SOURCE_DIR}/src/quad_PIDYaw.cpp	
	${quadCopter_SOURCE_DIR}/src/quad_IMU.cpp	
)

SET( quadCode_HDRS 
	${quadCopter_SOURCE_DIR}/include/quadCopter.h
	${quadCopter_SOURCE_DIR}/include/quad_Motor.h
	${quadCopter_SOURCE_DIR}/include/quad_MotorManager.h
	${quadCopter_SOURCE_DIR}/include/quad_PID.h
	${quadCopter_SOURCE_DIR}/include/quad_PIDRoll.h
	${quadCopter_SOURCE_DIR}/include/quad_PIDPitch.h
	${quadCopter_SOURCE_DIR}/include/quad_PIDYaw.h
	${quadCopter_SOURCE_DIR}/include/quad_PIDIMU.h
)

INCLUDE_DIRECTORIES(../thirdParty/RTIMU )
ADD_EXECUTABLE(quadcopter ${quadCode_SRCS} )
TARGET_LINK_LIBRARIES(quadcopter m RTIMU pthread )



