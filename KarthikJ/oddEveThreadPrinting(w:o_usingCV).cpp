#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include<condition_variable>
#include<chrono>

const int MAX = 100;
int count = 0;
std::mutex mtx;

void printEvenNum()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx); 

        if (count >= MAX)
        {
            break;
        }

        if (count % 2 == 0)
        {
            std::cout << count++ << std::endl;
            sleep(1);
        }
    }
}

void printOddNum()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx); 

        if (count >= MAX)
        {
            break;
        }

        if (count % 2 == 1)
        {
            std::cout << count++ << std::endl;
            sleep(1);
        }
    }
}

int main()
{
    std::thread t1(printEvenNum);
    std::thread t2(printOddNum);

    t1.join();
    t2.join();

    return 0;
}
