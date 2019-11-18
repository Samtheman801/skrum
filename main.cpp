#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include "/home/samuel/Programming/CPP/Skrum/pugixml.hpp"
using namespace std;
int menuC1, menuC2, gamechoice; 
string username, password, loginUsername, loginPassword, playerProfile, playerRank, line, gamerank;
char const END[2] = "1";

//added stuff
string selectedGameID;


//func declaration
void curlSteamStats(string selectedGame, string selectedUserID);

//callback function to write data to raw_html
size_t writeFunction(void *contents, size_t size, size_t nmemb, string *raw_html) {
    size_t newLength = size*nmemb;
    try {
        raw_html->append((char*)contents, newLength);
    }
    catch(std::bad_alloc &e) {
        //handle memory problem
        return 0;
    }
    return newLength;
}

int main() {
  cout<<"Welcome to Gamers 4 Gamers!\n\nWhat do you want to do?:\n"; 
  cout<<"\n\t1: Login\n\n\t2: Create an account\n\n\t3: Exit\n\n"; 
  cout<<"> "; 
  cin>>menuC1;  
  switch(menuC1){ 
    case 1:{
      cout<<"\n\tUsername: ";
      cin>>loginUsername;
      string userFile = loginUsername + ".txt";
      ifstream testUser;
      testUser.open(userFile);
      if (!testUser){
        cout<<"\nThat username doesn't exist. If you would like to create an account, please restart the program and choose option 2.";
        return 0;
      }
      else{
        testUser>>username;
        testUser>>password;
        cout<<"\n\tPassword: "; 
        cin>>loginPassword;
        if (loginPassword==password){
          cout<<"Login success!";
          break;
        }
        else if (loginPassword!=password){
          while (loginPassword!=password){
            cout<<"Sorry, that isn't the correct password. Please try again.";
            cin>>loginPassword;
          }
        }
        else{
          cout<<"Error, please try again later.";
          return 0;
        }
      }
    }
    case 2:{
      cout<<"\n\tUsername: ";
      cin>>loginUsername;
      ifstream inputNames;
      inputNames.open("usernames.txt");
      while (username!=END){
        if (loginUsername!=username){
          inputNames>>username;
        }
        else if (loginUsername==username){
          cout<<"\n\nYou cannot choose that name. Please select a new one.\n\n\tUsername: ";
          cin>>loginUsername;
        }
        else{
          cout<<"Error, please try again later.";
          return 0;
        }
      }
      inputNames.close();
      ifstream oldNames;
        oldNames.open("usernames.txt");
        ofstream temp;
        temp.open("temp.txt");
        while (getline(oldNames,line))
        {
            if (line != END)
            {
                temp << line << endl;
            }
        }
        temp<<loginUsername<<endl;
        temp<<END<<endl;
        temp.close();
        oldNames.close();
        remove("usernames.txt");
        rename("temp.txt","usernames.txt");
      cout<<"\n\n\tPassword: ";
      cin>>loginPassword;
      cout<<"\nWelcome, "<<loginUsername<<" to Gamers4Gamers!";
      string userFile = loginUsername + string(".txt");
      ofstream useroutFile;
      useroutFile.open(userFile);
      useroutFile<<loginUsername<<endl;
      useroutFile<<loginPassword<<endl;
      useroutFile.close();
      break;
    }
    case 3:{
      cout<<"See you soon!";
      curlSteamStats("csgo", "Samtheman801");                                                         // yo idiot
      return 0;
    }
    default:{
      cout<<"Error, please try again later.";
      return 0;
    }
  }
  username=loginUsername;
  password=loginPassword;


//LOGGED IN


  cout<<"\n\nWhat would you like to do?\n\t1. View other players\n\t2. Create your own profile\n\n> ";
  cin>>menuC2;
  switch(menuC2){
    
//view profiles
    
    case 1:{
      cout<<"From which game would you like to view player's profiles?\n\t1. CSGO\n\t2. PUBG\n\t3. ROCKET LEAGUE\n\n> ";
      cin>>gamechoice;
      if (gamechoice==1){
        string selectedGame = "csgo";
        ifstream inputCSGO;
        inputCSGO.open("csgo.txt");
        inputCSGO>>playerProfile;
        inputCSGO>>playerRank;
        cout<<"Player\tSkill\n";
        while (playerProfile!=END){
          cout<<playerProfile<<"\t"<<playerRank<<endl;
          inputCSGO>>playerProfile;
          inputCSGO>>playerRank;
        }
        inputCSGO.close();
        return 0;
      }
      else if (gamechoice==2){
        string selectedGame = "pubg";
        ifstream inputPUBG;
        inputPUBG.open("pubg.txt");
        inputPUBG>>playerProfile;
        inputPUBG>>playerRank;
        cout<<"Player\tSkill\n";
        while (playerProfile!=END){
          cout<<playerProfile<<"\t"<<playerRank<<endl;
          inputPUBG>>playerProfile;
          inputPUBG>>playerRank;
        }
        inputPUBG.close();
        return 0;
      }
      else if (gamechoice==3){
        string selectedGame = "rl";
        ifstream inputRL;
        inputRL.open("rl.txt");
        inputRL>>playerProfile;
        inputRL>>playerRank;
        cout<<"Player\tSkill\n";
        while (playerProfile!=END){
          cout<<playerProfile<<"\t"<<playerRank<<endl;
          inputRL>>playerProfile;
          inputRL>>playerRank;
        }
        inputRL.close();
        return 0;
      }
      else{
        cout<<"There was an error opening this file, or the game was not supported. Please try again later.";
        return 0;
      }
    }

//create personal profiles

    case 2:{
      cout<<"For which game would you like to create a profile for?\n\t1. CSGO\n\t2. PUBG\n\t3. ROCKET LEAGUE\n\n> ";
      cin>>gamechoice;
      if (gamechoice==1){
        ofstream outputCSGO;
        outputCSGO.open("csgo.txt");
        cout<<"Please input your current rank (no spaces!): ";
        cin>>gamerank;
        playerProfile = username+"\t"+gamerank;
        ifstream oldCSGO;
        oldCSGO.open("csgo.txt");
        ofstream temp1;
        temp1.open("temp1.txt");
        while (getline(oldCSGO,line))
        {
            if (line != END)
            {
                temp1 << line << endl;
            }
        }
        temp1<<playerProfile<<endl;
        temp1<<END<<endl;
        temp1.close();
        oldCSGO.close();
        remove("csgo.txt");
        rename("temp1.txt","csgo.txt");
        cout<<"You have made your own profile!" << endl;
        return 0;
      }
      else if (gamechoice==2){
        ofstream outputPUBG;
        outputPUBG.open("pubg.txt");
        cout<<"Please input your current rank(no spaces!): ";
        cin>>gamerank;
        playerProfile = username+"\t"+gamerank;
        ifstream oldPUBG;
        oldPUBG.open("pubg.txt");
        ofstream temp1;
        temp1.open("temp1.txt");
        while (getline(oldPUBG,line))
        {
            if (line != END)
            {
                temp1 << line << endl;
            }
        }
        temp1<<playerProfile<<endl;
        temp1<<END<<endl;
        temp1.close();
        oldPUBG.close();
        remove("pubg.txt");
        rename("temp1.txt","pubg.txt");
        cout<<"You have made your own profile!" << endl;
        return 0;
      }
      else if (gamechoice==3){
        ofstream outputRL;
        outputRL.open("rl.txt");
        cout<<"Please input your current rank(no spaces!): ";
        cin>>gamerank;
        playerProfile = username+"\t"+gamerank;
        ifstream oldRL;
        oldRL.open("rl.txt");
        ofstream temp1;
        temp1.open("temp1.txt");
        while (getline(oldRL,line))
        {
            if (line != END)
            {
                temp1 << line << endl;
            }
        }
        temp1<<playerProfile<<endl;
        temp1<<END<<endl;
        temp1.close();
        oldRL.close();
        remove("rl.txt");
        rename("temp1.txt","rl.txt");
        cout<<"You have made your own profile!" << endl;
        return 0;
      }
      else{
        cout<<"There was an error opening this file, or the game was not supported. Please try again later.";
        return 0;
      }
    }
    default:{
      cout<<"Error, please try again later.";
      return 0;
    }
  }
}

void curlSteamStats(string selectedGame, string selectedUserID) {
    /* build url to curl...

    URL Format

    https://steamcommunity.com/id/(STEAM ID)/stats/(GAME ID)/?xml=1

    steam game ids
    csgo = "CSGO";
    pubg = "587080";
    rl = "252950";

    */ 

    if (selectedGame.compare("csgo") == 0) {
        selectedGameID = "CSGO";
    }
    else if (selectedGame.compare("pubg") == 0) {
        selectedGameID = "587080";
    }
    else if (selectedGame.compare("rl") == 0) {
        selectedGameID = "252950";
    }

    string statURLstr = "https://steamcommunity.com/id/" + selectedUserID + "/stats/" + selectedGameID + "/?xml=1";
    const char *statURL = statURLstr.c_str();
    string raw_html;

    //create curl instance
    CURL *curl = curl_easy_init();
    CURLcode res;

    //cURL CONFIGURATION
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);                    //verbose output
    curl_easy_setopt(curl, CURLOPT_URL, statURL);                   //normal dns request
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);   //callback for writing data
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &raw_html);           //write data to string raw_html

    //cURL to site
    res = curl_easy_perform(curl);

    //cout << raw_html << endl;

    ofstream writeXML;
    string file = selectedUserID + selectedGame + ".xml";
    writeXML.open(file);
    writeXML << raw_html << endl;

    pugi::xml_document doc;
    pugi::xml_node tools = doc.child("Profile").child("Tools");
    auto root = doc.append_child("MyRoot");
    pugi::xml_parse_result result = doc.load_file("Samtheman801csgo.xml");
    std::cout << "Load result: " << result.description() << endl;

    for (pugi::xml_node tool = tools.first_child(); tool; tool = tool.next_sibling()) {
        cout << "Tool:";
        for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute()) {
            std::cout << " " << attr.name() << "=" << attr.value();
        }
    std::cout << std::endl;
    }

    //https://pugixml.org/docs/manual.html#access
}