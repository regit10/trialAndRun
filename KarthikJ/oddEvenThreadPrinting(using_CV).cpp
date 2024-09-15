#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono> 
using namespace std;

mutex mtx;
condition_variable cond;
bool isOdd = true; 

// Function to print odd numbers
void printOdd(int& count) {
    while (count < 100) {
        unique_lock<mutex> lock(mtx);
        cond.wait(lock,[]{ return isOdd; });

        cout << count << endl;
        ++count;

        isOdd = false; 
        cond.notify_all(); // To Notify

        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Function to print even numbers
void printEven(int& count) {
    while (count < 100) {
        unique_lock<mutex> lock(mtx);
        cond.wait(lock,[]{ return !isOdd; }); 

        cout << count << endl;
        ++count;

        isOdd = true; 
        cond.notify_all(); 

        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    int count = 0;
    std::thread t1([&]() { printOdd(count); });
    std::thread t2([&]() { printEven(count); });

    t1.join(); 
    t2.join(); 

    return 0;
}
