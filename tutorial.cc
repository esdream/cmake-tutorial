#include <iostream>
#include "config.h"

// 如果USE_MYMATH选项打开，则使用自己编写的MathFcuntions
// 否则使用math.h
#ifdef HAVE_POW
    #include <math.h>
#else
    #include "math/MathFunctions.h"
#endif

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Version is " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << endl;

    double base = 3.2;
    int exponent = 3;

#ifdef HAVE_POW
    cout << "Use the standard library." << endl;
    cout << pow(base, exponent) << endl;
#else
    cout << "Use our math library." << endl;
    cout << power(base, exponent) << endl;
#endif
    return 0;
}