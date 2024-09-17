#include<iostream>
#include<cstdlib>

extern "C"{

int add(int a,int b){
    return a+b;
}

int difference(int a ,int b){
    return abs(a-b);
}

int product(int a,int b){
    return a*b;
}

float divide(float a,int b){
    if(b!=0) return a/b;
    else return 0;
}

}