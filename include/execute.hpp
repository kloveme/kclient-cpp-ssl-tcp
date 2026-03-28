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

#ifndef KCLINET_EXECUTE
#define KCLINET_EXECUTE
#include "../include/Kclient.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
namespace kc {
    class Execute {
        private:
            std::string response_body;
            int response_status_code;
            std::unordered_map<std::string, std::string> response_headers;
            std::string response_status_str;
            std::string request_body;
            std::string user_config_host;
            std::string user_config_path;
            kc::method user_config_method;
            uint64_t user_config_port;
            std::unordered_map<std::string,
             std::string> user_config_headers;
            kc::kclient* _client_ptr;
        public:
        Execute(kc::kclient* client_ptr)
        :_client_ptr(std::move(client_ptr))
        {}
        inline void setBody (std::string body_data)
        { request_body = body_data;}
        void run ();
        std::string getBody();
        int getStatusCode();
        inline std::string getHeader(const std::string& key_name)
        {
            std::string query_result = response_headers[key_name];
            return query_result;
        }
        std::string getStatusMessage();
        void redirect_url (const std::string redirect_url , bool is_ssl);
    };
}

#endif