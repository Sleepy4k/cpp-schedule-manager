#include <iostream>
#include "./include/admin.hpp"
#include "./include/handler.hpp"

using namespace std;

int main() {
  Handler handler;
  int option = handler.main_menu();

  switch (option) {
    case 1:
      handler.handle_login("admin");

      Admin admin;
      admin.show_menu();
      break;
    case 2:
      handler.handle_login("user");
      break;
    case 3:
      handler.handle_register();
      
      main();
      break;
    case 4:
      cout << "\n\nThank You For Using Schedule Management System" << endl;
      exit(0);
      break;
    default:
      cout << "\n\nPlease Enter Valid Choice" << endl;
      break;
  }
}