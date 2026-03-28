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

#include "../../include/execute.hpp"
#include "../../include/httptmeplate.hpp"
#include "../../include/Impl/kclient_Impl.hpp"
#include "../../include/core/tcp_request.hpp"
#include "../../include/core/ssl_request.hpp"
#include <bits/types/locale_t.h>
#include <cstddef>
#include <cstdio>
#include <string>

void kc::Execute::run()
{
    kc::Impl::kclient_Impl* client_impl_ptr
        = dynamic_cast<kc::Impl::kclient_Impl*
        >(kc::Execute::_client_ptr);
    kc::Execute::user_config_host = 
    client_impl_ptr -> get_config_hostname();
    kc::Execute::user_config_method =
    client_impl_ptr -> get_config_method();
    kc::Execute::user_config_headers = 
    client_impl_ptr -> get_config_headers();
    kc::Execute::user_config_path =
    client_impl_ptr -> get_config_path();
    kc::http::make_template make_http_tmp(kc::Execute::user_config_host ,
         kc::Execute::user_config_method , kc::Execute::request_body ,
          kc::Execute::user_config_path);
    make_http_tmp.headers(kc::Execute::user_config_headers);
    make_http_tmp.make_http_template();
    const std::string http_tmp = make_http_tmp.get_http_template();
    if (client_impl_ptr -> get_ssl_used_verifiction())
    {
        kc::ssl_request::request_ssl request_ssl;
        request_ssl.init_socket_ssl(kc::Execute::user_config_host);
        request_ssl.send_ssl_data(http_tmp);
        kc::Execute::response_status_code = request_ssl.get_response_code();
        kc::Execute::response_status_str = request_ssl.get_response_message();
        kc::Execute::response_headers = request_ssl.get_response_headers();
        kc::Execute::response_body = request_ssl.get_response_body();
        if (kc::Execute::response_status_code == 302 || kc::Execute::response_status_code
            == 307 || kc::Execute::response_status_code == 301 || kc::Execute::response_status_code == 308)
            {redirect_url(getHeader("Location"), true);}
        return;
    }
    kc::tcp_request::request_tcp request_tcp;
    request_tcp.init_socket(kc::Execute::user_config_host);
    request_tcp.send_data(http_tmp);
    kc::Execute::response_status_code = request_tcp.get_response_code();
    kc::Execute::response_status_str = request_tcp.get_response_message();
    kc::Execute::response_headers = request_tcp.get_response_headers();
    kc::Execute::response_body = request_tcp.get_response_body();
    if (kc::Execute::response_status_code == 302 || kc::Execute::response_status_code
        == 307 || kc::Execute::response_status_code == 301 || kc::Execute::response_status_code == 308)
        {redirect_url(getHeader("Location"), false);}
}

void kc::Execute::redirect_url(const std::string redirect_url , bool is_ssl) 
{
    size_t https_ops = redirect_url.find("https");
    size_t http_ops = redirect_url.find("");
    std::string current_host;
    std::string current_path;
    if (http_ops != std::string::npos || http_ops != std::string::npos)
    {
        size_t link_start = (https_ops != std::string::npos) 
        ? https_ops + 8 : http_ops + 7;
        size_t slash = redirect_url.find("/" , link_start);
        if (slash != std::string::npos) 
        {
            current_host = redirect_url.substr(link_start , slash - link_start);
            current_path = redirect_url.substr(slash);
        }
        else {
            current_host = redirect_url.substr(link_start);
            current_path = "/";            
        }
    }

    kc::http::make_template make_http_tmp(current_host , 
        kc::Execute::user_config_method , request_body
         , current_path);
        make_http_tmp.make_http_template();
        const std::string http_tmp = make_http_tmp.get_http_template();
    if (is_ssl){
        kc::ssl_request::request_ssl ssl_req;
        ssl_req.init_socket_ssl(current_host);
        ssl_req.send_ssl_data(http_tmp);
        kc::Execute::response_status_code = ssl_req.get_response_code();
        kc::Execute::response_status_str = ssl_req.get_response_message();
        kc::Execute::response_headers = ssl_req.get_response_headers();
        kc::Execute::response_body = ssl_req.get_response_body();
        return;
    }
    kc::tcp_request::request_tcp tcp_req;
    tcp_req.init_socket(current_host);
    tcp_req.send_data(http_tmp);
    kc::Execute::response_status_code = tcp_req.get_response_code();
    kc::Execute::response_status_str = tcp_req.get_response_message();
    kc::Execute::response_headers = tcp_req.get_response_headers();
    kc::Execute::response_body = tcp_req.get_response_body();
}

std::string kc::Execute::getBody() 
{return kc::Execute::response_body;}
std::string kc::Execute::getStatusMessage()
{return kc::Execute::response_status_str;}
int kc::Execute::getStatusCode()
{return kc::Execute::response_status_code;}