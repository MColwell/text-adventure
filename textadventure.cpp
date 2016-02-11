#include<iostream>
#include<string>
#include<time.h>
#include<cstdlib>
#include<vector>
#include<readline/readline.h>
#include<readline/history.h>

class item {
  std::string item_name;
  int quantity;
  public:
    void set_item_name (std::string name) {
      item_name = name;
    }
    std::string getitemname() {
      return item_name;
    }
    void set_quantity (int count) {
      quantity = count;
    }
    int getquantity() {
      return quantity;
    }
};

class location {
  std::string location_name;
  std::vector<item> location_inventory;
  std::string description;
  public:
    void set_location_name(std::string loc_name) {
      location_name = loc_name;
    }
    std::string get_location_name() {
      return location_name;
    }
    void add_item(item item_to_add) {
      location_inventory.push_back(item_to_add);
    }
    std::vector<item> get_location_inventory() {
      return location_inventory;
    }
    void set_description(std::string desc) {
      description = desc;
    }
    std::string get_description(std::string desc) {
      return description;
    }
};

struct world {
  std::vector<location*> location_list;
};

class player {
  std::string player_name;
  int charisma;
  int wisdom;
  int intelligence;
  int spot;
  int will;
  int constitution;
  int agility;
  int level;
  int experience;
  std::vector<item> inventory;
  location* player_location;
  public:
  void newplayer () {
    srand ( time(NULL) );
    charisma = rand() % 10;
    wisdom = rand() % 10;
    intelligence = rand() % 10;
    spot = rand() % 10;
    will = rand() % 10;
    constitution = rand() % 10;
    agility = rand() % 10;
    level = 1;
    experience = 0;
    player_name = "Fred";
  }
  std::string set_name (std::string pname) {
    player_name = pname;
    return player_name;
  }
  std::string get_name () {
    return player_name;
  }
  void setcharisma (int charism) {
    experience = experience + (charism - charisma);
    charisma = charism;
  }
  int getcharisma () {
    return charisma;
  }
  void setwisdom (int wis) {
    wisdom = wis;
  }
  int getwisdom () {
    return wisdom;
  }
  void setintelligence (int intel) {
    intelligence = intel;
  }
  void setspot (int spo) {
    spot = spo;
  }
  void setwill (int wil) {
    will = wil;
  }
  void setconstitution (int con) {
    constitution = con;
  }
  void setagility (int ag) {
    agility = ag;
  }
  void setlevel (int newlevel) {
    level = newlevel;
    experience = experience % 1000;
  }
  int getlevel () {
    return level;
  }
  void setexperience (int exp) {
    experience = exp;
  }
  int getexperience () {
    return experience;
  }
  void printinventory() {
    for (unsigned int count = 0; count < inventory.size(); count++) {
      std::cout << inventory[count].getitemname() << " ";
    }
    std::cout << std::endl;
  }
  void printstats() {
    std::cout << "Name: " << player_name << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "Experience: " << experience << std::endl;
    std::cout << "Spot: " << spot << std::endl;
    std::cout << "Will: " << will << std::endl;
    std::cout << "Constitution: " << constitution << std::endl;
    std::cout << "Agility: " << agility << std::endl;
    std::cout << "Charisma: " << charisma << std::endl;
    std::cout << "Wisdom: " << wisdom << std::endl;
    std::cout << "Intelligence: " << intelligence << std::endl;
    std::cout << "Inventory: ";
    printinventory();
  }
  void set_location(location* location_ptr) {
    player_location = location_ptr;
  }
  location* get_location() {
    return player_location;
  }
};

bool parsecommand(std::string command, player fred) {
  std::string first_command = command;
  std::string the_rest = "";
  if (command.find(" ") != std::string::npos) {
    int end = command.find(" ");
    first_command = command.substr(0,end);
    end++;
    the_rest = command.substr(end,command.length());
  }
  if (command.length() <= 5) {
    if (command == "exit" || command == "quit") {
      std::cout << "Not saving..." << std::endl;
      std::cout << "Exiting..." << std::endl;
      return false;
    }
    if (command == "inv" || command == "stuff") {
      fred.printinventory();
      return true;
    }
  }
  if (command == "inventory") {
    fred.printinventory();
    return true;
  }
  if (command == "status" || command == "statistics" || command == "look myself" || command == "look self") {
    fred.printstats();
    return true;
  }
  if (first_command == "look" || first_command == "inspect" || first_command == "examine") {
    if (the_rest == "here" || the_rest == "around" || the_rest == "") {
      std::cout << (fred.get_location())->get_description() << std::endl;
      return true;
    }
  }
  bool commandstatus = false;
  //call location specific command parser here?
  if (commandstatus == false) {
    std::cout << "Not a valid command." << std::endl;
  }
  return true;
}

void setup(player fred) {
  fred.newplayer();
  item coaster;
  coaster.set_item_name("Coaster");
  coaster.set_quantity(1);
  location* tavern = new location;
  tavern->set_location_name("Ye Olde Tavern");
  tavern->add_item(coaster);
  fred.set_location(tavern);
  tavern->description = "The tavern is nearly empty. There is a coaster on the bar.";
}

int main () {
  std::cout << "You are in a tavern." << std::endl;
  std::cout << "Type what you will." << std::endl;
  player fred;
  setup(fred);
  //world earth;
  //earth.location_list.push_back(tavern);
  std::string command = "nothing";
  bool keepgoing = true;
  while (keepgoing) {
    std::cout << "> ";
    std::getline(std::cin, command);
    keepgoing = parsecommand(command, fred);
  }
  return 0;
}
