#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <HIRO/HIRO.h>

int main()
{
  hiro::SetAssetDirectory("./hiro_libs/assets/");
  hiro::SetIntermediateDirectory("./temp/");

  hiro::Initialize();

  while (hiro::IsOpen())
  {
    hiro::Update();
  }

  hiro::Terminate();
  return 0;
}