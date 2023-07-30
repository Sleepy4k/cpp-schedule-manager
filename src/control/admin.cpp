#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/admin.hpp"
#include "../include/handler.hpp"

using namespace std;

void Admin::show_schedule() {
  string line;
  vector<ScheduleStruct> schedule_data;
  ifstream file("src/data/schedule.csv");

  if (!file) {
    fstream outfile("src/data/schedule.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Admin::show_menu();
    }
  }

  while (getline(file, line)) {
    size_t pos = 0;
    ScheduleStruct schedule;

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

  for (const ScheduleStruct& schedule : schedule_data) {
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

  Admin::show_menu();
}

void Admin::add_schedule() {
  Handler handler;
  string date, subject, faculty;

  cout << "\n\nPlease Enter The Following Details To Create New Schedule" << endl;

  date = handler.input_validation("Enter Date (DD/MM/YYYY) : ", "date", false);
  subject = handler.input_validation("Enter Subject : ", "string", true);
  faculty = handler.input_validation("Enter Faculty : ", "string", true);

  ofstream file("src/data/schedule.csv", ios::app);

  if (!file) {
    fstream outfile("src/data/schedule.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Admin::show_menu();
    }
  }

  string uid = handler.generate_uuid();

  file << uid << "," << date << "," << subject << "," << faculty << endl;

  file.close();

  cout << "\nSchedule Created Successfully" << endl;

  cout << "\nPress Enter To Continue" << endl;
  std::cin.ignore();
  std::cin.get();

  Admin::show_menu();
}

void Admin::find_schedule() {
  string id, line;
  Handler handler;
  bool found = false;
  ifstream file("src/data/schedule.csv");

  if (!file) {
    fstream outfile("src/data/schedule.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Admin::show_menu();
    }
  }

  id = handler.input_validation("\nPlease Enter The Following UID To Find Schedule: ", "uid", false);

  cout << "\nSearching For UID " << id << "..." << endl;

  while (getline(file, line)) {
    size_t pos = 0;
    ScheduleStruct schedule;

    schedule.uid = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    schedule.date = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    schedule.subject = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    schedule.faculty = line.substr(0, (pos = line.find(',')));
    line.erase(0, pos + 1);

    if (schedule.uid == id) {
      cout << "\nHere's the data for id " << id << endl;
      cout << "\n--------------------------------------------------------";
      cout << "\nUID : " << schedule.uid;
      cout << "\nDate : " << schedule.date;
      cout << "\nSubject : " << schedule.subject;
      cout << "\nFaculty : " << schedule.faculty;
      cout << "\n--------------------------------------------------------" << endl;
      found = true;
      break;
    }
  }

  file.close();

  if (!found) {
    cout << "\nNo Data Found For UID " << id << endl;
  }

  cout << "\nPress Enter To Continue" << endl;
  std::cin.ignore();
  std::cin.get();

  Admin::show_menu();
}

void Admin::edit_schedule() {
  Handler handler;
  bool found = false;
  vector<ScheduleStruct> schedule_data;
  ifstream file("src/data/schedule.csv");
  string id, line, n_date, n_subject, n_faculty;

  if (!file) {
    fstream outfile("src/data/schedule.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Admin::show_menu();
    }
  }

  id = handler.input_validation("\nPlease Enter The Following UID To Edit Schedule: ", "uid", false);

  while (getline(file, line)) {
    size_t pos = 0;
    ScheduleStruct schedule;

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

  for (int i = 0; i < schedule_data.size(); i++) {
    if (schedule_data[i].uid == id) {
      n_date = handler.input_validation("\nEnter Date (DD/MM/YYYY) : ", "date", false);
      n_subject = handler.input_validation("Enter Subject : ", "string", true);
      n_faculty = handler.input_validation("Enter Faculty : ", "string", true);

      schedule_data[i].date = n_date;
      schedule_data[i].subject = n_subject;
      schedule_data[i].faculty = n_faculty;

      found = true;
      break;
    }
  }

  file.close();

  if (!found) {
    cout << "\nNo Data Found For UID " << id << endl;
  } else {
    ofstream n_file("src/data/schedule.csv");

    if (!n_file) {
      cerr << "Error creating file" << endl;
      Admin::show_menu();
    }

    for (const ScheduleStruct& schedule : schedule_data) {
      n_file << schedule.uid << "," << schedule.date << "," << schedule.subject << "," << schedule.faculty << endl;
    }

    n_file.close();

    cout << "\nSchedule Updated Successfully" << endl;
  }

  cout << "\nPress Enter To Continue" << endl;
  std::cin.ignore();
  std::cin.get();

  Admin::show_menu();
}

void Admin::delete_schedule() {
  string id, line;
  Handler handler;
  bool found = false;
  vector<ScheduleStruct> schedule_data;
  ifstream file("src/data/schedule.csv");

  if (!file) {
    fstream outfile("src/data/schedule.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Admin::show_menu();
    }
  }

  id = handler.input_validation("\nPlease Enter The Following UID To Delete Schedule: ", "uid", false);

  while (getline(file, line)) {
    size_t pos = 0;
    ScheduleStruct schedule;

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

  vector<ScheduleStruct> n_schedule_data;
  for (const ScheduleStruct& schedule : schedule_data) {
    if (schedule.uid != id) {
      n_schedule_data.push_back(schedule);
    } else {
      found = true;
    }
  }

  file.close();

  if (!found) {
    cout << "\nNo Data Found For UID " << id << endl;
  } else {
    ofstream n_file("src/data/schedule.csv");

    if (!n_file) {
      cerr << "Error creating file" << endl;
      Admin::show_menu();
    }

    for (const ScheduleStruct& schedule : n_schedule_data) {
      n_file << schedule.uid << "," << schedule.date << "," << schedule.subject << "," << schedule.faculty << endl;
    }

    n_file.close();

    cout << "\nSchedule Deleted Successfully" << endl;
  }

  cout << "\nPress Enter To Continue" << endl;
  std::cin.ignore();
  std::cin.get();

  Admin::show_menu();
}

void Admin::show_menu() {
  cout << "\nHere's your admin Dashboard";
  cout << "\nPlease enter your choice to perform particular tasks" << endl;
  cout << "\n--------------------------------------------------------";
  cout << "\nEnter 1 -> To Show ALL Schedule" << endl;
  cout << "Enter 2 -> To Create New Schedule" << endl;
  cout << "Enter 3 -> To Show spesific Schedule" << endl;
  cout << "Enter 4 -> To Update Existing Schedule" << endl;
  cout << "Enter 5 -> To Delete Existing Schedule" << endl;
  cout << "Enter 6 -> To Quit From This Session" << endl;
  cout << "--------------------------------------------------------" << endl;

  Handler handler;
  int choice = handler.menu_validation(1, 6);

  switch (choice) {
    case 1: {
      Admin::show_schedule();
      break;
    }
    case 2: {
      Admin::add_schedule();
      break;
    }
    case 3: {
      Admin::find_schedule();
      break;
    }
    case 4: {
      Admin::edit_schedule();
      break;
    }
    case 5: {
      Admin::delete_schedule();
      break;
    }
    case 6: {
      Handler handler;
      handler.main_menu();
      break;
    }
    default:
      break;
  }
}