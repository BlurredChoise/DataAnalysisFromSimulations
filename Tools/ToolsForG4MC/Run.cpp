#include <iostream>
#include <JPetManager/JPetManager.h>
#include "G4MCReader/G4MCReader.h"

int main(int argc, const char* argv[])
{
 JPetManager& manager = JPetManager::getManager();
 manager.registerTask<ToolsForG4MC::G4MCReader>("G4MCReader");
 manager.useTask("G4MCReader", "mc", "results");
 manager.run(argc, argv);
}
