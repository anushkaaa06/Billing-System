#include<iostream>
#include<string>
#include<ctime>
#include<iomanip>
#include<fstream>
using namespace std;

class Product {
private:
    int productNumber;
    string productName;
    float productRate;

public:
    Product() {
        productNumber = 0;
        productName = "";
        productRate = 0.0;
    }

    Product(int number, string name, float rate) {
        productNumber = number;
        productName = name;
        productRate = rate;

        ofstream outProduct;
        outProduct.open("Products.txt", ios::out | ios::app);
        outProduct << productNumber << ' ' << productName << ' ' << productRate << endl;
        outProduct.close();
    }

    int getNumber() {
        return productNumber;
    }

    string getName() {
        return productName;
    }

    float getRate() {
        return productRate;
    }

    void setNumber(int x) {
        productNumber = x;
    }

    void setName(string x) {
        productName = x;
    }

    void setRate(float x) {
        productRate = x;
    }
};

class Bill {
public:
    string date;
    float totalAmount;

    Bill() {
        time_t now = time(0);
        char* dt = ctime(&now);
        date = dt;
        totalAmount = 0;
    }
};

class BillItems {
private:
    Product product;
    int quantity;

public:
    void getItem(int code) {
        ifstream prod;
        prod.open("Products.txt", ios::in);
        int pn;
        string pp;
        float pr;
        while (prod >> pn >> pp >> pr) {
            if (pn == code) {
                product.setNumber(pn);
                product.setName(pp);
                product.setRate(pr);
                break;
            }
        }
        prod.close();
    }

    void setQuantity(int x) {
        quantity = x;
    }

    float getAmount() {
        return product.getRate() * quantity;
    }

    void printItemDet() {
        cout << "\t" << setw(14) << product.getNumber() << "\t" << setw(12)
             << product.getName() << "\t" << setw(12) << product.getRate()
             << "\t" << setw(8) << quantity << "\t";
    }
};

class Invoice : public Bill {
private:
    int numOfItems;
    BillItems item[50];
};

class NavPages {
public:
    static void intro() {
        cout << "\n\n\n\tBILLING SYSTEM" << endl;
        cout << "\n\t================================================================\n";
        cout << "\n\n\tMADE BY:";
        cout << "\n\n\tAnushka Gupta";
    }

    static void user() {
        int ch;
        system("clear"); // "cls" for Windows
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t1. CUSTOMER";
        cout << "\n\n\t2. ADMINISTRATOR";
        cout << "\n\n\t3. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3): ";
        cin >> ch;
        switch (ch) {
            case 1: customer(); break;
            case 2: admin(); break;
            case 3: exit(0);
        }
    }

    static void customer() {
        int n;
        BillItems item[20];
        system("clear");
        cout << "\n\n\tENTER THE NUMBER OF ITEMS: ";
        cin >> n;
        displayProduct();
        int code, qty;
        for (int i = 0; i < n; i++) {
            cout << "\n\tENTER ITEM CODE: ";
            cin >> code;
            item[i].getItem(code);
            cout << "\n\tENTER ITEM QUANTITY: ";
            cin >> qty;
            item[i].setQuantity(qty);
        }
        Bill fBill;
        for (int i = 0; i < n; i++) {
            fBill.totalAmount += item[i].getAmount();
        }

        system("clear");
        cout << "\n\n\tINVOICE\t\t\tDate/Time: " << fBill.date;
        cout << "\t==========================================================================" << endl;
        cout << "\tProduct Number\tProduct Name\tProduct Rate\tQuantity\tAmount" << endl;
        for (int i = 0; i < n; i++) {
            item[i].printItemDet();
            cout << setw(6) << item[i].getAmount() << endl;
        }
        cout << "\n\n\t\t\t\tTOTAL AMOUNT: " << fBill.totalAmount;
        cout << "\n\tThank You for Shopping" << endl;
        cout << "\n\tPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    static void admin() {
        while (1) {
            system("clear");
            int ch;
            cout << "\n\n\n\tADMIN MENU";
            cout << "\n\n\t1. CREATE PRODUCT";
            cout << "\n\n\t2. DISPLAY ALL PRODUCTS";
            cout << "\n\n\t3. MODIFY PRODUCT";
            cout << "\n\n\t4. DELETE PRODUCT";
            cout << "\n\n\t5. BACK TO MAIN MENU";
            cout << "\n\n\tPlease Enter Your Choice (1-5): ";
            cin >> ch;
            switch (ch) {
                case 1: createProduct(); break;
                case 2: displayProduct(); break;
                case 3: modifyProduct(); break;
                case 4: deleteProduct(); break;
                case 5: return;
                default: break;
            }
        }
    }

    static void createProduct() {
        system("clear");
        int n;
        string p;
        float r;
        cout << "\n\n\tENTER THE DETAILS OF THE PRODUCT" << endl;
        cout << "\n\tENTER THE PRODUCT NUMBER: ";
        cin >> n;
        cout << "\n\tENTER THE PRODUCT NAME: ";
        cin >> p;
        cout << "\n\tENTER THE PRODUCT RATE: ";
        cin >> r;
        Product prod(n, p, r);
        cout << "\n\tPRODUCT ADDED SUCCESSFULLY!";
        cin.ignore();
        cin.get();
    }

    static void displayProduct() {
        system("clear");
        ifstream displayProducts("Products.txt");
        int n;
        string p;
        float r;
        cout << "\n\n\tDISPLAY ALL PRODUCTS\n\t=============================================" << endl;
        while (displayProducts >> n >> p >> r) {
            cout << "\n\tPRODUCT NUMBER : " << n;
            cout << "\n\tPRODUCT NAME   : " << p;
            cout << "\n\tRATE OF PRODUCT: " << r;
            cout << "\n\t---------------------------------------------";
        }
        displayProducts.close();
        cout << "\n\tPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    static void modifyProduct() {
        system("clear");
        displayProduct();
        ifstream prodIn("Products.txt");
        ofstream prodTmp("temp.txt");
        cout << "\n\tEnter the Product Number to Modify: ";
        int modNum;
        cin >> modNum;
        int n;
        string p;
        float r;
        while (prodIn >> n >> p >> r) {
            if (n == modNum) {
                cout << "\n\tEnter new rate: ";
                cin >> r;
            }
            prodTmp << n << ' ' << p << ' ' << r << endl;
        }
        prodIn.close();
        prodTmp.close();
        remove("Products.txt");
        rename("temp.txt", "Products.txt");
        cout << "\n\n\tPRODUCT RATE UPDATED SUCCESSFULLY";
        cin.ignore();
        cin.get();
    }

    static void deleteProduct() {
        system("clear");
        displayProduct();
        ifstream prodIn("Products.txt");
        ofstream prodTmp("temp.txt");
        cout << "\n\tEnter the Product Number to Delete: ";
        int delNum;
        cin >> delNum;
        int n;
        string p;
        float r;
        while (prodIn >> n >> p >> r) {
            if (n != delNum) {
                prodTmp << n << ' ' << p << ' ' << r << endl;
            }
        }
        prodIn.close();
        prodTmp.close();
        remove("Products.txt");
        rename("temp.txt", "Products.txt");
        cout << "\n\n\tPRODUCT DELETED SUCCESSFULLY";
        cin.ignore();
        cin.get();
    }
};

int main() {
    NavPages::intro();
    cin.get();
    system("clear");
    while (1) {
        NavPages::user();
    }
}
