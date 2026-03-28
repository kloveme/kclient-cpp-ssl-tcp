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

#include "../../include/core/http_parser/parser.hpp"
#include <cstddef>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <unordered_map>

size_t kc::data_parser::http_parser::get_content_length
    (const std::string &headers_data)
{
    size_t content_length_pos = headers_data.find("Content-Length:");
    if (content_length_pos == std::string::npos) 
    {return 0;}
    size_t colon = headers_data.find(":" , content_length_pos);
    if (colon == std::string::npos)
    {return 0;}
    size_t start = headers_data.find_first_not_of("\t\r\n" , colon + 1);
    if (start == std::string::npos){return 0;}
    size_t end = headers_data.find_first_of("\r\n" , start);
    if (end == std::string::npos)
    {return 0;}
    std::string len_str = headers_data.substr(start , end - start);
    return std::stol(len_str);
}

void kc::data_parser::http_parser::is_chunked(bool is_chunked)
{kc::data_parser::http_parser::response_is_chunked = is_chunked;}

void kc::data_parser::http_parser::set_full_responsedata(const std::string& full_data)
{kc::data_parser::http_parser::full_response_data = full_data; 
    parser_header_information_func(); parser_headers_func();}

void kc::data_parser::http_parser::parser_header_information_func()
{
    size_t line_end = kc::data_parser::http_parser::full_response_data.find("\r\n");
    if (line_end == std::string::npos) {throw std::runtime_error("Parser failed error response : \a"+full_response_data);}
    std::string status_line = kc::data_parser::http_parser::full_response_data.substr
    (0 , line_end);
    size_t space_1_ops = status_line.find(' ');
    size_t space_2_ops = status_line.find(' ',space_1_ops + 1);
    std::string code_str = status_line.substr
    (space_1_ops + 1 , space_2_ops - space_1_ops - 1);
    kc::data_parser::http_parser::status_code = std::stoi(code_str);
    kc::data_parser::http_parser::staus_message = status_line.substr(space_2_ops + 1);
}

void kc::data_parser::http_parser::parser_headers_func()
{
    size_t status_line_end = full_response_data.find("\r\n");
    size_t headers_end = full_response_data.find("\r\n\r\n");
    size_t headers_start = status_line_end + 2;
    size_t headers_length = headers_end - headers_start;
    std::string full_headers_str = full_response_data.substr(headers_start , headers_length);
    kc::data_parser::http_parser::response_body = full_response_data.substr(headers_end + 4);
    size_t now_pos = 0;
    while (now_pos < full_headers_str.size()) {
        size_t eol = full_headers_str.find("\r\n" , now_pos);
        if (eol == std::string::npos) break;
        std::string header_line = full_headers_str.substr(now_pos , eol - now_pos);
        size_t colon = header_line.find(":");
        if (colon != std::string::npos) 
        {
            std::string headers_key = trim(header_line.substr(0,colon));
            std::string headers_value = trim(header_line.substr(colon + 1));
            kc::data_parser::http_parser::response_headers_map[headers_key]=headers_value;
        }
        now_pos = eol + 2;
    }
}

int kc::data_parser::http_parser::getresponse_status_code() 
{return kc::data_parser::http_parser::status_code;}
std::string kc::data_parser::http_parser::getresponse_status_message()
{return kc::data_parser::http_parser::staus_message;}
std::string kc::data_parser::http_parser::getresponse_body() 
{return kc::data_parser::http_parser::response_body;}
std::unordered_map<std::string, std::string> kc::data_parser::http_parser::getresponse_headers()
{return kc::data_parser::http_parser::response_headers_map;}