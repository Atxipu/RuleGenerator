//============================================================================
// Name        : RuleGenerator.cpp
// Author      : Asier
// Version     :
// Copyright   : Copyleft
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;

std::string path = "C:/Users/Asier/eclipse-workspace/RuleGenerator/";
std::string file = "rules.txt";

void title();
void readFromFile();
void countFileLines(int *numLines);
struct RawLine divideCauseImplication(std::string line);
void debugLines(struct RawLine *lines, int numLines);

struct Condition {
	int componentId;
	std::string currentState;
	std::string status;
};

struct RawLine {
	int lineId;
	std::string cause;
	std::string implication;
};

int main() {
	title();

	readFromFile();

	cout << endl << "Press 'return' button to finish the program . . .";
	getchar();
	return 0;
}

void readFromFile() {
	struct RawLine *lines;
	int numLines = 0;

	countFileLines(&numLines);
	cout << " value: " << numLines << endl;

	cout << "Opening file '" + file << "' . . .";
	ifstream myFile(path + file);
	if(myFile.is_open()) {
		cout << " opened." << endl;

		lines = new RawLine[numLines];

		cout << "Reading RULES from "<< file <<" . . ." << endl << endl;
		int i = 0;
		std::string line;
		while(std::getline(myFile, line)) {
			lines[i] = divideCauseImplication(line);
			i++;
		}
		debugLines(lines, numLines);
		myFile.close();
		cout << endl << "File '" + file << "' closed." << endl;
	}else cout << "Error while opening the file. Try again." << endl;
}

void countFileLines(int *numLines) {
	ifstream myFile(path + file);
	std:string str;

	cout << "Calculating file lines counter . . .";
	if(myFile.is_open()) {
		while(std::getline(myFile, str)) (*numLines)++;
		myFile.close();
	}else cout << "Error while counting file lines." << endl;
}

struct RawLine divideCauseImplication(std::string line) {
	struct RawLine splittedLine;
	std::string delimiter = "$";
	size_t pos = 0;

	while ((pos = line.find(delimiter)) != std::string::npos) {
		splittedLine.cause = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		splittedLine.implication = line;
	}
	return splittedLine;
}

void debugLines(struct RawLine *lines, int numLines) {
	for(int i = 0; i < numLines; i++){
		cout << "Line[" << i << "] causes: " << lines[i].cause << endl
				<< "Line[" << i << "] implications: " + lines[i].implication << endl;
	}
}

void title() {
	cout << " ________________________"  << endl;
	cout << "|                        |" << endl;
	cout << "| Rule Generator Program |" << endl;
	cout << "|________________________|" << endl;
	cout << endl;
}
