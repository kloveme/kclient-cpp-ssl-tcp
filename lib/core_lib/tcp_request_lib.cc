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

#include "../../include/core/tcp_request.hpp"
#include "../../include/core/http_parser/parser.hpp"
#include <arpa/inet.h>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <memory>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/types.h>

#ifdef _WIN32
    #include <winsock2.h> 
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#endif

#ifdef __gnu_linux__
    #include <sys/socket.h>
    #include <unistd.h>
    #include <netdb.h>
#endif

void kc::tcp_request::request_tcp::init_socket(const std::string& target_host)
{
    kc::tcp_request::request_tcp::response_parser = 
        std::make_unique<kc::data_parser::http_parser>();
    kc::tcp_request::request_tcp::socket_fd_object
    = socket(AF_INET, SOCK_STREAM, 0);
    if (kc::tcp_request::request_tcp::socket_fd_object
        == INVALID_SOCKET_VALUE) throw std::runtime_error
        ("socket initialize failed!");
    struct hostent* server_informations =
        gethostbyname(target_host.c_str());
        if (!server_informations) throw std::runtime_error
        ("resolver host failed!");
    struct sockaddr_in socket_config_addr;
    socket_config_addr.sin_family = AF_INET;
    memcpy(&socket_config_addr.sin_addr.s_addr,
        server_informations->h_addr,
        server_informations->h_length);
    socket_config_addr.sin_port = htons(kc::tcp_request::request_tcp::connection_port);
    kc::tcp_request::request_tcp::connection_tcp(socket_config_addr);
}
void kc::tcp_request::request_tcp::connection_tcp(struct sockaddr_in socket_config)
{   
    if (connect(socket_fd_object, (struct sockaddr*)&socket_config, sizeof(socket_config)) < 0)
    {
        close_socket(socket_fd_object);
        throw std::runtime_error("Connection target server failed: " + std::string(strerror(errno)));
    }
}

void kc::tcp_request::request_tcp::send_data(const std::string& http_tmp_data)
{
    const char* send_data_cstr = http_tmp_data.c_str();
    const size_t send_data_size = http_tmp_data.size();
    size_t sent_code = send(socket_fd_object, 
        send_data_cstr,send_data_size,0);
    if (sent_code < 0) {throw std::runtime_error("send failed:\a"
    + std::string(strerror(errno)));}
    if (sent_code != (ssize_t)send_data_size)
    {throw std::runtime_error("send partial data");}
    std::string recv_buf; size_t content_length = 0;
    bool headers_done = false;
    char resp_buffer [46091];
    while (true) {
        ssize_t data_size = recv(kc::tcp_request::request_tcp::socket_fd_object, 
        resp_buffer,sizeof(resp_buffer), 0);
        if (data_size < 0){throw std::runtime_error("Get response failed!");}
        if (data_size == 0){throw std::runtime_error("The other party proactively closed the connection");}
            recv_buf.append(resp_buffer , data_size);
            if (!headers_done) {
                size_t headers_end = recv_buf.find("\r\n\r\n");
                if (headers_end != std::string::npos)
                {
                    content_length = kc::tcp_request::request_tcp::response_parser
                        -> get_content_length(recv_buf);
                    headers_done = true;
                }
            }
            if (headers_done && content_length > 0)
            {
                size_t body_start = recv_buf.find("\r\n\r\n") + 4;
                size_t body_length = recv_buf.size() - body_start;
                if (body_length >= content_length) 
                { kc::tcp_request::request_tcp::response_parser 
                    -> set_full_responsedata(recv_buf);
                    kc::tcp_request::request_tcp::response_status_code = kc::tcp_request::request_tcp::response_parser 
                        -> getresponse_status_code();
                    kc::tcp_request::request_tcp::response_status_message = kc::tcp_request::request_tcp::response_parser
                        -> getresponse_status_message();
                    kc::tcp_request::request_tcp::response_headers = kc::tcp_request::request_tcp::response_parser->
                        getresponse_headers();
                    kc::tcp_request::request_tcp::response_data = kc::tcp_request::request_tcp::response_parser->
                        getresponse_body();
                break;}
            }
    }
}
