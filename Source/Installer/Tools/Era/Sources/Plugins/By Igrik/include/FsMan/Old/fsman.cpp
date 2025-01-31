#include <string>
#include <vector>
#include <windows.h>
#include "fsman.hpp"
#include <iostream>

namespace fsman 
{

  std::string getCurrentDirectory () {
    int bufSize = GetCurrentDirectoryA(0, NULL);

    if (bufSize > 0) {
      std::vector<char> buf;
      buf.resize(bufSize);

      bufSize = GetCurrentDirectoryA(bufSize, &buf[0]);

      if (bufSize > 0 && bufSize <= buf.size()) {
        std::string result(buf.begin(), buf.begin() + bufSize);

        return result;
      }
    }

    return "";
  }

  std::string expandFilePath (const std::string &filePath) {
    int bufSize = GetFullPathNameA(filePath.c_str(), 0, NULL, NULL);

    if (bufSize > 0) {
      std::vector<char> buf;
      buf.resize(bufSize);

      bufSize = GetFullPathNameA(filePath.c_str(), bufSize, &buf[0], NULL);

      if (bufSize > 0 && bufSize <= buf.size()) {
        // Strip trailing path delimiter
        if ((buf[bufSize - 1] == '\\' || buf[bufSize - 1] == '/') && bufSize >= 2 && buf[bufSize - 2] != ':') {
          bufSize--;
        }

        std::string result(buf.begin(), buf.begin() + bufSize);

        return result;
      }
    }

    return "";
  }

  bool isAbsPath (const std::string &filePath) {
    return filePath.length() >= 1 && (filePath[0] == '\\' || filePath[0] == '/' || (filePath.length() >= 2 && filePath[1] == ':'));
  }

  std::vector<char> getDriveList () {
    unsigned int       drivesMask  = GetLogicalDrives();
    unsigned int       bitTester   = 1;
    char               driveLetter = 'A';
    const unsigned int alphabetLen = 26;
    const unsigned int stopBit     = 1 << alphabetLen - 1;
    std::vector<char> result;

    while (bitTester < stopBit) {
      if (drivesMask & bitTester) {
        result.push_back(driveLetter);
      }

      driveLetter++;
      bitTester <<= 1;
    }

    return result;
  }

  FsMan::FsMan (const std::string &initialDirectory) {
    this->_currentDirectory = fsman::expandFilePath(initialDirectory);
  }

  const std::string& FsMan::currentDirectory() {
    return this->_currentDirectory;
  }

  std::string FsMan::expandFilePath (const std::string &filePath) {
    return fsman::expandFilePath(isAbsPath(filePath) ? filePath : this->_currentDirectory + "\\" + filePath);
  }

  bool FsMan::changeDirectory (const std::string &dirPath) {
    std::string expandedPath = this->expandFilePath(dirPath);

    bool result = expandedPath != "";

    if (result) {
      this->_currentDirectory = expandedPath;
    }

    return result;
  }

  std::vector<std::string> FsMan::listDirectories () {
    std::vector<std::string> result;
    WIN32_FIND_DATAA foundRec;
    HANDLE searchHandle = FindFirstFileA((this->_currentDirectory + "\\*").c_str(), &foundRec);

    if (searchHandle == INVALID_HANDLE_VALUE) {
      result.push_back("..");
    } else {
      if (std::string(foundRec.cFileName) != "." && (foundRec.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        result.push_back(foundRec.cFileName);
      }

      while (FindNextFileA(searchHandle, &foundRec)) {
        if (std::string(foundRec.cFileName) != "." && (foundRec.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
          result.push_back(foundRec.cFileName);
        }
      }

      FindClose(searchHandle);
    }

    return result;
  }

  std::vector<std::string> FsMan::listFiles (const std::string &fileMask) {
    std::vector<std::string> result;
    WIN32_FIND_DATAA foundRec;
    HANDLE searchHandle = FindFirstFileA((this->_currentDirectory + "\\" + fileMask).c_str(), &foundRec);

    if (searchHandle != INVALID_HANDLE_VALUE) {
      if (std::string(foundRec.cFileName) != "." && !(foundRec.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        result.push_back(foundRec.cFileName);
      }

      while (FindNextFileA(searchHandle, &foundRec)) {
        if (std::string(foundRec.cFileName) != "." && !(foundRec.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
          result.push_back(foundRec.cFileName);
        }
      }

      FindClose(searchHandle);
    }

    return result;
  }

} // .namespace fsman
