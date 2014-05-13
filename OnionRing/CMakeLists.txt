file(GLOB or_top_SOURCES *.*)
file(GLOB or_util_SOURCES Utils/*.*)
file(GLOB or_util_math_SOURCES Utils/Math/*.*)
file(GLOB or_system_SOURCES System/*.*)
file(GLOB or_rendering_SOURCES Rendering/*.*)

if(BUILD_STATIC)
    set(BUILD_MODE STATIC)
else()
    set(BUILD_MODE SHARED)
endif()

add_library(OnionRing ${BUILD_MODE} ${or_top_SOURCES} ${or_util_SOURCES} ${or_util_math_SOURCES} ${or_system_SOURCES} ${or_rendering_SOURCES})

target_link_libraries(OnionRing SDL2 zlib Lua)

source_group("OnionRing" FILES ${or_top_SOURCES})
source_group("OnionRing\\Utils" FILES ${or_util_SOURCES})
source_group("OnionRing\\Utils\\Math" FILES ${or_util_math_SOURCES})
source_group("OnionRing\\System" FILES ${or_system_SOURCES})
source_group("OnionRing\\Rendering" FILES ${or_rendering_SOURCES})

#install(TARGETS MethCasting RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
