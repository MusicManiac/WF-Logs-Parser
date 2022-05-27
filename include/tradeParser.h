#include <string>
#include <vector>

using namespace ::std;

const string ITEMS_RECIEVED_STRING = "	TRADED ITEMS RECIEVED :";

struct tradeInfo {
	string timeStamp;
	int tradeType; // 1 - buying, 2 - selling, 3 - exchange
	string offeredItems[6] = {"-","-","-","-","-","-"}; // plain number means plat paid
	string receivedItems[6] = {"-","-","-","-","-","-"}; // plain number means plat received
	int creditsSpent;
};

string tradeIntoCSV (vector<string> rawTrade) {
    tradeInfo trade;
    trade.timeStamp = rawTrade[0].substr(0, 19); // date and time are always 19 char long
    for (int i = 2; i < rawTrade.size(); i++){ // strat from 2, becasue 0 is date and 1 is "	TRADED ITEMS GIVEN :"
        string currentString = rawTrade[i];
        if (currentString.substr(2,8) == "PLATINUM") { // process plat line
            trade.tradeType = 1;
            trade.offeredItems[0] = currentString.substr(currentString.find("-"));
            continue; 
        }
        if (currentString.substr(2,7) == "CREDITS") { // process credit line
            trade.creditsSpent = stoi(currentString.substr(currentString.find("-")));
            continue;
        }
        
    }
    string csvString = trade.timeStamp + ",";
    for (int i = 0; i < 6; i++) {
        csvString += trade.offeredItems[i] + ",";
    }
    for (int i = 0; i < 6; i++) {
        csvString += trade.receivedItems[i] + ",";
    }
    csvString += trade.creditsSpent + "," + to_string(trade.tradeType) + "\n";
    return csvString;
}