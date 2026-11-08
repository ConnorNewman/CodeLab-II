#include <iostream>
#include <string>
using namespace std;

// Prompt to ask for distance and only accepts valid numbers
double getDistance() {
    double distance;
    cout << "Enter in numbers how many miles you drove: ";
    cin >> distance;

    // Keeps asking if the user types letters or a number that is 0 or less
    while (cin.fail() || distance <= 0) {
        cin.clear();                 
        cin.ignore(1000, '\n');     
        cout << "Please enter a number bigger than 0: ";
        cin >> distance;
    }
    return distance;
}

// Prompt that asks for fuel type
string getFuelType() {
    string fuel;
    cout << "Enter fuel type (Diesel or Petrol): ";
    cin >> fuel;

    // Keeps asking until the user types a valid fuel type
    while (fuel != "Diesel" && fuel != "diesel" &&
           fuel != "Petrol" && fuel != "petrol") {
        cout << "Please type Diesel or Petrol: ";
        cin >> fuel;
    }

    
    return fuel;
}

// Calculates the total CO2 produced
double calculateCO2(double distance, string fuelType) {
    double litresUsed = (distance / 100.0) * 9.66;   // 9.66 litres per 100 miles

    // Ternary operator chooses the correct CO2 value
    double co2PerLitre = (fuelType == "Diesel") ? 2.68 : 2.31;

    return litresUsed * co2PerLitre;
}
// Main function - starts the program, calls the other functions and shows the result
int main() {
    cout << "CO2 Emissions Calculator" << endl << endl;

    double miles = getDistance();
    string fuel = getFuelType();
    double totalCO2 = calculateCO2(miles, fuel);

    cout << endl;
    cout << "Estimated CO2 emissions: " << totalCO2 << " kg" << endl;

    return 0;
}