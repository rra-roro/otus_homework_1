#include "lib.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
      (void)argc;
      (void)argv;

      cout << "Hello world!!\n";
      cout << "PROJECT_VERSION_PATCH: " << version() << "\n";

      return 0;
}
