#ifndef DATA_H
#define DATA_H

#include <string>

using namespace std;

class Data {

    private:
        string title;
        double price;
        int quantity;
        char result;

    public:
        Data();
        Data(string title, double price, int quantity);

        void setTitle(string title);
        void setPrice(double price);
        void setQuantity(int quantity);
        void setResult(char result);

        string getTitle();
        double getPrice();
        int getQuantity();
        char getResult();

        int compareTo(Data data);
};

#endif // DATA_H
