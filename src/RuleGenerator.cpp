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
std::string outputFile = "generatedCode.txt";

void title();
void readFromFile();
void countFileLines(int *numLines);
struct RawLine divideCausesImplications(std::string line);
void debugLines(struct RawLine *lines, int numLines);
void divideConditions(std::string causes);
void divideGrammar(std::string);

struct Condition {
	int componentId;
	std::string currentState;
	std::string status;
};

struct RawLine {
	int lineId;
	std::string causes;
	std::string implications;
};

int main() {
	title();

	readFromFile();

	/*cout << endl << "Press 'return' button to finish the program . . .";
	getchar();*/
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
			lines[i] = divideCausesImplications(line);
			i++;
		}
		//debugLines(lines, numLines); //Uncomment ONLY for debug
		myFile.close();
		cout << endl << "File '" + file << "' closed." << endl;
	}else cout << "Error while opening the file. Try again." << endl;

	int j;

	for(j = 0; j < numLines; j++) {
		cout << "Line[" << j << "]:" << endl;
		cout << "Causes: ";
		divideConditions(lines[j].causes);
		cout << " | Implications: ";
		divideConditions(lines[j].implications);
		cout << endl;
	}
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

struct RawLine divideCausesImplications(std::string line) {
	struct RawLine splittedLine;
	std::string delimiter = "$";
	size_t pos = 0;

	while ((pos = line.find(delimiter)) != std::string::npos) {
		splittedLine.causes = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		splittedLine.implications = line;
	}
	return splittedLine;
}

void divideConditions(std::string causes) {
	std::string delimiter = "&";
	size_t pos = 0;
	std::string str;

	while((pos = causes.find(delimiter)) != std::string::npos) {
		str = causes.substr(0, pos);
		if(!(str.compare("and") == 0 || str.compare("or") == 0)) divideGrammar(str);
		causes.erase(0, pos + delimiter.length());
	}
	divideGrammar(causes);
}

void divideGrammar(std::string cond) {
	struct Condition conditions;
	std::string delimiter = ":";
	size_t pos = 0;
	std::string str;
	int i = 0;

	while((pos = cond.find(delimiter)) != std::string::npos) {
		str = cond.substr(0, pos);
		if(i > 0) conditions.currentState = str;
		else conditions.componentId = atoi(str.c_str());
		cond.erase(0, pos + delimiter.length());
		i++;
	}
	conditions.status = cond;

	cout << " Id: " << conditions.componentId << ", Current State: "
			<< conditions.currentState << ", Status: " << conditions.status;

	ofstream myFile(path + outputFile, std::ofstream::app);
	if(myFile.is_open()) {
		myFile << "if((id == " << conditions.componentId << ") && (currentState == '" <<
				conditions.currentState <<"') && (status == '" << conditions.status << "'))" << endl;
		myFile.close();
	}else cout << "Error while counting file lines." << endl;

}

void debugLines(struct RawLine *lines, int numLines) {
	for(int i = 0; i < numLines; i++){
		cout << "Line[" << i << "] causes: " << lines[i].causes << endl
				<< "Line[" << i << "] implications: " + lines[i].implications << endl;
	}
}

void title() {
	cout << " ________________________"  << endl;
	cout << "|                        |" << endl;
	cout << "| Rule Generator Program |" << endl;
	cout << "|________________________|" << endl;
	cout << endl;
}
