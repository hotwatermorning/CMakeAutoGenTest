cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)

project(CMakeAutoGenTestProject VERSION 0.0.1)

##########################################################################

# .proto ファイルの配置ディレクトリ
set(PROTO_FILES_DIR "${CMAKE_CURRENT_LIST_DIR}/Schemas")

# .proto ファイルをコンパイルしたソースファイルの出力パス
set(PROTO_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/Schemas)

# Protobuf のインストール情報を取得
find_package(Protobuf REQUIRED)

# .proto ファイルの一覧
set(PROTO_FILES
  ${PROTO_FILES_DIR}/MyData.proto
  ${PROTO_FILES_DIR}/User.proto
  )

foreach(PROTO_FILE ${PROTO_FILES})
  get_filename_component(NAME ${PROTO_FILE} NAME_WE)
  list(APPEND PROTO_OUTPUT_FILES
    ${PROTO_OUTPUT_DIR}/${NAME}.pb.h
    ${PROTO_OUTPUT_DIR}/${NAME}.pb.cc
    )
endforeach()

# .proto ファイルをコンパイルするコマンドを定義
add_custom_command(
  OUTPUT ${PROTO_OUTPUT_FILES}  # 生成するソースファイルを OUTPUT に指定しておく。
  DEPENDS ${PROTO_FILES}        # 生成するソースファイルの元になるファイルを DEPENDS に指定する。
                                # DEPENDS に指定したファイルが更新されると、
                                # 次回 add_custom_target() で定義したターゲットのビルド時に
                                # add_custom_command() で定義したコマンドが再実行される。
  COMMAND protobuf::protoc ARGS --proto_path=${PROTO_FILES_DIR} ${PROTO_FILES} --cpp_out=${PROTO_OUTPUT_DIR}
  VERBATIM
  )

# .proto ファイルをコンパイルするターゲットを定義。
add_custom_target(CompileSchemas
  DEPENDS ${PROTO_OUTPUT_FILES} # add_custom_command() の OUTPUT に指定したファイルを DEPENDS に指定する。
  )

# compile-schemas ターゲットのソースファイルを設定する。
# add_custom_target() コマンドの SOURCES 引数に ${PROTO_FILES} を設定するのでも問題ない。
source_group(TREE ${PROTO_FILES_DIR} FILES ${PROTO_FILES})
target_sources(CompileSchemas PRIVATE ${PROTO_FILES})

##########################################################################

add_executable(AutoGenTest)

set(SOURCE_FILES
  Sources/main.cpp
  )

# CompileSchemas ターゲットで生成したソースファイルを
# ソースリストに追加する。
list(APPEND SOURCE_FILES ${PROTO_OUTPUT_FILES})
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCE_FILES})
target_sources(AutoGenTest PRIVATE ${SOURCE_FILES})

# 実行ファイルやライブラリを作成するターゲットに対して、
# CompileSchemas ターゲットを依存ターゲットに設定する。
add_dependencies(AutoGenTest CompileSchemas)

# CompileSchemas ターゲットで生成したヘッダーファイルを
# 探索可能にする。
target_include_directories(AutoGenTest
  PUBLIC
  ${PROTO_OUTPUT_DIR}
  )

target_link_libraries(AutoGenTest
  PUBLIC
  protobuf::libprotobuf
  protobuf::libprotobuf-lite
  protobuf::libprotoc
  )

