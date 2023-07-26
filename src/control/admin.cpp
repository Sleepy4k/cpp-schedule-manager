#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/admin.hpp"
#include "../include/handler.hpp"

using namespace std;

void Admin::show_schedule() {
  std::vector<ScheduleStruct> schedule_data;

  string line;
  ifstream file("src/data/schedule.csv");

  while (getline(file, line)) {
    ScheduleStruct schedule;
    string date, subject, faculty;

    date = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    subject = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    faculty = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    schedule.date = date;
    schedule.subject = subject;
    schedule.faculty = faculty;

    schedule_data.push_back(schedule);
  }

  file.close();

  cout << "\n\nHere's the list of all schedule (" << schedule_data.size() << " total data)" << endl;

  for (int i = 0; i < schedule_data.size(); i++) {
    cout << "\n--------------------------------------------------------";
    cout << "\nDate : " << schedule_data[i].date;
    cout << "\nSubject : " << schedule_data[i].subject;
    cout << "\nFaculty : " << schedule_data[i].faculty;
    cout << "\n--------------------------------------------------------" << endl;
  }

  cout << "\n\nPress Enter To Continue" << endl;
  cin.ignore(512, '\n');
  cin.get();

  Admin::show_menu();
}

void Admin::add_schedule() {
  string date, subject, faculty;

  cout << "\n\nPlease Enter The Following Details To Create New Schedule" << endl;

  cout << "\nEnter Date (DD/MM/YYYY) : ";
  cin >> date;

  cout << "Enter Subject : ";
  getline(cin >> ws, subject);

  cout << "Enter Faculty : ";
  getline(cin >> ws, faculty);

  ofstream file("src/data/schedule.csv", ios::app);

  if (!file) {
    cerr << "Error opening file" << endl;
    Admin::show_menu();
  }

  file << date << "," << subject << "," << faculty << endl;

  file.close();

  cout << "\nSchedule Created Successfully" << endl;

  cout << "\n\nPress Enter To Continue" << endl;
  cin.ignore(512, '\n');
  cin.get();

  Admin::show_menu();
}

void Admin::show_menu() {
  int choice;

  cout << "\nHere's your admin Dashboard";
  cout << "\nPlease enter your choice to perform particular tasks" << endl;
  cout << "\n--------------------------------------------------------";
  cout << "\nEnter 1 -> To Show ALl Schedule" << endl;
  cout << "Enter 2 -> To Create New Schedule" << endl;
  cout << "Enter 3 -> To Update Existing Schedule" << endl;
  cout << "Enter 4 -> To Quit From This Session" << endl;
  cout << "--------------------------------------------------------" << endl;

  cout << "\nPlease Enter Your Choice : ";
  cin >> choice;

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a number!!" << endl;

      Admin::show_menu();
    } else if (choice >= 1 && choice <= 4) {
      break;
    } else {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a number between 1 and 3!!" << endl;

      Admin::show_menu();
    }
  }

  switch (choice) {
    case 1:
      Admin::show_schedule();
      break;
    case 2:
      Admin::add_schedule();
      break;
    case 4:
      Handler handler;
      handler.main_menu();
      break;
    default:
      break;
  }
}