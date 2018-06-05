#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

using namespace std;
int main()
{
    cout << "pid: " << getpid() << std::endl;
    int i = 0;
    while( 1 < 100 )
    {
        int fd = open("./test.file", O_CREAT, 777);
        if (fd == -1)
        {
            std::cout << "open file ./test.file error msg: " << strerror(errno) << std::endl;
            return 0;
        }
        sleep(1);
    }
    return 0;
}

