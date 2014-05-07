file(GLOB loader_top_SOURCES *.*)

include_directories(${PROJECT_SOURCE_DIR}/OnionLoader/)

add_executable(OnionLoader ${loader_top_SOURCES})

source_group("OnionLoader\\" FILES ${loader_top_SOURCES})

target_link_libraries(OnionLoader OnionRing)
