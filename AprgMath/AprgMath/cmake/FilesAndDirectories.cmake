set(APRG_MATH_SOURCE_DIRECTORY
    ${APRG_MATH_DIR}/src
)

set(APRG_MATH_TEST_DIRECTORY
    ${APRG_MATH_DIR}/tst
)

set(APRG_MATH_INCLUDE_DIRECTORIES
    ${APRG_MATH_SOURCE_DIRECTORY}
)

set(APRG_MATH_TEST_INCLUDE_DIRECTORIES
    ${APRG_MATH_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${APRG_MATH_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_MATH_SOURCE_DIRECTORY_LIST ${APRG_MATH_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_MATH_SOURCES APRG_MATH_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${APRG_MATH_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_MATH_TEST_DIRECTORY_LIST ${APRG_MATH_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_MATH_TESTS APRG_MATH_TEST_DIRECTORY_LIST)

set(APRG_MATH_SOURCES_AND_TESTS
    ${APRG_MATH_SOURCES}
    ${APRG_MATH_TESTS}
)
