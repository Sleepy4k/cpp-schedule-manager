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
    int main_menu();
    string generate_uuid();
    void handle_login(string role);
    void handle_register();
};