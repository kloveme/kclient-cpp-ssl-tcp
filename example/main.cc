#include "../include/Kclient.hpp"
#include "../include/execute.hpp"
#include <iostream>
#include <stdexcept>

using namespace kc;

int main () {
    const std::string user_agent = 
    "Mozilla/5.0 (X11; Linux x86_64; rv:149.0) Gecko/20100101 Firefox/149.0";
    try {
        clientPtr cp = kclient::newClient();
        cp-> setHost(method::GET,"api.github.com")
            .setPath("/users/octocat")
            .addHeaders("User-Agent", user_agent)
            .SSL(true);
        Execute exec(cp.get());
        exec.run();
        const int response_status_code = exec.getStatusCode();
        const std::string response_status_message = exec.getStatusMessage();
        const std::string response_body = exec.getBody();
        const std::string query_content_length = exec.getHeader("Content-Length");
        std::cout << "Code : \a" << response_status_code << std::endl; 
        std::cout << "Status : \a" << response_status_message << std::endl; 
        std::cout << "Body : \a\n" << response_body << std::endl;
        std::cout << "Content length : \a" << query_content_length << std::endl;
    }catch (std::runtime_error error_)
    {std::cout << error_.what() << std::endl;}
}