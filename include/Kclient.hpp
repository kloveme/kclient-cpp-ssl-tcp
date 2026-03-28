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

#ifndef KCLINET_HEADEFILE
#define KCLINET_HEADEFILE

#include <memory>
#include <string>
#include <sys/socket.h>
namespace kc {
    enum class method {
        GET,
        POST,
    };
    class kclient {
        public:
            virtual ~kclient() = default;
            virtual kclient& setHost(const kc::method& req_method , 
                const std::string& hostname) = 0;
            virtual kclient& setPath(const std::string& 
                req_path) = 0;
            virtual kclient& addHeaders(const std::string& headers_key , 
                const std::string& headers_value) = 0;
            virtual kclient& timeout(long req_timeout) = 0;
            virtual kclient& SSL(bool ssl) = 0;
            static std::unique_ptr<kc::kclient> newClient ();
    };
    using clientPtr = std::unique_ptr
        <kc::kclient>;
}

#endif