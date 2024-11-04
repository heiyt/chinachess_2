# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\chinachess_2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\chinachess_2_autogen.dir\\ParseCache.txt"
  "chinachess_2_autogen"
  )
endif()
