#include<iostream>
#include "myLib.h"
#include<dlfcn.h>


using namespace std;

void loadLibrary(){

    void* handle = dlopen("./libmylib.so", RTLD_LAZY);
    if (!handle) {
        cerr << "Error: Unable to load library: " << dlerror() << endl;
        return;
    }

    dlerror();

    typedef int (*func_int_t)(int, int);
    typedef float (*func_float_t)(float, int);

    func_int_t add = (func_int_t) dlsym(handle, "add");
    func_int_t difference = (func_int_t) dlsym(handle, "difference");
    func_int_t product = (func_int_t) dlsym(handle, "product");
    func_float_t divide = (func_float_t) dlsym(handle, "divide");

    const char* error;
    if ((error = dlerror()) != NULL) {
        cerr << "Error: Unable to load function: " << error << endl;
        dlclose(handle);
        return;
    }

    int a,b, isTrue=1;
    while(isTrue){
        cout<<"\n\nchoose one of the options:\n 1) Addition \n 2) Subtraction \n 3) Multiplication \n 4) Division\n 5) Exit!\n\n";
        int choice;
        cin>>choice;

        switch (choice)
        {
        case 1:
            cout<<"Enter the two numbers a and b: "<<endl;
            cin>>a>>b; 
            cout<<a<<"+"<<b<<"="<<add(a,b)<<"\n";
            break;
        
        case 2:
            cout<<"Enter the two numbers a and b: "<<endl;
            cin>>a>>b;
            cout<<a<<"-"<<b<<"="<<difference(a,b)<<"\n";
            break;

        case 3:
            cout<<"Enter the two numbers a and b: "<<endl;
            cin>>a>>b;
            cout<<a<<"*"<<b<<"="<<product(a,b)<<"\n";
            break;

        case 4:
            cout<<"Enter the two numbers a and b: "<<endl;
            cin>>a>>b;
            cout<<a<<"/"<<b<<"="<<divide(float(a),b)<<"\n";
            break;

        case 5:
            isTrue = 0;
            break;

        default:
            cout<<"Please enter a valid option!\n";
            break;
        }

    }
    
    dlclose(handle);

}



int main(){
    cout<<"Calling loadLibrary to dynamically load and use the shared library..!\n";
    loadLibrary();

    return 0;
}