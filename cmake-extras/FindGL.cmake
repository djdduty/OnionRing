 
# - Try to find OpenGL, glut includes and libraries
# Once done this will define:
#  gl_FOUND        - system has OpenGL and glut
#  gl_INCLUDE_DIR  - incude paths to use OpenGL and glut
#  gl_LIBRARIES    - Link these to use OpenGL and glut

SET(GL_FOUND 0)
IF(UNIX)
	FIND_PATH(gl_INCLUDE_DIR
		gl.h
		/usr/local/include
		/usr/include
		)

	FIND_LIBRARY(gl_LIBRARIES
		GL
		/usr/local/lib
		/usr/lib
		)
		
	IF(gl_LIBRARIES AND gl_INCLUDE_DIR)
		SET(GL_FOUND 1 CACHE STRING "Set to 1 if GL is found, 0 otherwise")
		INCLUDE_DIRECTORIES(BEFORE ${gl_INCLUDE_DIR})
		MESSAGE("DBG gl_INCLUDE_DIR: ${gl_INCLUDE_DIR}")
	ELSE(gl_LIBRARIES AND gl_INCLUDE_DIR)
		SET (GL_FOUND 0 CACHE STRING "Set to 1 if GL is found, 0 otherwise")
	ENDIF(gl_LIBRARIES AND gl_INCLUDE_DIR)
ENDIF(UNIX)


#global settings
SET(GL_LIBRARIES ${gl_LIBRARIES})
MESSAGE("DBG GL_LIBRARIES: ${GL_LIBRARIES}")