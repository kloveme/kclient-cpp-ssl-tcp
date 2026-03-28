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

#ifndef KCLIENT_HTTP_PARSER
#define KCLIENT_HTTP_PARSER

#include <cstddef>
#include <string>
#include <unordered_map>
namespace kc {
    namespace data_parser 
    {
        //http parser
        class http_parser {
            private:
            std::string staus_message;
            int status_code;
            int status_http_code;
            std::string response_body;
            std::string full_response_data;
            bool response_is_chunked;
            std::unordered_map<std::string, std::string> response_headers_map;
            public:
               size_t get_content_length (const std::string& headers_data);
               void set_full_responsedata (const std::string& full_data);
               std::string getresponse_status_message ();
               std::string getresponse_body ();
               int getresponse_status_code ();
               std::unordered_map<std::string, std::string> getresponse_headers();
               void is_chunked (bool is_chunked);
               //Parser function
               void start();
               void parser_header_information_func();
               void parser_headers_func();
               std::string trim(const std::string& str) {
                size_t start = str.find_first_not_of(" \t\r\n");
                if (start == std::string::npos) return "";
                size_t end = str.find_last_not_of(" \t\r\n");
                return str.substr(start, end - start + 1);
                }
        };

        //websocket parser
    }
}

#endif