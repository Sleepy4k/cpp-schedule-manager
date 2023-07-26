#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/handler.hpp"

using namespace std;

int Handler::main_menu() {
  int choice;

  cout << "\n\n--------------------------------------------------------------------" << endl;
  cout << "               Schedule Management System                  " << endl;
  cout << "--------------------------------------------------------------------" << endl;
  cout << "Welcome To Home Page" << endl;
  cout << "Press 1 --> Admin Dashboard" << endl;
  cout << "Press 2 --> Faculty Dashboard" << endl;
  cout << "Press 3 --> Exit" << endl;

  cout << "\nPlease Enter Your Choice : ";
  cin >> choice;

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a number!!" << endl;

      Handler::main_menu();
    } else if (choice >= 1 && choice <= 3) {
      break;
    } else {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a number between 1 and 3!!" << endl;

      Handler::main_menu();
    }
  }

  return choice;
}

void Handler::handle_login(string access) {
  bool valid = false;
  string username, password;
  std::vector<UserRecord> users_data;

  cout << "\nPlease Enter Your Username & Password For Authentiocation";

  cout << "\nEnter Your Username : ";
  cin >> username;

  cout << "Enter Your Password : ";
  cin >> password;

  ifstream file("src/data/users.csv");

  if (!file) {
    cerr << "Error opening file" << endl;
    Handler::main_menu();
  }

  string line;

  while (getline(file, line)) {
    UserRecord user;
    string username, password, role;

    username = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    password = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    role = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    user.username = username;
    user.password = password;
    user.role = role;

    users_data.push_back(user);
  }

  file.close();

  for (int i = 0; i < users_data.size(); i++) {
    if (users_data[i].username == username && users_data[i].password == password && users_data[i].role == access) {
      valid = true;
      break;
    }
  }

  if (valid) {
    cout << "\n\nLogin Successful" << endl;
  } else {
    cout << "\n\nLogin Failed" << endl;
    cout << "\nPlease Try Again" << endl;

    Handler::main_menu();
  }
}