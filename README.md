<head>
  <link rel="stylesheet" type="text/css" href="/readme.css">
</head>
<div class="author">
    <div>
        <img class="author_pictures" src="/Github-Assets/头像.jpg" alt="头像">
    </div>
    <div class="author_information-txt">
        <h3>Author : Kloveme </h3>
        <span>Project name : Kclient</span>
        <span>Github Home: https://github.com/kloveme</span>
        <div style="margin-top: 5px;" class="other_box">
            <button>😁 Hai bro! Star on GitHub</button>
        </div>
    </div> 
</div>
<br>
<div class="project-intorduction">
    <div class="project_infotmations">
        <div class="information">
            <div class="logo_tags">
                <img class="project_logo" src="/Github-Assets/LOGO.png" alt="Mylogo">
                <div class="intorduction-porject_tags">
                        <img src="https://img.shields.io/badge/Linux-FCC624?logo=linux&logoColor=black" />
                        <img src="https://img.shields.io/badge/C%2B%2B-17-blue" />
                        <img src="https://img.shields.io/badge/HTTP-HTTPS-green" />
                        <img src="https://img.shields.io/badge/License-MIT-yellow" />
                </div>
            </div>
            <div class="information-txt">
                <div class="basic_information">
                    <span>Version : 0.1.0 </span><br>
                    <span>Language : C ++ 17</span><br>
                </div>
                <div style="font-size: 14px; padding: 10px;" class="information-txt_intorduction">
                    This project is written based on POSIX standard sockets 
                    and the OpenSSL library. Since my development environment is a Linux system, 
                    support for Windows is not particularly complete and will need to be gradually rectified 
                    later. It requires everyone's testing and suggestions. If you encounter missing 
                    OpenSSL dependencies during compilation, please refer to the documentation 
                    [4] below
                </div>
            </div>
        </div>
    </div>
</div>
<br>
<div class="project_api">
    <span style="font-weight: bold; color: blanchedalmond; font-size: 23px;">Next, I will explain the usage method : </span>
<pre> 
<code class="code-box" style="overflow-x: auto;">[1] Include the required header files
//This header file contains the client configuration method 
functions
#include "../include/Kclient.hpp"
//This header file contains the execution of sending and 
receiving access request responses by the actuator user
#include "../include/execute.hpp"
</code>
</pre>

<pre> 
<code class="code-box" style="overflow-x: auto;">[2] Configuration Request
//We take a random Github API as an example
// We take a random Github API as an example

clientPtr cp = kclient::newClient();
// Here we create a client pointer 
// This function is a static function, 
// so there is no need to create a class object, 
// and we can call it directly. It will return a 'unique_ptr' pointer.

cp->setHost(method::GET, "api.github.com")
// setHost() - Configure the target host and request method
// Parameters: 
//   - method::GET/POST/PUT/DELETE (HTTP method)
//   - "api.github.com" (target server address)
// Returns: kclient& (for chaining calls)

  .setPath("/users/octocat")
// setPath() - Set the request path
// Parameters:
//   - "/users/octocat" (API endpoint path)
// Returns: kclient& (for chaining calls)

  .addHeaders("User-Agent", user_agent)
// addHeaders() - Add HTTP headers to the request
// Parameters:
//   - "User-Agent" (header name)
//   - user_agent (header value, e.g., browser identifier)
// Returns: kclient& (for chaining calls)

  .SSL(true);
// SSL() - Enable/disable HTTPS encryption
// Parameters:
//   - true (enable HTTPS, use port 443)
//   - false (use HTTP, port 80)
// Returns: kclient& (for chaining calls)
</code>
</pre>

<pre>
<code class="code-box" style="overflow-x: auto;">[3] Execute requests and obtain and access response content 
Execute exec(cp.get());
// Create executor with client pointer (cp.get() returns raw pointer from unique_ptr)
// The executor is responsible for sending the request and storing the response

exec.run();
// Execute the HTTP request (blocking call)
// Performs: TCP connection → Send request → Receive response → Parse headers & body

const int response_status_code = exec.getStatusCode();
// Get HTTP status code (e.g., 200 = OK, 404 = Not Found, 500 = Server Error)

const std::string response_status_message = exec.getStatusMessage();
// Get HTTP status message (e.g., "OK", "Not Found", "Internal Server Error")

const std::string response_body = exec.getBody();
// Get response body as string (supports text, JSON, binary data)

const std::string headers_xxx = exec.getHeader("key_name");
// Get specific header value by key (e.g., "Content-Type", "Content-Length")
// Returns empty string if header doesn't exist
</code>
</pre>


<pre><code class="code-box" style="overflow-x: auto;">[4] Compilation issue
If you encounter a missing OpenSSL dependency when compiling with CMake,
please download according to your system. Here is a list of download 
tutorials 
INSTALL OpenSSL
<div class="download">LINUX 🐧
Linux Arch
    <code>sudo pacman -S oepnssl</code>
Linux Ubuntu
    <code>sudo apt upadate
sudo apt install libssl-dev</code>
Linux Fedora/REHL/CentOS
    <code>sudo dnf install openssl-devel
or sudo yum install openssl-devel</code>
Linux OpenSUSE
    <code>sudo zypper install libopenssl-devel</code>
Linux Alpine Linux
    <code>sudo apk add openssl-dev</code>

Windows 🪟
 1. Open https://slproweb.com/products/Win32OpenSSL.html
 2. Download -> Win64 OpenSSL v3.x
 3. Install,click -> "Copy DLLs to /bin"
 4. Next,ok

If you cannot open this Windows download link, please get 
the '.exe' installer in my project folder 
'Windows_openssl_package' 📦

If you are a Windows or Linux user and the compilation fails, you can put the log in 
'Issue' and tell me. I will reply to you and fix it because my development 
machine is Linux, so I can't know the Windows bugs and compilation dependencies
very well 😭 or you can tell me about any series of problems you encounter while 
using it,and I will handle them promptly!

!!!!!!!!!!!!!!!
I'm 16 and my code is really bad, 
don't criticize me, I just wrote it 
simply to pass the timeIncluding 
variable name spelling errors and 
the implementation being too simple-minded, 
there are some parts I don't quite understand, 
so I wrote it according to my own thinking
!!!!!!!!!!!!!!!
</div>
</code>
</pre>
</div>
</div>
