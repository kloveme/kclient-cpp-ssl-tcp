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


#ifndef KCLINET_TCPREQUEST
#define KCLINET_TCPREQUEST

#include "http_parser/parser.hpp"
#include <cstdint>
#include <memory>
#include <netinet/in.h>
#include <string>
#include <unordered_map>

#ifdef __gnu_linux__
    #include <sys/socket.h>
    #include <unistd.h>
#endif

#ifdef _WIN32
    #include <winsock2.h> 
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#endif

#ifdef _WIN32
    using socket_t = SOCKET;
    const socket_t INVALID_SOCKET_VALUE = INVALID_SOCKET;
#else
    using socket_t = int;
    const socket_t INVALID_SOCKET_VALUE = -1;
#endif

#ifdef _WIN32
    inline void close_socket(socket_t socket_fd) 
    { closesocket(socket_fd); }
#else
    inline void close_socket(int socket_fd) { close(socket_fd); }
#endif

namespace kc {
    namespace tcp_request {
        class request_tcp 
        {
            private:
            socket_t socket_fd_object;
            uint64_t connection_port = 80;
            std::unordered_map<std::string, std::string> response_headers;
            std::string response_status_message;
            int response_status_code;
            std::string response_data;
            std::unique_ptr<kc::data_parser::http_parser> response_parser;
            public:
            ~request_tcp() = default;
            void init_socket (const std::string& target_host);
            void connection_tcp(struct sockaddr_in socket_config);
            void send_data(const std::string& http_tmp_data);
            inline std::string get_response_body () {return response_data;}
            inline int get_response_code () {return response_status_code;}
            inline std::string get_response_message () {return response_status_message;}
            inline std::unordered_map<std::string, std::string> get_response_headers(){return response_headers;}
        };
    }
}

#endif