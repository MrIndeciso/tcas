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
    src/xml
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
    src/math/math.h
    src/math/math.c
    src/tcas.c
    src/tcas.h
    src/test.c
)


add_executable(${CMAKE_PROJECT_NAME} ${SRCS})

target_link_libraries(${CMAKE_PROJECT_NAME} ${GMP})
