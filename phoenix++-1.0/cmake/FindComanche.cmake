# find comanche

if(NOT COMANCHE_PREFIX)
    message( FATAL_ERROR "need to set comanche root dir -DCOMANCHE_PREFIX" )
endif()
include_directories(${COMANCHE_PREFIX}/src/components/)
include_directories(${COMANCHE_PREFIX}/src/lib/common/include)
include_directories(${COMANCHE_PREFIX}/src/lib/core/include)
link_directories(${COMANCHE_PREFIX}/lib)
