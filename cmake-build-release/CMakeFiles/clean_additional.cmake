# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\PasswordContainerProd_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PasswordContainerProd_autogen.dir\\ParseCache.txt"
  "PasswordContainerProd_autogen"
  )
endif()
