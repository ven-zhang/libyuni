cmake_minimum_required(VERSION 2.8)
include("../cmake/message.cmake")


YMESSAGE("")
YMESSAGE("Yuni Framework - Samples")
YMESSAGE("")
project(yuni-samples)

if(POLICY CMP0011)
	cmake_policy(SET CMP0011 NEW)
endif(POLICY CMP0011)

include(CheckCSourceCompiles)
include(CheckCXXSourceCompiles)
include(CheckIncludeFiles)
include(CheckIncludeFileCXX)
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)


# To find 'FindYuni.cmake'
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../packages/cmake")

include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/common-settings.cmake")

add_custom_target(samples)

set(Yuni_YUNICONFIG_PATH ${YUNI_CONFIG})
find_package(Yuni COMPONENTS core)
if(Yuni_FOUND)

	# Infos
	YMESSAGE("The Yuni Framework : ${Yuni_INFOS}")

	add_subdirectory(audio)
	add_subdirectory(core)
	add_subdirectory(marshal)
	add_subdirectory(io)
	add_subdirectory(devices)
	add_subdirectory(jobs)
	add_subdirectory(threads)
	add_subdirectory(messaging)
	add_subdirectory(extra)
	add_subdirectory(dbi)
	add_subdirectory(parser)

else()

	YMESSAGE("A working Yuni Framework was not found (could not locate yuni-config).")
	YMESSAGE("If you are not building from within the source tree, you should define")
	YMESSAGE("YUNI_CONFIG to the path to the yuni-config binary, e.g.:")
	YMESSAGE(" $ cmake -DYUNI_CONFIG=path/to/yuni-config <samples_path>")
	YERROR("Aborting.")

endif()

