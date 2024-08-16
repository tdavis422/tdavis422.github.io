//Project 2 - Fixing Security Vulnerablilities
//Treyton Davis
//CS-410

#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
using namespace std;

class Customer {
  private:
    static unsigned int nextCustomerId;
    unsigned int customerId;
    string name;
    int serviceChoice;
  public:
    Customer(string name, int serviceChoice) {
      this->customerId = ++nextCustomerId;
      this->name = name;
      this->serviceChoice = serviceChoice;
    }
    unsigned int getId() const { return this->customerId;}
    string getName() { return this->name; }
    int getServiceChoice() const { return this->serviceChoice; }
    void setServiceChoice(int choice) {this->serviceChoice = choice;}
};
unsigned int Customer::nextCustomerId = 0;

//Vector of customers and service choice.
//Can not be limited of customers
vector<Customer> customers = {
  Customer("Bob Jones", 1),
  Customer("Sarah Davis", 1),
  Customer("Amy Friendly", 1),
  Customer("Johnny Smith", 1),
  Customer("Carol Spears", 1)
};

//Check is user is allowed to access system
int CheckUserPermissionAccess() {
  string password, username;

  cout << "Enter username: ";
  cin >> username;

  cout << endl << "Enter password: ";
  cin >> password;
  cout << endl;

  if(password == "123"){
    return 1;
  }
  else{
    return 2;
  }
}

//Display users and selected options
void DisplayInfo(){
  cout << "Client Name | Selected Service (1 = Brokerage, 2 = Retirement)" << endl;
  for (Customer & client : customers) {
    cout << client.getId() << ". "
         << client.getName() << " selected option "
         << client.getServiceChoice() << endl;
  }
}

void ChangeCustomerChoice() {
  int changeChoice, newService;
  unsigned int numCustomers = customers.size();

  //Validating customer choice input
  do {
    cout << "Enter number of client that you would like to change" << endl;
    cin >> changeChoice;

    if (cin.good() && changeChoice >= 1 && changeChoice <= numCustomers){
      break;
    }
    else {
      cout << "Invalid customer choice. Try again." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  } while(true);

  //Validating service choice input
  do {
    cout << "Enter new service choice (1 = Brokerage, 2 = Retirement)" << endl;
    cin >> newService;

    if (cin.good() && newService >= 1 && newService <= 2){
      break;
    }
    else {
      cout << "Invalid service choice. Try Again." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }while (true);

  find_if(customers.begin(),
          customers.end(),
          [&changeChoice](const Customer& customer) {return customer.getId() == changeChoice; })
          ->setServiceChoice(newService);
}

int main(){
  int accessAuthorized = 0, menuInput = 0;

  cout << "SNHU Investments Conversion Project 2 | Treyton Davis" << endl;

  cout << "Hello! Welcome to our Investment Company" << endl;

  //Checks if user is authorized to access system
  do{
    //Check username with password
    accessAuthorized = CheckUserPermissionAccess();

    if(accessAuthorized != 1){
      cout << "Invalid username or password. Please try again" << endl;
    }
  } while(accessAuthorized != 1);

  while (true) {
    cout << "What would you like to do?" << endl;
    cout << "DISPLAY the client list (enter 1)" << endl;
    cout << "CHANGE a client's choice (enter 2)" << endl;
    cout << "Exit the program (enter 3)" << endl;
    
    //Validates menu choice input
    do{
      cin >> menuInput;

      if(cin.good() && menuInput >= 1 && menuInput <= 3){
        break;
      }

      else {
        cout << "Invalid menu choice. Try again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
    }while (true);

    cout << "You chose " << menuInput << endl;

    if(menuInput == 1){
      DisplayInfo();
    }
    else if(menuInput == 2){
      ChangeCustomerChoice();
    }
    else if(menuInput == 3){
      break;
    }
  }

  return 0;
}