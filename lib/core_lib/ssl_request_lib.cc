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

#include "../../include/core/ssl_request.hpp"
#include "../../include/core/http_parser/parser.hpp"
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/tls1.h>
#include <openssl/err.h>
#include <stdexcept>
#include <string>

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

void kc::ssl_request::request_ssl::init_socket_ssl(const std::string& target_host)
{
  kc::ssl_request::request_ssl::response_parser = std::make_unique<kc::data_parser::http_parser>();
  kc::ssl_request::request_ssl::socket_fd_object = 
    socket(AF_INET, SOCK_STREAM,0);
  if (kc::ssl_request::request_ssl::socket_fd_object == INVALID_SOCKET_VALUE)
  {throw std::runtime_error("socket initialize failed!");}
  struct hostent* server_resovler = 
    gethostbyname(target_host.c_str());
  if (!server_resovler) throw std::runtime_error("resovler server host failed");
  kc::ssl_request::request_ssl::config_host_name = target_host;
  struct sockaddr_in socket_config_addr;
  socket_config_addr.sin_family = AF_INET;
  memcpy(&socket_config_addr.sin_addr.s_addr,
      server_resovler->h_addr,server_resovler->h_length);
  socket_config_addr.sin_port = htons(kc::ssl_request::request_ssl::connection_port);
  SSL_library_init();
  SSL_load_error_strings();
  OpenSSL_add_ssl_algorithms();
  SSL_CTX* openssl_ctx = SSL_CTX_new(TLS_client_method());
  SSL_CTX_set_min_proto_version(openssl_ctx , TLS1_2_VERSION);
  SSL_CTX_set_max_proto_version(openssl_ctx, TLS1_3_VERSION);
  if (!openssl_ctx) {throw std::runtime_error("oepnssl context create failed");}
  int err_code = SSL_CTX_load_verify_locations(openssl_ctx, "/etc/ssl/certs/ca-certificates.crt",
     nullptr);
  if (err_code != 1)
  { SSL_CTX_set_verify(openssl_ctx, SSL_VERIFY_PEER, nullptr);
       int set_default_ec =  SSL_CTX_set_default_verify_paths(openssl_ctx);
        if (set_default_ec != 1)
        {unsigned long err_ = ERR_get_error();
          char error_buffer[400];
          ERR_error_string_n(err_, error_buffer, sizeof(error_buffer));
          throw std::runtime_error("Setting default SSL verify failed \n|Error informations : \a "
            + std::string(error_buffer));
        }
      }
  connection_tcp(socket_config_addr , openssl_ctx);
}

void kc::ssl_request::request_ssl::connection_tcp(struct sockaddr_in socket_config , SSL_CTX* ssl_context)
{

  if (connect(kc::ssl_request::request_ssl::socket_fd_object, 
    (struct sockaddr*)&socket_config, sizeof(socket_config))
   < 0)
   {
    close_socket(kc::ssl_request::request_ssl::socket_fd_object);
    throw std::runtime_error("Connection TCP target server failed");
   }
  connection_ssl(ssl_context);
}

void kc::ssl_request::request_ssl::connection_ssl(SSL_CTX* ssl_context)
{
  kc::ssl_request::request_ssl::oepnssl_object = SSL_new(ssl_context);
  SSL_set_fd(kc::ssl_request::request_ssl::oepnssl_object,
    kc::ssl_request::request_ssl::socket_fd_object);
  int tlsext_host = 
  SSL_set_tlsext_host_name(kc::ssl_request::request_ssl::oepnssl_object, 
    kc::ssl_request::request_ssl::config_host_name.c_str());
    if (tlsext_host != 1) 
    { char error_buffer[400];
      unsigned long err_ = ERR_get_error();
      ERR_error_string_n(err_,error_buffer,sizeof(error_buffer));
      throw std::runtime_error("trying to add tlsext_host fialed \n| Error information:\a" + 
        std::string(error_buffer) + "Host \a > " + kc::ssl_request::request_ssl::config_host_name);
    }
  int ssl_connection_ret = SSL_connect(kc::ssl_request::request_ssl::oepnssl_object);
  if (ssl_connection_ret != 1) 
  {
    unsigned long err = ERR_get_error();
    char error_buffer[400];
    ERR_error_string_n(err, error_buffer, sizeof(error_buffer));
    throw std::runtime_error("SSL connection failed \n|Error infotmation\a" 
      + std::string(error_buffer));
  }
}

void kc::ssl_request::request_ssl::send_ssl_data(const std::string& http_tmp_data)
{
  const size_t http_tmp_data_size = http_tmp_data.size();
  const char* send_data_cstr = http_tmp_data.c_str();
  int sent_data_ret = SSL_write(kc::ssl_request::request_ssl::oepnssl_object, 
     send_data_cstr, http_tmp_data_size);
     if (sent_data_ret <= 0)
     {
      int err = SSL_get_error(kc::ssl_request::request_ssl::oepnssl_object
        , sent_data_ret);
        char error_buffer[400];
        ERR_error_string_n(ERR_get_error(), 
    error_buffer, sizeof(error_buffer));
        throw std::runtime_error
        ("An error occurred while sending the request \a | ERROR informations: \a"
          + std::string(error_buffer));
     }
    bool headers_done = false;
    std::string recv_buf;
    char resp_buffer[8192]; size_t content_length = 0;
    while (true) {
      int read_response_ret = SSL_read(kc::ssl_request::request_ssl::oepnssl_object, 
        resp_buffer,sizeof(resp_buffer));
      if (read_response_ret < 0)
      {
        char err_buf[256];
        ERR_error_string_n(ERR_get_error(), err_buf, sizeof(err_buf));
        throw std::runtime_error("SSL_read: " + std::string(err_buf));
      }
      if (read_response_ret == 0) 
      {throw std::runtime_error("The other party actively closed the SSL connection");}
      if (read_response_ret > 0) 
      {
        recv_buf.append(resp_buffer , read_response_ret);
        if (!headers_done)
        {
          size_t headers_end = recv_buf.find("\r\n\r\n");
          if (headers_end != std::string::npos) {
            headers_done = true;
            content_length = kc::ssl_request::request_ssl::response_parser 
              -> get_content_length(recv_buf);
          }
        }
        if (headers_done && content_length > 0)
        {
          size_t body_start = recv_buf.find("\r\n\r\n") + 4;
          size_t body_recevied = recv_buf.size() - body_start;
          if (body_recevied >= content_length)
          {
            kc::ssl_request::request_ssl::response_parser 
              -> set_full_responsedata(recv_buf);
            kc::ssl_request::request_ssl::response_status_code 
            = kc::ssl_request::request_ssl::response_parser -> getresponse_status_code();
            kc::ssl_request::request_ssl::response_status_message 
              = kc::ssl_request::request_ssl::response_parser -> getresponse_status_message();
            kc::ssl_request::request_ssl::response_data
              = kc::ssl_request::request_ssl::response_parser -> getresponse_body();
            kc::ssl_request::request_ssl::response_headers
              = kc::ssl_request::request_ssl::response_parser -> getresponse_headers();
            break;
          }
        }
      }
    }
}