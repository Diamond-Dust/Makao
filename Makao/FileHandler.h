#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "PlayerInfo.h"

class FileHandler {
private:
	FILE* fileStream;
public:
	FileHandler();
	FileHandler(const char* cString, const char* mode);
	void Open(const char* cString, const char* mode);
	void PrintMessage(char* cString);
	void FileHandler::PrintSimEnd(int numOfGames, double timePerGame, int nameLength, std::vector<PlayerInfo> & PI);	
	~FileHandler();
};