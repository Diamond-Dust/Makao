#include "FileHandler.h"

FileHandler::FileHandler() {
}

FileHandler::FileHandler(const char * cString, const char* mode) {
	fileStream = fopen(cString, mode);
	if (fileStream == NULL) {
		fprintf(stderr, "Can't open output file!\n");
		exit(1);
	}
}

void FileHandler::Open(const char * cString, const char * mode) {
	fclose(fileStream);
	fileStream = fopen(cString, mode);
	if (fileStream == NULL) {
		fprintf(stderr, "Can't open output file!\n");
		exit(1);
	}
}

void FileHandler::PrintMessage(char * cString) {
	fprintf(fileStream, cString);
}

void FileHandler::PrintSimEnd(int numOfGames, double timePerGame, int nameLength, std::vector<PlayerInfo> & PI) {
	fprintf(fileStream, "Makao simulation with:\t%d games\n", numOfGames);
	fprintf(fileStream, "\tAverage time per game:\t%lf\n", timePerGame);
	for (int i = 0; i < PI.size(); i++)
		fprintf(fileStream, "\t%-*s\t%d\n", nameLength, PI[i].name.c_str(), PI[i].points);
	fflush(fileStream);
}


FileHandler::~FileHandler() {
	fclose(fileStream);
}
