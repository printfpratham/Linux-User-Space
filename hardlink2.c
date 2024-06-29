#include <stdio.h>
#include <unistd.h>



int main()
{
        int ret;
        ret = link("hardlink.txt","hardlink2.txt");
        if(ret != 0)
                perror("hardlink error\n");
}
