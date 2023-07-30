#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include "../include/admin.hpp"
#include "../include/faculty.hpp"
#include "../include/handler.hpp"

using namespace std;

bool Handler::is_data_numeric(string data) {
  for (int i = 0; i < data.length(); i++) {
    if (!isdigit(data[i])) {
      return false;
    }
  }

  return true;
}

bool Handler::validate_date(string date) {
  string delimiter = "/";

  string day = date.substr(0, date.find(delimiter));
  date.erase(0, date.find(delimiter) + 1);

  string month = date.substr(0, date.find(delimiter));
  date.erase(0, date.find(delimiter) + 1);

  string year = date.substr(0, date.find(delimiter));
  date.erase(0, date.find(delimiter) + 1);

  if (!Handler::is_data_numeric(day) || !Handler::is_data_numeric(month) || !Handler::is_data_numeric(year)) {
    return false;
  }

  if (day.length() != 2 || month.length() != 2 || year.length() != 4) {
    return false;
  }

  if (stoi(day) < 1 || stoi(day) > 31) {
    return false;
  }

  if (stoi(month) < 1 || stoi(month) > 12) {
    return false;
  }

  if (stoi(year) < 1000 || stoi(year) > 9999) {
    return false;
  }

  return true;
}

bool Handler::validate_string(string text) {
  for (int i = 0; i < text.length(); i++) {
    if (!isalpha(text[i]) && !isspace(text[i])) {
      return false;
    }
  }

  return true;
}

bool Handler::validate_uid(string text) {
  for (int i = 0; i < text.length(); i++) {
    if (!isalnum(text[i])) {
      return false;
    }
  }

  return true;
}

string Handler::generate_uuid() {
  srand(time(NULL));
  string uuid = "";
  string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  int randomize = 2 + ( std::rand() % ( 5 - 2 + 1 ) );

  for (int i = 0; i < 6 + randomize; i++) {
    uuid += characters[rand() % characters.length()];
  }

  return uuid;
}

string Handler::input_validation(string prompt, string type, bool is_ws) {
  string input;
  bool invalid = false;

  while (true) {
    cout << prompt;
    
    if (is_ws) {
      getline(cin, input);
    } else {
      cin >> input;
    }

    invalid = type == "date" ? !Handler::validate_date(input) : "string" ? !Handler::validate_string(input) : "uid" ? !Handler::validate_uid(input) : true;

    if (cin.fail() || invalid) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nInvalid input. Please try again." << endl;
    } else {
      cin.ignore(512, '\n');
      break;
    }
  }

  return input;
}

int Handler::menu_validation(int min, int max) {
  int choice;

  while (true) {
    cout << "\nPlease Enter Your Choice : ";
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a number!!" << endl;
    } else if (choice >= min && choice <= max) {
      cin.ignore(512, '\n');
      break;
    } else {
      cin.ignore(512, '\n');
      cout << "\nPlease enter a number between " << min << " and " << max << "!!" << endl;
    }
  }

  return choice;
}

string Handler::handle_login(string access) {
  bool valid = false;
  string id, username, password;
  vector<UserRecord> users_data;

  cout << "\nPlease Enter Your Username & Password For Authentiocation";

  cout << "\nEnter Your Username : ";
  cin >> username;

  cout << "Enter Your Password : ";
  cin >> password;

  ifstream file("src/data/users.csv");

  if (!file) {
    fstream outfile("src/data/users.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Handler::main_menu();
    }
  }

  string line;

  while (getline(file, line)) {
    UserRecord user;
    string uid, username, password, role;

    uid = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    username = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    password = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    role = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    user.uid = uid;
    user.username = username;
    user.password = password;
    user.role = role;

    users_data.push_back(user);
  }

  file.close();

  for (int i = 0; i < users_data.size(); i++) {
    if (users_data[i].username == username && users_data[i].password == password && users_data[i].role == access) {
      id = users_data[i].uid;
      valid = true;
      break;
    }
  }

  if (valid) {
    cout << "\n\nLogin Successful" << endl;

    return id;
  } else {
    cout << "\n\nLogin Failed" << endl;
    cout << "\nPlease Try Again" << endl;

    Handler::main_menu();
  }
}

void Handler::handle_register() {
  string username, password;
  vector<UserRecord> users_data;

  cout << "\nPlease Enter Your Username & Password For Registration";

  cout << "\nEnter Your Username : ";
  cin >> username;

  cout << "Enter Your Password : ";
  cin >> password;

  ifstream file("src/data/users.csv");

  if (!file) {
    fstream outfile("src/data/users.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Handler::main_menu();
    }
  }

  string line;

  while (getline(file, line)) {
    UserRecord user;
    string uid, username, password, role;

    uid = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    username = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    password = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    role = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    user.uid = uid;
    user.username = username;
    user.password = password;
    user.role = role;

    users_data.push_back(user);
  }

  file.close();

  for (int i = 0; i < users_data.size(); i++) {
    if (users_data[i].username == username) {
      cout << "\n\nUsername Already Exists" << endl;
      cout << "\nPlease Try Again" << endl;

      Handler::main_menu();
    }
  }

  ofstream outfile;
  outfile.open("src/data/users.csv", ios::app);

  if (!outfile) {
    cerr << "Error opening file" << endl;
    Handler::main_menu();
  }

  string uid = Handler::generate_uuid();

  outfile << uid << "," << username << "," << password << ",user" << endl;

  outfile.close();

  cout << "\n\nRegistration Successful" << endl;
}

void Handler::main_menu() {
  cout << "\n\n--------------------------------------------------------------------" << endl;
  cout << "               Schedule Management System                  " << endl;
  cout << "--------------------------------------------------------------------" << endl;
  cout << "Welcome To Home Page" << endl;
  cout << "Press 1 --> Admin Dashboard" << endl;
  cout << "Press 2 --> Faculty Dashboard" << endl;
  cout << "Press 3 --> Registration User" << endl;
  cout << "Press 4 --> Exit" << endl;

  int choice = Handler::menu_validation(1, 4);

  switch (choice) {
    case 1: {
      Handler::handle_login("admin");

      Admin admin;
      admin.show_menu();
      break;
    }
    case 2: {
      string id = Handler::handle_login("user");

      Faculty faculty(id);
      faculty.show_menu();
      break;
    }
    case 3: {
      Handler::handle_register();
      
      Handler::main_menu();
      break;
    }
    case 4: {
      cout << "\n\nThank You For Using Schedule Management System" << endl;
      exit(0);
      break;
    }
    default:
      break;
  }
}