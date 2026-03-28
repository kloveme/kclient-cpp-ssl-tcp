cmake_minimum_required(VERSION 3.15)
project(kclient VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
set(SOURCES
 "../Kclient/lib/api/execute.cc"
 "../Kclient/lib/api/kclient.cc"
 "../Kclient/lib/core_lib/parser_lib.cc"
 "../Kclient/lib/api/httptemplate_lib.cc"
 "../Kclient/lib/core_lib/tcp_request_lib.cc"
 "../Kclient/lib/core_lib/ssl_request_lib.cc"
"../Kclient/lib/Impl_lib/kclinet_impl_lib.cc"
)

set(HEADERS_FILE
  "../Kclient/includ"
  "../Kclient/include/Impl/"
  "../Kclient/include/core/"
  "../Kclient/include/core/http_parser/"
)
add_library(_kclient_so SHARED ${SOURCES})
add_executable(kclient ../Kclient/example/main.cc)
target_link_libraries(kclient ${OPENSSL_LIBRARIES} _kclient_so)
set_target_properties(_kclient_so PROPERTIES 
  VERSION 0.1.0
  SOVERSION 0
)
target_include_directories(kclient PRIVATE ${HEADERS_FILE})
