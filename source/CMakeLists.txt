cmake_minimum_required(VERSION 3.20)

include(CMakePrintHelpers)
find_package(PkgConfig REQUIRED)

add_executable(
	ffmpeg-decode
	main.cpp
	ffmpeg_file.cpp
    ffmpeg_scale.cpp
)

pkg_check_modules(LIBAV REQUIRED libavutil libavcodec libavformat libswscale libswresample)
cmake_print_variables(LIBAV_CFLAGS LIBAV_LDFLAGS LIBAV_LINK_LIBRARIES LIBAV_LIBRARIES)

target_compile_options(ffmpeg-decode PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${LIBAV_CFLAGS}>)
target_link_libraries(ffmpeg-decode PRIVATE ${LIBAV_LINK_LIBRARIES})

install(TARGETS ffmpeg-decode DESTINATION ${CMAKE_SOURCE_DIR}/)
