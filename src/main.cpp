#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace ::std;

const string TRADE_BEGINNING = "	TRADED ITEMS GIVEN :";


int main(void) {
	string filename = "test.txt";

	//cout << "Filename:";
	//cin >> filename;

	fstream logFile;

	vector<string> wholeTrade;

	logFile.open(filename , ios::in);
	if (logFile.is_open()) {
		string freshLine = "", oldLine = "";
		bool processingTrade = false;
		while (getline(logFile, freshLine)) {
			if (freshLine == TRADE_BEGINNING) { // save previous (date) and current line to vector, since we know it's a trade
				wholeTrade.push_back(oldLine);
				wholeTrade.push_back(freshLine);
				processingTrade = true; // flag to know we're still doing the trade
				continue;
			}
			if(processingTrade) { // keep pushing lines into vector until we find empty line
				wholeTrade.push_back(freshLine);
				if (freshLine.empty()){
					processingTrade = false; // uncheck the flag once empy line is found
				}
			}
			oldLine = freshLine; // save previous line, since we won't know we're in a trade until we find "	TRADED ITEMS GIVEN :" line
		}
		logFile.close();
	} else {
		cout << "Didn't get the file";
	}
	return 0;
}