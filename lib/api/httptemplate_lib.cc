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

#include "../../include/httptmeplate.hpp"
#include <string>

void kc::http::make_template::make_http_template()
{
    switch (kc::http::make_template::_req_method) {
        case kc::method::GET:
        {
            kc::http::make_template::http_template_result += "GET ";
            break;
        }
        case kc::method::POST:
        {
            kc::http::make_template::http_template_result += "POST ";
            break;
        }        
    };
    kc::http::make_template::http_template_result += kc::http::make_template::_req_path + " ";
    kc::http::make_template::http_template_result += "HTTP/1.1\r\n";
    kc::http::make_template::http_template_result += "Host: " + kc::http::make_template::_hostname + "\r\n";
    if (kc::http::make_template::_req_method == kc::method::POST)
    {kc::http::make_template::http_template_result += "Content-Length: " + 
        std::to_string(kc::http::make_template::_req_body.size()) + "\r\n";}
    for (const auto& [headers_key , headers_value] :
         kc::http::make_template::_headers_map)
    {
        kc::http::make_template::http_template_result += headers_key + ": " + headers_value + "\r\n";
    }
    kc::http::make_template::http_template_result += "Connection: close\r\n";
    kc::http::make_template::http_template_result += "\r\n";
    if (kc::http::make_template::_req_method == kc::method::POST)
    {
        kc::http::make_template::http_template_result += 
        kc::http::make_template::_req_body;
    }
}