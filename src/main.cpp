#include "lib.h"

#include <iostream>

using namespace std;
// #include <spdlog/spdlog.h>

int main(int argc, char *argv[])
{
      //    auto logger = spdlog::stdout_logger_mt("console");
      //    logger->info("version {} was started", version());

      cout << "Hello world!!\n";
      cout << "PROJECT_VERSION_PATCH: " << version() << "\n";

      return 0;
}
