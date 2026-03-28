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

#ifndef KCLIENT_HTTPTEMPLATE
#define KCLIENT_HTTPTEMPLATE

#include "Kclient.hpp"
#include <string>
#include <unordered_map>

namespace kc {
    namespace http {
        class make_template {
            private:
                std::string _hostname;
                kc::method _req_method;
                std::string _req_body;
                std::string _req_path;
                std::unordered_map<std::string,
                    std::string> _headers_map;
                std::string http_template_result;
            public:
            make_template
            (const std::string& host_name ,kc::method& method_name
                ,const std::string& req_body , const std::string& req_path)
                :_hostname(host_name),_req_method(method_name), _req_body(req_body) ,
                _req_path(req_path){}
            inline void headers
            (std::unordered_map<std::string, std::string>& headers_map)
            { _headers_map = headers_map;}
            void make_http_template();
            std::string get_http_template()
            {return http_template_result;}
        };
    }
}

#endif