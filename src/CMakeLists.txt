
SET( quadCode_SRCS 
	${quadCopter_SOURCE_DIR}/src/quad_Motor.cpp
	${quadCopter_SOURCE_DIR}/src/quad_MotorScheduler.cpp
	${quadCopter_SOURCE_DIR}/src/main.cpp	
)

SET( quadCode_HDRS 
	${quadCopter_SOURCE_DIR}/include/quad_Motor.h
	${quadCopter_SOURCE_DIR}/include/quad_MotorScheduler.h
)

ADD_EXECUTABLE(quadcopter ${quadCode_SRCS} )
TARGET_LINK_LIBRARIES(quadcopter m)


