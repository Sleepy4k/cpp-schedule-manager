#include <iostream>
#include <string>

using namespace std;

class Admin {
  private:
    struct ScheduleStruct {
      string uid;
      string date;
      string subject;
      string faculty;
    };
    
    bool is_data_numeric(string data);
    bool validate_date(string date);
    bool validate_string(string text);
    bool validate_uid(string text);
  public:
    void show_menu();
    void show_schedule();
    void add_schedule();
    void find_schedule();
    void edit_schedule();
    void delete_schedule();
};