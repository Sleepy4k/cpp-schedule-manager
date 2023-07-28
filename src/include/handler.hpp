#include <string>

using namespace std;

class Handler {
  private:
    struct UserRecord {
      string uid;
      string username;
      string password;
      string role;
    };
  public:
    void main_menu();
    string generate_uuid();
    string handle_login(string role);
    void handle_register();
    bool is_data_numeric(string data);
    bool validate_date(string date);
    bool validate_string(string text);
    bool validate_uid(string text);
};