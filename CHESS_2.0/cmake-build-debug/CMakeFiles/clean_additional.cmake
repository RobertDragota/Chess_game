# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CHESS_2_0_autogen"
  "CMakeFiles/CHESS_2_0_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/CHESS_2_0_autogen.dir/ParseCache.txt"
  )
endif()
