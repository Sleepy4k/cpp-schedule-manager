#include <iostream>
#include <string>

using namespace std;

class Admin {
  private:
    struct ScheduleStruct {
      string date;
      string subject;
      string faculty;
    }; 
  public:
    void show_menu();
    void show_schedule();
    void add_schedule();
};