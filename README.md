# WF-Logs-Parser
This parser uses data provided by DE to show you some neat stats about your trades.

![preview](https://i.imgur.com/MWdf5JC.png)
![preview2](https://i.imgur.com/aThRDVd.png)

Following data is available for each trade you made:
- Date and time
- Items offered
- Items recieved
- Credits spent
- Type of trade
  - Sale: you got platinum from trade
  - Purchase: you spent platinum on trade
  - Exchange: no platinum was involved

Which makes it possible to get all kind of interesting (at least, for me) data and graphs. Pictures attached higher up.

# How to use parser
1. Get your data from DE
    - Go to [zendesk](https://digitalextremes.zendesk.com/hc/en-us)
    - Submit new request in category "My Account"
    - Select subcategory "CCPA or GDPR - General Data Protection Regulation"
    - Write something in Subject and Description fields
    - Wait 1+ days
2. After you get your .txt files, place them in same directory where .exe is
3. Run the .exe (get it in [Releases](https://github.com/MusicManiac/WF-Logs-Parser/releases))
4. Paste name of the file you got, it looks something like "1234567_Nickname101_GDPR_Trades_Warframe.txt"
    - You are free to rename file you got to something like "a.txt" to make process easier, I guess?
5. Program will parse through the file you provided, and generate [.csv file](https://en.wikipedia.org/wiki/Comma-separated_values)

# What to do with received ParsedTrades.csv file
You can do whatever you want with it, but I've included a nice spreadsheet that you can use to get results like on picture provided at the start.
How to get it working:
1. Import provided TradeStats.xlsx (get it in [Releases](https://github.com/MusicManiac/WF-Logs-Parser/releases)) file into selected spreadsheet app (I personally use and prefer [Google Sheets](https://www.google.com/sheets/about/))
2. Import your ParsedTrades.csv file into your freshly created worksheet (make sure the sheet name stays the same as filename, "ParsedTrades")
3. To refresh everything, do following "Find and Repalce" (yes, it does nothing, but it refreshes all formulas to account for your freshly imported "ParsedTrades" Sheet). It also might take extra few seconds depending on how many trades you have there.

![FindAndReplace](https://i.imgur.com/2w9qfM9.png)

4. You are free to tinker with any and all data you have available

# Legal stuff
Code is written under [GNU GPL V3](LICENSE.md)

# ToDo
- GUI, maybe? No real need for it but probably will look pretty.

# Bugs and stuff
I have 3k of my own trades of various different items, and it kinda looks like I was able to catch all cases, but in case I missed something, feel free to open a ticket. I will need part of your trade file attached to find a problem though. If you do attach it, make sure to remove all information *before* trades part (Ctrl+F for "TRADED ITEMS GIVEN :" and delete everything that's before 1st trade)
