#include <iostream>
#include <string>
#include <vector>

using namespace std;
class FoodItem {
public:
    FoodItem(string name) : name(name) {}
    virtual ~FoodItem() {}
    virtual void printInfo() const = 0;
    virtual double calculateCalories() const = 0;

protected:
    string name;
};

class Meat : public FoodItem {
public:
    Meat(string name, double proteinPer100g, double fatPer100g) : FoodItem(name), proteinPer100g(proteinPer100g), fatPer100g(fatPer100g) {}
    void printInfo() const override {
        cout << "Meat: " << name << ", Protein: " << proteinPer100g << "g/100g, Fat: " << fatPer100g << "g/100g" << endl;
    }

    double calculateCalories() const override {
        return (proteinPer100g * 4) + (fatPer100g * 9);
    }

private:
    double proteinPer100g;
    double fatPer100g;
};

class Fruit : public FoodItem {
public:
    Fruit(string name, double carbsPer100g) : FoodItem(name), carbsPer100g(carbsPer100g) {}
    void printInfo() const override {
        cout << "Fruit: " << name << ", Carbs: " << carbsPer100g << "g/100g" << endl;
    }
    double calculateCalories() const override {
        return carbsPer100g * 4;
    }

private:
    double carbsPer100g;
};

class Grain : public FoodItem {
public:
    Grain(string name, double carbsPer100g, double fiberPer100g) : FoodItem(name), carbsPer100g(carbsPer100g), fiberPer100g(fiberPer100g) {}
    void printInfo() const override {
        cout << "Grain: " << name << ", Carbs: " << carbsPer100g << "g/100g, Fiber: " << fiberPer100g << "g/100g" << endl;
    }
    double calculateCalories() const override {
        return (carbsPer100g * 4) - (fiberPer100g * 2);
    }

private:
    double carbsPer100g;
    double fiberPer100g;
};

class CalorieCalculator {
public:
    ~CalorieCalculator() {
        for (size_t i = 0; i < foodItems.size(); ++i) {
            delete foodItems[i];
        }
    }

    void addItem(FoodItem* item) {
        foodItems.push_back(item);
    }

    void listItems() const {
        if (foodItems.empty()) {
            cout << "No food items!\n";
        }
        else {
            cout << "Food items:\n";
            for (const auto& item : foodItems) {
                item->printInfo();
            }
        }
    }

    double calculateTotalCalories() const {
        double totalCalories = 0;
        for (const auto& item : foodItems) {
            totalCalories += item->calculateCalories();
        }
        return totalCalories;
    }

private:
    vector<FoodItem*> foodItems;
};

int main() {
    CalorieCalculator calculator;

    string choice;
    while (true) {
        cout << "\n\nMENU\n===========================\n";
        cout << "1. Add Meat\n2. Add Fruit\n3. Add Grain\n";
        cout << "4. List Items\n5. Calculate Total Calories\n0. Exit\nChoose: ";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == "0") {
            break;
        }
        else if (choice == "4") {
            calculator.listItems();
        }
        else if (choice == "5") {
            cout << "Total Calories: " << calculator.calculateTotalCalories() << endl;
        }
        else if (choice == "1" || choice == "2" || choice == "3") {
            string name;
            double value1, value2;

            cout << "Name: "; getline(cin, name);

            while (true) {
                cout << "Value 1: ";
                if (cin >> value1) {
                    break;
                }
                else {
                    cout << "Invalid input. Please enter a valid number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            if (choice == "1") {
                while (true) {
                    cout << "Value 2: ";
                    if (cin >> value2) {
                        break;
                    }
                    else {
                        cout << "Invalid input. Please enter a valid number.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                calculator.addItem(new Meat(name, value1, value2));
            }
            else if (choice == "2") {
                calculator.addItem(new Fruit(name, value1));
            }
            else if (choice == "3") {
                while (true) {
                    cout << "Value 2: ";
                    if (cin >> value2) {
                        break;
                    }
                    else {
                        cout << "Invalid input. Please enter a valid number.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                calculator.addItem(new Grain(name, value1, value2));
            }
        
        else {
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}

       