// Copyright (c) 2026 0xNovak. All Rights Reserved.
#include <app.h>
#include <log.h>
int main(int argc, char *argv[]) {
  Log::info("initializing app");
  Application app{};
  Log::info("starting app\n");
  app.run();
  return 0;
}
