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
    ScheduleStruct schedule;
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

  Admin::show_menu();
}

void Admin::add_schedule() {
  Handler handler;
  string date, subject, faculty;

  cout << "\n\nPlease Enter The Following Details To Create New Schedule" << endl;

  cout << "\nEnter Date (DD/MM/YYYY) : ";
  cin >> date;

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid date!!" << endl;

      Admin::add_schedule();
    } else if (handler.validate_date(date)) {
      break;
    } else {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid date!!" << endl;

      Admin::add_schedule();
    }
  }

  cout << "Enter Subject : ";
  getline(cin >> ws, subject);

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid subject!!" << endl;

      Admin::add_schedule();
    } else if (handler.validate_string(subject)) {
      break;
    } else {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid subject!!" << endl;

      Admin::add_schedule();
    }
  }

  cout << "Enter Faculty : ";
  getline(cin >> ws, faculty);

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid faculty!!" << endl;

      Admin::add_schedule();
    } else if (handler.validate_string(faculty)) {
      break;
    } else {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid faculty!!" << endl;

      Admin::add_schedule();
    }
  }

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
  cin.ignore();
  cin.get();

  Admin::show_menu();
}

void Admin::find_schedule() {
  string id;
  string line;
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

  cout << "\nPlease Enter The Following UID To Find Schedule: ";
  cin >> id;

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid UID!!" << endl;

      Admin::find_schedule();
    } else if (handler.validate_uid(id)) {
      break;
    } else {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid UID!!" << endl;

      Admin::find_schedule();
    }
  }

  while (getline(file, line)) {
    ScheduleStruct schedule;
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

    if (schedule.uid == id) {
      schedule_data.push_back(schedule);
      found = true;
      break;
    }
  }

  file.close();

  for (int i = 0; i < schedule_data.size(); i++) {
    cout << "\nHere's the data for id " << id << endl;
    cout << "\n--------------------------------------------------------";
    cout << "\nUID : " << schedule_data[i].uid;
    cout << "\nDate : " << schedule_data[i].date;
    cout << "\nSubject : " << schedule_data[i].subject;
    cout << "\nFaculty : " << schedule_data[i].faculty;
    cout << "\n--------------------------------------------------------" << endl;
    break;
  }

  if (!found) {
    cout << "\nNo Data Found For UID " << id << endl;
  }

  cout << "\nPress Enter To Continue" << endl;
  cin.ignore();
  cin.get();

  Admin::show_menu();
}

void Admin::edit_schedule() {
  string line;
  Handler handler;
  bool found = false;
  vector<ScheduleStruct> schedule_data;
  vector<ScheduleStruct> n_schedule_data;
  ifstream file("src/data/schedule.csv");
  string id, n_date, n_subject, n_faculty;

  if (!file) {
    fstream outfile("src/data/schedule.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Admin::show_menu();
    }
  }

  cout << "\n\nPlease Enter The Following UID To Edit Schedule: ";
  cin >> id;

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid UID!!" << endl;

      Admin::edit_schedule();
    } else if (handler.validate_uid(id)) {
      break;
    } else {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid UID!!" << endl;

      Admin::edit_schedule();
    }
  }

  while (getline(file, line)) {
    ScheduleStruct schedule;
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

  for (int i = 0; i < schedule_data.size(); i++) {
    if (schedule_data[i].uid == id) {
      cout << "\nEnter Date (DD/MM/YYYY) : ";
      cin >> n_date;

      while (true) {
        if (cin.fail()) {
          cin.clear();
          cin.ignore(512, '\n');
          cout << "\nPlease enter a valid date!!" << endl;

          Admin::edit_schedule();
        } else if (handler.validate_date(n_date)) {
          break;
        } else {
          cin.clear();
          cin.ignore(512, '\n');
          cout << "\nPlease enter a valid date!!" << endl;

          Admin::edit_schedule();
        }
      }

      cout << "Enter Subject : ";
      getline(cin >> ws, n_subject);

      while (true) {
        if (cin.fail()) {
          cin.clear();
          cin.ignore(512, '\n');
          cout << "\nPlease enter a valid subject!!" << endl;

          Admin::edit_schedule();
        } else if (handler.validate_string(n_subject)) {
          break;
        } else {
          cin.clear();
          cin.ignore(512, '\n');
          cout << "\nPlease enter a valid subject!!" << endl;

          Admin::edit_schedule();
        }
      }

      cout << "Enter Faculty : ";
      getline(cin >> ws, n_faculty);

      while (true) {
        if (cin.fail()) {
          cin.clear();
          cin.ignore(512, '\n');
          cout << "\nPlease enter a valid faculty!!" << endl;

          Admin::edit_schedule();
        } else if (handler.validate_string(n_faculty)) {
          break;
        } else {
          cin.clear();
          cin.ignore(512, '\n');
          cout << "\nPlease enter a valid faculty!!" << endl;

          Admin::edit_schedule();
        }
      }

      schedule_data[i].date = n_date;
      schedule_data[i].subject = n_subject;
      schedule_data[i].faculty = n_faculty;

      found = true;
    }
  }

  if (!found) {
    cout << "\nNo Data Found For UID " << id << endl;
  } else {
    ofstream n_file("src/data/schedule.csv");

    if (!n_file) {
      cerr << "Error creating file" << endl;
      Admin::show_menu();
    }

    for (int i = 0; i < schedule_data.size(); i++) {
      n_file << schedule_data[i].uid << "," << schedule_data[i].date << "," << schedule_data[i].subject << "," << schedule_data[i].faculty << endl;
    }

    n_file.close();

    cout << "\nSchedule Updated Successfully" << endl;
  }

  cout << "\nPress Enter To Continue" << endl;
  cin.ignore();
  cin.get();

  Admin::show_menu();
}

void Admin::delete_schedule() {
  string line;
  Handler handler;
  bool found = false;
  vector<ScheduleStruct> schedule_data;
  vector<ScheduleStruct> n_schedule_data;
  ifstream file("src/data/schedule.csv");
  string id;

  if (!file) {
    fstream outfile("src/data/schedule.csv", ios::app);

    if (!outfile) {
      outfile.close();
      cerr << "Error opening file" << endl;
      Admin::show_menu();
    }
  }

  cout << "\n\nPlease Enter The Following UID To Delete Schedule: ";
  cin >> id;

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid UID!!" << endl;

      Admin::delete_schedule();
    } else if (handler.validate_uid(id)) {
      break;
    } else {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a valid UID!!" << endl;

      Admin::delete_schedule();
    }
  }

  while (getline(file, line)) {
    ScheduleStruct schedule;
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

  for (int i = 0; i < schedule_data.size(); i++) {
    if (schedule_data[i].uid != id) {
      n_schedule_data.push_back(schedule_data[i]);
    } else {
      found = true;
    }
  }

  if (!found) {
    cout << "\nNo Data Found For UID " << id << endl;
  } else {
    ofstream n_file("src/data/schedule.csv");

    if (!n_file) {
      cerr << "Error creating file" << endl;
      Admin::show_menu();
    }

    for (int i = 0; i < n_schedule_data.size(); i++) {
      n_file << n_schedule_data[i].uid << "," << n_schedule_data[i].date << "," << n_schedule_data[i].subject << "," << n_schedule_data[i].faculty << endl;
    }

    n_file.close();

    cout << "\nSchedule Deleted Successfully" << endl;
  }

  cout << "\nPress Enter To Continue" << endl;
  cin.ignore();
  cin.get();

  Admin::show_menu();
}

void Admin::show_menu() {
  int choice;

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

  cout << "\nPlease Enter Your Choice : ";
  cin >> choice;

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a number!!" << endl;

      Admin::show_menu();
    } else if (choice >= 1 && choice <= 6) {
      break;
    } else {
      cin.clear();
      cin.ignore(512, '\n');
      cout << "\nPlease enter a number between 1 and 6!!" << endl;

      Admin::show_menu();
    }
  }

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