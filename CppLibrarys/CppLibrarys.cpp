#include <iostream>
using std::cout;
using std::endl;

void close();

int main()
{
    atexit(close);

    cout << "hello world!" << endl;

    system("pause");
    return 0;
}

void close() {
    if (true) {
        exit(0);
    }
    else {
        exit(-1);
    }
}
