package app;

public class Customer {
    private static int nextCustomerId = 0;
    private int customerId;
    private String name;
    private int serviceChoice;

    public Customer(String name, int serviceChoice) {
        this.customerId = ++nextCustomerId;
        this.name = name;
        this.serviceChoice = serviceChoice;
    }

    public int getId() {
        return this.customerId;
    }

    public String getName() {
        return this.name;
    }

    public int getServiceChoice() {
        return this.serviceChoice;
    }

    public void setServiceChoice(int choice) {
        this.serviceChoice = choice;
    }
}