#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/admin.hpp"
#include "../include/faculty.hpp"
#include "../include/handler.hpp"

using namespace std;

Faculty::Faculty(string id) {
  Faculty::userId = id;
}

void Faculty::view_schedule() {
  string line;
  vector<Admin::ScheduleStruct> schedule_data;
  ifstream file("src/data/schedule.csv");

  if (!file) {
    fstream outfile("src/data/schedule.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Faculty::show_menu();
    }
  }

  while (getline(file, line)) {
    Admin::ScheduleStruct schedule;
    string uid, date, subject, faculty;

    uid = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    date = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    subject = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    faculty = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    schedule.uid = uid;
    schedule.date = date;
    schedule.subject = subject;
    schedule.faculty = faculty;

    schedule_data.push_back(schedule);
  }

  file.close();

  cout << "\nHere's the list of all schedule (" << schedule_data.size() << " total data)" << endl;

  for (int i = 0; i < schedule_data.size(); i++) {
    cout << "\n--------------------------------------------------------";
    cout << "\nUID : " << schedule_data[i].uid;
    cout << "\nDate : " << schedule_data[i].date;
    cout << "\nSubject : " << schedule_data[i].subject;
    cout << "\nFaculty : " << schedule_data[i].faculty;
    cout << "\n--------------------------------------------------------" << endl;
  }

  cout << "\nPress Enter To Continue" << endl;
  cin.ignore();
  cin.get();

  Faculty::show_menu();
};

void Faculty::view_training() {
  string line;
  Handler handler;
  vector<TrainingStruct> training_data;
  ifstream file("src/data/training.csv");

  if (!file) {
    fstream outfile("src/data/training.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Faculty::show_menu();
    }
  }

  while (getline(file, line)) {
    TrainingStruct training;
    string uid, userID, scheduleID, date;

    uid = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    userID = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    scheduleID = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    date = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    training.uid = uid;
    training.userID = userID;
    training.scheduleID = scheduleID;
    training.date = date;

    if (training.userID == Faculty::userId) {
      training_data.push_back(training);
    }
  }

  file.close();

  cout << "\nHere's the list of your training (" << training_data.size() << " total data)" << endl;

  for (int i = 0; i < training_data.size(); i++) {
    cout << "\n--------------------------------------------------------";
    cout << "\nUID : " << training_data[i].uid;
    cout << "\nUser ID : " << training_data[i].userID;
    cout << "\nSchedule ID : " << training_data[i].scheduleID;
    cout << "\nDate : " << training_data[i].date;
    cout << "\n--------------------------------------------------------" << endl;
  }

  cout << "\nPress Enter To Continue" << endl;
  cin.ignore();
  cin.get();

  Faculty::show_menu();
}

void Faculty::add_training() {
  Handler handler;
  string scheduleID;

  cout << "\n\nPlease Enter The Following Details To Create New Training" << endl;

  cout << "Enter Schedule UID : ";
  cin >> scheduleID;

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid schedule UID!!" << endl;

      Faculty::add_training();
    } else if (handler.validate_uid(scheduleID)) {
      break;
    } else {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid schedule UID!!" << endl;

      Faculty::add_training();
    }
  }

  ofstream file("src/data/training.csv", ios::app);

  if (!file) {
    fstream outfile("src/data/training.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Faculty::show_menu();
    }
  }

  string line;
  string scheduleDate;
  ifstream input("src/data/schedule.csv");

  if (!input) {
    fstream outinput("src/data/schedule.csv", ios::app);

    if (!outinput) {
      outinput.close();
      cerr << "Error opening file" << endl;
      Faculty::show_menu();
    }
  }

  while (getline(input, line)) {
    Admin::ScheduleStruct schedule;
    string uid, date, subject, faculty;

    uid = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    date = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    subject = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    faculty = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    schedule.uid = uid;
    schedule.date = date;
    schedule.subject = subject;
    schedule.faculty = faculty;

    if (schedule.uid == scheduleID) {
      scheduleDate = schedule.date;
      break;
    }
  }

  input.close();

  string uid = handler.generate_uuid();

  file << uid << "," << Faculty::userId << "," << scheduleID << "," << scheduleDate << endl;

  file.close();

  cout << "\nTraining Created Successfully" << endl;

  cout << "\nPress Enter To Continue" << endl;
  cin.ignore();
  cin.get();

  Faculty::show_menu();
}

void Faculty::cancel_training() {
  string line;
  Handler handler;
  bool found = false;
  vector<TrainingStruct> training_data;
  vector<TrainingStruct> n_training_data;
  ifstream file("src/data/training.csv");
  string id;

  if (!file) {
    fstream outfile("src/data/training.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Faculty::show_menu();
    }
  }

  cout << "\n\nPlease Enter The Following UID To Delete Training: ";
  cin >> id;

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid UID!!" << endl;

      Faculty::cancel_training();
    } else if (handler.validate_uid(id)) {
      break;
    } else {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid UID!!" << endl;

      Faculty::cancel_training();
    }
  }

  while (getline(file, line)) {
    TrainingStruct training;
    string uid, userID, scheduleID, date;

    uid = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    userID = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    scheduleID = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    date = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);

    training.uid = uid;
    training.userID = userID;
    training.scheduleID = scheduleID;
    training.date = date;

    training_data.push_back(training);
  }

  for (int i = 0; i < training_data.size(); i++) {
    if (training_data[i].uid != id) {
      n_training_data.push_back(training_data[i]);
    } else {
      found = true;
    }
  }

  if (!found) {
    cout << "\nNo Data Found For UID " << id << endl;
  } else {
    ofstream n_file("src/data/training.csv");

    if (!n_file) {
      cerr << "Error creating file" << endl;
      Faculty::show_menu();
    }

    for (int i = 0; i < n_training_data.size(); i++) {
      n_file << n_training_data[i].uid << "," << n_training_data[i].userID << "," << n_training_data[i].scheduleID << "," << n_training_data[i].date << endl;
    }

    n_file.close();

    cout << "\nTraining Deleted Successfully" << endl;
  }

  cout << "\nPress Enter To Continue" << endl;
  cin.ignore();
  cin.get();

  Faculty::show_menu();
}

void Faculty::show_menu() {
  int choice;

  cout << "\nHere's your faculty Dashboard";
  cout << "\nPlease enter your choice to perform particular tasks" << endl;
  cout << "\n--------------------------------------------------------";
  cout << "\nEnter 1 -> To Show ALL Schedule" << endl;
  cout << "Enter 2 -> To Show Your Training" << endl;
  cout << "Enter 3 -> To Add Your Training" << endl;
  cout << "Enter 4 -> To Cancel Your Training" << endl;
  cout << "Enter 5 -> To Quit From This Session" << endl;
  cout << "--------------------------------------------------------" << endl;

  cout << "\nPlease Enter Your Choice : ";
  cin >> choice;

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a number!!" << endl;

      Faculty::show_menu();
    } else if (choice >= 1 && choice <= 5) {
      break;
    } else {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a number between 1 and 6!!" << endl;

      Faculty::show_menu();
    }
  }

  switch (choice) {
    case 1: {
      Faculty::view_schedule();
      break;
    }
    case 2: {
      Faculty::view_training();
      break;
    }
    case 3: {
      Faculty::add_training();
      break;
    }
    case 4: {
      Faculty::cancel_training();
      break;
    }
    case 5: {
      Handler handler;
      handler.main_menu();
      break;
    }
    default:
      break;
  }
}