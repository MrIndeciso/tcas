# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

cmake_minimum_required(VERSION 3.5)
project(tcas)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(GMP gmp)

include_directories(
    src
    src/parser
    src/reducer
    src/tokenizer
    src/translator
    src/types
    src/math
    src/util
    src/math/basic
    src/xml
    src/test
)

set (SRCS
    src/parser/parser.c
    src/parser/parser.h
    src/parser/rpn_defs.c
    src/parser/rpn_defs.h
    src/parser/rpn_parser.c
    src/parser/rpn_parser.h
    src/parser/util.c
    src/parser/util.h
    src/reducer/reducer.c
    src/reducer/reducer.h
    src/tokenizer/tokenizer.c
    src/tokenizer/tokenizer.h
    src/translator/translator.c
    src/translator/translator.h
    src/translator/translator_util.c
    src/translator/translator_util.h
    src/types/expr_structs.h
    src/types/parser_enums.h
    src/types/parser_structs.h
    src/types/tcas_enums.h
    src/types/tcas_structs.h
    src/types/tokenizer_structs.h
    src/xml/xml.c
    src/xml/xml.h
    src/util/mem_util.h
    src/util/mem_util.c
    src/util/debug_util.h
    src/util/debug_util.c
    src/math/math.h
    src/math/math.c
    src/math/type_util.h
    src/math/type_util.c
    src/math/basic/plus.h
    src/math/basic/plus.c
    src/math/basic/minus.h
    src/math/basic/minus.c
    src/math/basic/times.h
    src/math/basic/times.c
    src/math/basic/divide.h
    src/math/basic/divide.c
    src/tcas.c
    src/tcas.h
)

set (CLI_SRCS
    src/tcas_cli.c
)

set (TEST_SRCS
    src/test.c
    src/test/test_util.h
    src/test/test_util.c
    src/test/basic_test.h
    src/test/basic_test.c
)

add_executable(tcas_cli ${SRCS} ${CLI_SRCS})
add_executable(test ${SRCS} ${TEST_SRCS})

target_link_libraries(tcas_cli ${GMP})
target_link_libraries(test ${GMP})
