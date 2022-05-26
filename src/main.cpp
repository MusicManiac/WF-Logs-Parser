#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace ::std;

struct tradeInfo {
	string timeStamp;
	int tradeType; // 1 - buying, 2 - selling, 3 - exchange
	string offeredItems[6] = {"-","-","-","-","-","-"};
	string receivedItems[6] = {"-","-","-","-","-","-"};
	int creditsSpent;
};

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
		tradeInfo trade;
		bool processingTrade = false;
		while (getline(logFile, freshLine)) {
			if (freshLine == TRADE_BEGINNING) {
				wholeTrade.push_back(oldLine);
				wholeTrade.push_back(freshLine);
				processingTrade = true;
				continue;
			}
			if(processingTrade) {
				wholeTrade.push_back(freshLine);
				if (freshLine.empty()){
					processingTrade = false;
				}
			}
			oldLine = freshLine;
			/*
			if (freshLine == TRADE_BEGINNING) {
				cout << "Found trade beggining\n";
				trade.timeStamp = oldLine;
				processingTrade = true;
			}
			oldLine = freshLine;
			if (processingTrade == true) {
				if (freshLine.size() >=10 && freshLine.substr(2, 8) == "PLATINUM") {
				cout << "Found plat\n";
				}
			}
			*/
			
		}
		logFile.close();
	} else {
		cout << "Didn't get the file";
	}

	for (int i = 0; i < wholeTrade.size(); i++) {
		cout << wholeTrade[i] << "\n";
	}
}