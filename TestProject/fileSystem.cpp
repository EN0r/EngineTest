#include "fileSystem.h"
fileSystem* fileSystem::fSystem = nullptr;

/*


*/

fileSystem::fileSystem()
{

}

fileSystem* fileSystem::getFileSystem()
{
	if (fSystem != nullptr)
		return fSystem;
	else
	{
		fSystem = new fileSystem;
		return fSystem;
	}
	return nullptr;
}
