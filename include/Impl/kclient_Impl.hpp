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

#ifndef KCLINET_HEADEFILE_IMPL
#define KCLINET_HEADEFILE_IMPL

#include "../Kclient.hpp"
#include <string>
#include <unordered_map>

namespace kc::Impl {
    class kclient_Impl : public kc::kclient {
        private:
            long timeout_number; 
            std::string config_hostname;
            std::string config_path;
            kc::method config_method;
            bool config_is_ssl;
            std::unordered_map<std::string, std::string> headers_map;
        public:
            ~kclient_Impl() = default;
            kclient_Impl& setHost(const kc::method &req_method, const std::string &hostname) override;
            kclient_Impl& setPath(const std::string &req_path) override;
            kclient_Impl& addHeaders(const std::string &headers_key, const std::string &headers_value) override;
            kclient_Impl& timeout(long req_timeout) override;
            kclient_Impl& SSL(bool ssl) override;
            inline std::string get_config_hostname () {return config_hostname;}
            inline std::string get_config_path () {return config_path;}
            inline kc::method get_config_method () {return config_method;}
            inline bool get_ssl_used_verifiction () {return config_is_ssl;}
            inline std::unordered_map<std::string, std::string>& get_config_headers ()
            {return headers_map;}
    };
}

#endif
