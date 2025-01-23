#ifndef FSMAN_HEADER
#define FSMAN_HEADER

#include <windows.h>
#include <string>
#include <vector>

namespace fsman 
{

    /* Global file system functions */
    std::string getCurrentDirectory();
    std::string expandFilePath (const std::string &filePath);
    bool isAbsPath (const std::string &filePath);
    std::vector<char> getDriveList ();

    /* File system manager for open/save dialogs */
    class FsMan 
    {
     protected:
      std::string _currentDirectory;

     public:
      FsMan (const std::string &initialDirectory = ".");
      const std::string& currentDirectory();
      std::string expandFilePath(const std::string &filePath);
      bool changeDirectory(const std::string &dirPath);
      std::vector<std::string> listDirectories();
      std::vector<std::string> listFiles(const std::string &fileMask);
    }; // .class FsMan

} // .namespace fsman

#endif
