/**
MIT License

Copyright (c) 2026 半夜变身魔丸偷袭微软老巢(kloveme)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef KCLIENT_SSLREQUEST
#define KCLIENT_SSLREQUEST

#include "http_parser/parser.hpp"
#include <cstdint>
#include <netinet/in.h>
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <string>
#include <unordered_map>
#include <memory>
#include "tcp_request.hpp"

#endif

namespace kc {
    namespace ssl_request {
        class request_ssl {
            private:
            SSL* oepnssl_object;
            socket_t socket_fd_object;
            uint64_t connection_port = 443;
            std::unordered_map<std::string, std::string> response_headers;
            std::string response_status_message;
            int response_status_code;
            std::string response_data;
            std::string config_host_name;
            std::unique_ptr<kc::data_parser::http_parser> response_parser;
            public:
            ~request_ssl() = default;
            void init_socket_ssl(const std::string& target_host);
            void connection_tcp (struct sockaddr_in socket_config , SSL_CTX* ssl_context);
            void connection_ssl (SSL_CTX* ssl_context);
            void send_ssl_data (const std::string& http_tmp_data);
            inline std::string get_response_message () {return response_status_message;}
            inline int get_response_code () {return response_status_code;}
            inline std::string get_response_body () {return response_data;}
            inline std::unordered_map<std::string,std::string> get_response_headers()
            {return response_headers;}
        };  
    }
}
