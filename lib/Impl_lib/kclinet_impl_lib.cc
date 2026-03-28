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

#include "../../include/Impl/kclient_Impl.hpp"
#include <string>

kc::Impl::kclient_Impl& kc::Impl::kclient_Impl::setHost(const kc::method &req_method, const std::string &hostname)
{
    kc::Impl::kclient_Impl::config_method = req_method;
    kc::Impl::kclient_Impl::config_hostname = hostname;
    return *this;
}

kc::Impl::kclient_Impl& kc::Impl::kclient_Impl::setPath(const std::string &req_path)
{
    kc::Impl::kclient_Impl::config_path = req_path;
    return *this;
}

kc::Impl::kclient_Impl& kc::Impl::kclient_Impl::addHeaders(const std::string &headers_key, const std::string &headers_value)
{
    kc::Impl::kclient_Impl::headers_map[headers_key] = headers_value;
    return *this;
}

kc::Impl::kclient_Impl& kc::Impl::kclient_Impl::SSL(bool ssl)
{
    kc::Impl::kclient_Impl::config_is_ssl = ssl;
    return *this;
}

kc::Impl::kclient_Impl& kc::Impl::kclient_Impl::timeout(long req_timeout)
{
    kc::Impl::kclient_Impl::timeout_number = req_timeout;
    return *this;
}