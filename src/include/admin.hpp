#include <iostream>
#include <string>

using namespace std;

class Admin {
  public:
    struct ScheduleStruct {
      string uid;
      string date;
      string subject;
      string faculty;
    };

    void show_menu();
    void show_schedule();
    void add_schedule();
    void find_schedule();
    void edit_schedule();
    void delete_schedule();
};