include (${project_cmake_dir}/Utils.cmake)
include (CheckCXXSourceCompiles)

include (${project_cmake_dir}/FindOS.cmake)
include (FindPkgConfig)

########################################
# Include man pages stuff
include (${project_cmake_dir}/Ronn2Man.cmake)
add_manpage_target()

########################################
# Temporarily include Gazebo stuff
find_package (gazebo REQUIRED gazebo_common gazebo_math)
include_directories (${GAZEBO_INCLUDE_DIRS})
link_directories (${GAZEBO_LIBRARY_DIRS})
