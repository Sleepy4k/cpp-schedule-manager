#include <string>

using namespace std;

class Faculty {
  private:
    string userId;
    struct TrainingStruct {
      string uid;
      string userID;
      string scheduleID;
      string date;
    };
  public:
    Faculty(string id);
    
    void show_menu();
    void view_schedule();
    void add_training();
    void view_training();
    void cancel_training();
};