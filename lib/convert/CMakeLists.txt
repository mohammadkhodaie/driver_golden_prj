

########################################################################
# This file included, use CMake directory variables
########################################################################
INCLUDE(CheckIncludeFileCXX)
MESSAGE(STATUS "")

########################################################################
# Look for Orc support
########################################################################
#FIND_PACKAGE(ORC)

#IF(NOT ORCC_EXECUTABLE)
#    FIND_PROGRAM(ORCC_EXECUTABLE orcc)
#ENDIF()

#LIBPAX_REGISTER_COMPONENT("ORC" ENABLE_ORC ON "ENABLE_LIBPAX;ORC_FOUND;ORCC_EXECUTABLE" OFF)

#IF(ENABLE_ORC)
#    INCLUDE_DIRECTORIES(${ORC_INCLUDE_DIRS})
#    LINK_DIRECTORIES(${ORC_LIBRARY_DIRS})
#    ENABLE_LANGUAGE(C)

#    SET(orcc_src ${CMAKE_CURRENT_SOURCE_DIR}/convert_orc.orc)

#    GET_FILENAME_COMPONENT(orc_file_name_we ${orcc_src} NAME_WE)
#    SET(orcc_gen ${CMAKE_CURRENT_BINARY_DIR}/${orc_file_name_we}.c)
#    MESSAGE(STATUS "Orc found, enabling Orc support.")
#    ADD_CUSTOM_COMMAND(
#        COMMAND ${ORCC_EXECUTABLE} --implementation -o ${orcc_gen} ${orcc_src}
#        DEPENDS ${orcc_src} OUTPUT ${orcc_gen}
#    )
#    LIBPAX_APPEND_SOURCES(${orcc_gen})
#    LIBPAX_APPEND_SOURCES(
#        ${CMAKE_CURRENT_SOURCE_DIR}/convert_with_orc.cpp
#    )
#    LIBPAX_APPEND_LIBS(${ORC_LIBRARIES})
#ELSE(ENABLE_ORC)
#    MESSAGE(STATUS "Orc not found, disabling orc support.")
#ENDIF(ENABLE_ORC)

########################################################################
# Check for SSE2 SIMD headers
########################################################################
IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(EMMINTRIN_FLAGS -msse2)
ELSEIF(MSVC)
    SET(EMMINTRIN_FLAGS /arch:SSE2)
ENDIF()

SET(CMAKE_REQUIRED_FLAGS ${EMMINTRIN_FLAGS})
CHECK_INCLUDE_FILE_CXX(emmintrin.h HAVE_EMMINTRIN_H)
SET(CMAKE_REQUIRED_FLAGS)

IF(HAVE_EMMINTRIN_H)
    SET(convert_with_sse2_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/sse2_sc16_to_fc64.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sse2_sc16_to_fc32.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sse2_sc8_to_fc64.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sse2_sc8_to_fc32.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sse2_fc64_to_sc16.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sse2_fc32_to_sc16.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sse2_fc64_to_sc8.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sse2_fc32_to_sc8.cpp
    )
    SET_SOURCE_FILES_PROPERTIES(
        ${convert_with_sse2_sources}
        PROPERTIES COMPILE_FLAGS "${EMMINTRIN_FLAGS}"
    )
    LIBPAX_APPEND_SOURCES(${convert_with_sse2_sources})
ENDIF(HAVE_EMMINTRIN_H)

########################################################################
# Check for NEON SIMD headers
########################################################################
IF(CMAKE_COMPILER_IS_GNUCXX)
    CHECK_INCLUDE_FILE_CXX(arm_neon.h HAVE_ARM_NEON_H)
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

IF(HAVE_ARM_NEON_H)
    ENABLE_LANGUAGE(ASM)

    # LIBPAX_APPEND_SOURCES(
    #     ${CMAKE_CURRENT_SOURCE_DIR}/convert_with_neon.cpp
    #     ${CMAKE_CURRENT_SOURCE_DIR}/convert_neon.S
    # )
ENDIF()

########################################################################
# Convert types generation
########################################################################
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})



LIBPAX_APPEND_SOURCES(
    ${CMAKE_CURRENT_SOURCE_DIR}/convert_with_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/convert_impl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/convert_item32.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/convert_pack_sc12.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/convert_unpack_sc12.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/convert_fc32_item32.cpp
)
