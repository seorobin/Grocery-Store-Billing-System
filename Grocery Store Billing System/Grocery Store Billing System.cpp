#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include<string>

using namespace std;

// Structure to store item details
struct Item {
    string name;
    double price;
    int quantity;
};

// Function to display the bill
void displayBill(const vector<Item>& items, double total, double discount, const string& paymentMethod) {
    cout << "\n========== BILL ==========\n";
    cout << left << setw(20) << "Item"
        << setw(10) << "Qty"
        << setw(10) << "Price"
        << setw(10) << "Total" << endl;
    cout << string(50, '-') << endl;

    for (const auto& item : items) {
        cout << left << setw(20) << item.name
            << setw(10) << item.quantity
            << setw(10) << item.price
            << setw(10) << item.price * item.quantity << endl;
    }
    cout << string(50, '-') << endl;
    cout << "Subtotal: $" << total << endl;
    cout << "Discount: $" << discount << endl;
    cout << "Final Total: $" << total - discount << endl;
    cout << "Payment Method: " << paymentMethod << endl;
    cout << "==========================\n";
}

// Function to save the bill to a CSV file
void saveToCSV(const vector<Item>& items, double total, double discount, const string& paymentMethod) {
    ofstream file("GroceryBill.csv", ios::app); // Append mode
    if (file.is_open()) {
        file << "Item,Quantity,Price,Total\n";
        for (const auto& item : items) {
            file << item.name << "," << item.quantity << "," << item.price << "," << item.price * item.quantity << "\n";
        }
        file << ",,,Subtotal," << total << "\n";
        file << ",,,Discount," << discount << "\n";
        file << ",,,Final Total," << total - discount << "\n";
        file << ",,,Payment Method," << paymentMethod << "\n\n";
        file.close();
    }
    else {
        cerr << "Error: Unable to save to file.\n";
    }
}

int main() {
    vector<Item> items;
    double total = 0.0, discount = 0.0;
    string paymentMethod;
    char choice;

    cout << "Welcome to the Grocery Store Billing System\n";

    // Input items
    do {
        Item item;
        cout << "\nEnter item name: ";
        cin >> ws; // Clear input buffer
        getline(cin, item.name);
        cout << "Enter item price: ";
        cin >> item.price;
        cout << "Enter item quantity: ";
        cin >> item.quantity;

        items.push_back(item);
        total += item.price * item.quantity;

        cout << "Do you want to add another item? (y/n): ";
        cin >> choice;

    } while (tolower(choice) == 'y');

    // Apply discount
    string promoCode;
    cout << "\nEnter promotional code (or press Enter to skip): ";
    cin >> ws; // Clear input buffer
    getline(cin, promoCode);

    if (promoCode == "SAVE10") {
        discount = total * 0.10; // 10% discount
        cout << "Promo code applied! You saved 10%.\n";
    }
    else if (!promoCode.empty()) {
        cout << "Invalid promo code. No discount applied.\n";
    }

    // Select payment method
    cout << "\nSelect payment method:\n";
    cout << "1. Cash\n";
    cout << "2. Card\n";
    cout << "3. UPI\n";
    int paymentChoice;
    cin >> paymentChoice;

    switch (paymentChoice) {
    case 1: paymentMethod = "Cash"; break;
    case 2: paymentMethod = "Card"; break;
    case 3: paymentMethod = "UPI"; break;
    default: paymentMethod = "Unknown"; break;
    }

    // Display the bill
    displayBill(items, total, discount, paymentMethod);

    // Save the bill to a CSV file
    saveToCSV(items, total, discount, paymentMethod);

    cout << "\nThank you for shopping with us!\n";

    return 0;
}
