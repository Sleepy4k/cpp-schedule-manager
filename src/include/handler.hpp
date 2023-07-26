using namespace std;

class Handler {
  private:
    struct UserRecord {
      string username;
      string password;
      string role;
    };
  public:
    int main_menu();
    void handle_login(string role);
};