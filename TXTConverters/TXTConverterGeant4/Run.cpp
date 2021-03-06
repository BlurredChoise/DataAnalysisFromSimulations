#include <iostream>
#include <JPetManager/JPetManager.h>
#include "TXTModelReader.h"

int main(int argc, const char* argv[])
{
 JPetManager& manager = JPetManager::getManager();
 manager.registerTask<TXTModelReader>("TXTModelReader");
 manager.useTask("TXTModelReader", "mcGeant.raw", "myResults");
 manager.run(argc, argv);
}
