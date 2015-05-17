#
# The "olists" library build rules
#
# Copyright (C) 2015 Samo Pogacnik <samo_pogacnik@t-2.net>
# All rights reserved.
#
# This file is part of the "olists" software project.
# This file is provided under the terms of the BSD 3-Clause license,
# available in the LICENSE file of the "olists" software project.
#

# Create a library called "olists" which includes the source files "oredredstr.c, ...".
# The extension is already found. Any number of sources could be listed here.
add_library (olists SHARED orderedstr.c orderedmem.c) 

set_target_properties (olists PROPERTIES VERSION ${project_VERSION_STRING} SOVERSION ${project_VERSION_MAJOR})

install(TARGETS olists DESTINATION lib COMPONENT libs)
install(FILES ${project_SOURCE_DIR}/include/olists/olists.h DESTINATION include/olists COMPONENT headers)
