
YMESSAGE_MODULE("Regex (via PCRE)  (EXPERIMENTAL)")

LIBYUNI_CONFIG_LIB("both" "regex"        "yuni-static-regex")


# Sources for parsing JSON are imported from nany and no relative paths
# is currently provided
include_directories("..")

set(SRC_REGEX
	regex/regex.h
	regex/regex.hxx
	regex/regex.cpp
)
source_group("Regex" FILES ${SRC_REGEX})



add_Library(yuni-static-regex STATIC
	${SRC_REGEX}
)

# Setting output path
SET_TARGET_PROPERTIES(yuni-static-regex PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
install(TARGETS yuni-static-regex ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

# Install regex-related headers
install(
	DIRECTORY regex
	DESTINATION include/${YUNI_VERSIONED_INST_PATH}/yuni
	FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	PATTERN ".svn" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
	PATTERN "cmake" EXCLUDE
)
