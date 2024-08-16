package app;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class InvestmentSystem {
    // Vector of customers and service choice. Can not be limited of customers
    static List<Customer> customers = new ArrayList<Customer>() {{
        add(new Customer("Bob Jones", 1));
        add(new Customer("Sarah Davis", 1));
        add(new Customer("Amy Friendly", 1));
        add(new Customer("Johnny Smith", 1));
        add(new Customer("Carol Spears", 1));
    }};

    // Check if user is allowed to access system
    static int checkUserPermissionAccess() {
    	//initialize variables
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        //if password is equal to entered value
        //then return 1, else return 2
        if (password.equals("123")) {
            return 1;
        } 
        else {
            return 2;
        }
    }

    // Display users and selected options
    static void displayInfo() {
    	//print name and choice of each user
        System.out.println("Client Name | Selected Service (1 = Brokerage, 2 = Retirement)");
        for (Customer client : customers) {
            System.out.println(client.getId() + ". " + client.getName() + " selected option " + client.getServiceChoice());
        }
    }
    
    //Allows user to change choice of customer from one choice to the other
    //and vice versa
    static void changeCustomerChoice() {
    	//initialize variables
        Scanner scanner = new Scanner(System.in);
        int changeChoice, newService;
        final int innerChangeChoice, innerNewService;
        int numCustomers = customers.size();

        // Validating customer choice input
        do {
            System.out.print("Enter number of client that you would like to change: ");
            changeChoice = scanner.nextInt();
            if (changeChoice >= 1 && changeChoice <= numCustomers) {
                break;
            } 
            else {
                System.out.println("Invalid customer choice. Try again.");
            }
        } while (true);

        // Validating service choice input
        do {
            System.out.print("Enter new service choice (1 = Brokerage, 2 = Retirement): ");
            newService = scanner.nextInt();
            if (newService >= 1 && newService <= 2) {
                break;
            } 
            else {
                System.out.println("Invalid service choice. Try Again.");
            }
        } while (true);
        
        //Update choice for chosen client
        innerChangeChoice = changeChoice;
        innerNewService = newService;
        
        customers.stream()
                .filter(customer -> customer.getId() == innerChangeChoice)
                .findFirst()
                .ifPresent(customer -> customer.setServiceChoice(innerNewService));
    }

    public static void main(String[] args) { 
    	//initialize variables
    	Scanner scanner = new Scanner(System.in);
        int accessAuthorized = 0;
        int menuInput;
        System.out.println("SNHU Investments Conversion Project 2 | Treyton Davis");
        System.out.println("Hello! Welcome to our Investment Company");

        // Checks if user is authorized to access system
        do {
            accessAuthorized = checkUserPermissionAccess();
            if (accessAuthorized != 1) {
                System.out.println("Invalid username or password. Please try again");
            }
        } while (accessAuthorized != 1);
        
       
        while (true) {
        	//Display menu options to let users know what they can do
            System.out.println("What would you like to do?");
            System.out.println("DISPLAY the client list (enter 1)");
            System.out.println("CHANGE a client's choice (enter 2)");
            System.out.println("Exit the program (enter 3)");

            // Validates menu choice input
            while(true) {
                menuInput = scanner.nextInt();
                if (menuInput == 1 || menuInput == 2 || menuInput == 3) {
                    break;
                } 
                else {
                    System.out.println("Invalid menu choice. Try again.");
                }
            }
            
            //Switch between which option the user chose
            System.out.println("You chose " + menuInput);
            if (menuInput == 1) {
                displayInfo();
            } 
            else if (menuInput == 2) {
                changeCustomerChoice();
            } 
            else if (menuInput == 3) {
            	System.out.println("Program Terminated");
                break;
            }
        }
        //deactivate scanner when done with program
        scanner.close();
    }
}

