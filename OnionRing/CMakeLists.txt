file(GLOB or_top_SOURCES *.*)
file(GLOB or_util_SOURCES Utils/*.*)

if(BUILD_STATIC)
    set(BUILD_MODE STATIC)
else()
    set(BUILD_MODE SHARED)
endif()

add_library(OnionRing ${BUILD_MODE} ${or_top_SOURCES} ${or_util_SOURCES})

target_link_libraries(OnionRing Soil Glew Glfw zlib Lua ${GL_LIBRARIES} ${GLFW_LIBRARIES})

source_group("OnionRing" FILES ${or_top_SOURCES})
source_group("OnionRing\\Utils" FILES ${or_util_SOURCES})

#install(TARGETS MethCasting RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
