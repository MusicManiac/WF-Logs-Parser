#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tradeParser.h>

using namespace ::std;

const string TRADE_BEGINNING = "	TRADED ITEMS GIVEN :";


int main(void) {

	string filename = "";

	cout << "Filename (with extension, looks like \"numbers_yourNickname_GDPR_Trades_Warframe.txt\"):";
	cin >> filename;

	fstream logFile;
	ofstream csvFile;

	csvFile.open("ParsedTrades.csv", std::ofstream::out | std::ofstream::trunc); // erase current csv file if present
	csvFile.close();

	logFile.open(filename, ios::in);
	csvFile.open("ParsedTrades.csv", ios::app);
	csvFile << "Date,Offered Item 1,Offered Item 2,Offered Item 3,Offered Item 4,Offered Item 5,Offered Item 6,Received Item 1,Received Item 2,Received Item 3,Received Item 4,Received Item 5,Received Item 6,Creds Spent,Trade Type\n"; // header for csv

	if (logFile.is_open() && csvFile.is_open())
	{
		string freshLine = "", oldLine = "";
		bool processingTrade = false;
		vector<string> wholeTrade;
		while (getline(logFile, freshLine)) {
			if (freshLine == TRADE_BEGINNING) { // save previous (date) and current line to vector, since we know it's a trade
				wholeTrade.push_back(oldLine);
				wholeTrade.push_back(freshLine);
				processingTrade = true; // flag to know we're still doing the trade
				continue;
			}
			if(processingTrade) { // keep pushing lines into vector until we find empty line
				if (freshLine.empty() || logFile.eof()){
					processingTrade = false; // uncheck the flag once empty line is found
					if (logFile.eof()) {
						wholeTrade.push_back(freshLine);
					}
					csvFile << tradeIntoCSV(wholeTrade);
					wholeTrade.clear();
					continue;
				}
				wholeTrade.push_back(freshLine);
			}
			oldLine = freshLine; // save previous line, since we won't know we're in a trade until we find "	TRADED ITEMS GIVEN :" line
		}
		logFile.close();
	}
	else {
		cout << "Didn't get the file";
	}
	return 0;
}