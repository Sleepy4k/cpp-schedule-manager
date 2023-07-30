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
    size_t pos = 0;
    Admin::ScheduleStruct schedule;

    schedule.uid = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    schedule.date = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    schedule.subject = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    schedule.faculty = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    schedule_data.push_back(schedule);
  }

  file.close();

  cout << "\nHere's the list of all schedule (" << schedule_data.size() << " total data)" << endl;

  for (const Admin::ScheduleStruct& schedule : schedule_data) {
    cout << "\n--------------------------------------------------------";
    cout << "\nUID : " << schedule.uid;
    cout << "\nDate : " << schedule.date;
    cout << "\nSubject : " << schedule.subject;
    cout << "\nFaculty : " << schedule.faculty;
    cout << "\n--------------------------------------------------------" << endl;
  }

  cout << "\nPress Enter To Continue" << endl;
  std::cin.ignore();
  std::cin.get();

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
    size_t pos = 0;
    TrainingStruct training;

    training.uid = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    training.userID = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    training.scheduleID = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    training.date = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    if (training.userID == Faculty::userId) {
      training_data.push_back(training);
    }
  }

  file.close();

  cout << "\nHere's the list of your training (" << training_data.size() << " total data)" << endl;

  for (const TrainingStruct& training : training_data) {
    cout << "\n--------------------------------------------------------";
    cout << "\nUID : " << training.uid;
    cout << "\nUser ID : " << training.userID;
    cout << "\nSchedule ID : " << training.scheduleID;
    cout << "\nDate : " << training.date;
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
  bool found = false;

  scheduleID = handler.input_validation("\nPlease Enter The Following Schedule UID To Add Training: ", "uid", false);

  string line, scheduleDate;
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
    size_t pos = 0;
    Admin::ScheduleStruct schedule;

    schedule.uid = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    schedule.date = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    schedule.subject = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    schedule.faculty = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    if (schedule.uid == scheduleID) {
      scheduleDate = schedule.date;
      found = true;
      break;
    }
  }

  input.close();

  if (!found) {
    cout << "\nSchedule Not Found" << endl;
  } else {
    ofstream file("src/data/training.csv", ios::app);

    if (!file) {
      fstream outfile("src/data/training.csv", ios::app);

      if (!outfile) {
        outfile.close();
        cerr << "Error opening file" << endl;
        Faculty::show_menu();
      }
    }

    string uid = handler.generate_uuid();

    file << uid << "," << Faculty::userId << "," << scheduleID << "," << scheduleDate << endl;

    file.close();

    cout << "\nTraining Created Successfully" << endl;
  }

  cout << "\nPress Enter To Continue" << endl;
  cin.ignore();
  cin.get();

  Faculty::show_menu();
}

void Faculty::cancel_training() {
  string id, line;
  Handler handler;
  bool found = false;
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

  id = handler.input_validation("\nPlease Enter The Following UID To Edit Schedule: ", "uid", false);

  while (getline(file, line)) {
    size_t pos = 0;
    TrainingStruct training;

    training.uid = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    training.userID = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    training.scheduleID = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    training.date = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    training_data.push_back(training);
  }

  vector<TrainingStruct> n_training_data;
  for (const TrainingStruct& training : training_data) {
    if (training.uid != id) {
      n_training_data.push_back(training);
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

    for (const TrainingStruct& training : n_training_data) {
      n_file << training.uid << "," << training.userID << "," << training.scheduleID << "," << training.date << endl;
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
  cout << "\nHere's your faculty Dashboard";
  cout << "\nPlease enter your choice to perform particular tasks" << endl;
  cout << "\n--------------------------------------------------------";
  cout << "\nEnter 1 -> To Show ALL Schedule" << endl;
  cout << "Enter 2 -> To Show Your Training" << endl;
  cout << "Enter 3 -> To Add Your Training" << endl;
  cout << "Enter 4 -> To Cancel Your Training" << endl;
  cout << "Enter 5 -> To Quit From This Session" << endl;
  cout << "--------------------------------------------------------" << endl;

  Handler handler;
  int choice = handler.menu_validation(1, 5);

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