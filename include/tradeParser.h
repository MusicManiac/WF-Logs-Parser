#include <string>
#include <vector>

using namespace ::std;

const string ITEMS_RECEIVED_STRING = "	TRADED ITEMS RECIEVED :";

struct tradeInfo {
	string timeStamp;
	int tradeType = 3; // 1 - buying, 2 - selling, 3 - exchange
	string offeredItems[6] = {"-","-","-","-","-","-"}; // plain number means plat paid
	string receivedItems[6] = {"-","-","-","-","-","-"}; // plain number means plat received
	string creditsSpent;
};

string tradeIntoCSV (vector<string> rawTrade) {
    tradeInfo trade;
    trade.timeStamp = rawTrade[0].substr(0, 19); // date and time are always 19 char long
    int currentOfferedItemsIndex = 0, currentReceivedItemsIndex = 0;
    bool processingReceivedItems = false;
    for (int i = 2; i < rawTrade.size(); i++){ // start from 2, because 0 is date and 1 is "	TRADED ITEMS GIVEN :"
        string currentString = rawTrade[i];
        if (!processingReceivedItems) {
            if (currentString.substr(2,8) == "PLATINUM") { // process plat line
                trade.tradeType = 1;
                trade.offeredItems[currentOfferedItemsIndex++] = currentString.substr(currentString.find("-"));
                continue; 
            }
            if (currentString.substr(2,7) == "CREDITS") { // process credit line
                trade.creditsSpent = currentString.substr(currentString.find("-"));
                continue;
            }
            if (currentString != ITEMS_RECEIVED_STRING) { // keep processing lines until "	TRADED ITEMS RECIEVED :"is found
                if (currentString.find(":") != string::npos) { // if item has count, add items to array as many times as amount of copies offered, max 6 so length is 1
                    for (int i = 0; i < stoi(currentString.substr(currentString.size() - 1)); i++) {
                        trade.offeredItems[currentOfferedItemsIndex++] = currentString.substr(2, currentString.size() - 2 - 5); // -2 for tabs and -5 for amount of items traded " : -X"
                    }
                } else { // else it's some stuff like "MELEE RIVEN MOD" or "VAYOR HEK"
                    trade.offeredItems[currentOfferedItemsIndex++] = currentString.substr(2); // remove 2 tabs at start
                }
            } else {
                processingReceivedItems = true;
                continue;
            }
        } else {
            if (currentString.substr(2,8) == "PLATINUM") { // process plat line
                trade.tradeType = 2;
                trade.receivedItems[currentReceivedItemsIndex++] = currentString.substr(currentString.find(":") + 2);
                continue; 
            }
            if (currentString.find(":") != string::npos) { // if item has count, add items to array as many times as amount of copies offered, max 6 so length is 1
                for (int i = 0; i < stoi(currentString.substr(currentString.size() - 1)); i++) {
                    trade.receivedItems[currentReceivedItemsIndex++] = currentString.substr(2, currentString.size() - 2 - 4); // -2 for tabs and -4 for amount of items traded " : X"
                }
            } else { // else it's some stuff like "MELEE RIVEN MOD" or "VAYOR HEK"
                trade.receivedItems[currentReceivedItemsIndex++] = currentString.substr(2); // remove 2 tabs at start

            }
            
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