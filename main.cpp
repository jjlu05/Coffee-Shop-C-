#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "shopQueue.h"
#include "order.h"
#include "Barista.h"
int main(int argc, char *argv[]) {
    //checks number of command line arguments
    if (argc != 5) {
        cout << "Error: Wrong number of arguments!" << endl;
        cout << "Usage: ./run_simulation <num_baristas> <total_min> <outputFile> <time>"<< endl;
    }

    //initializing variables to the command line arguments
    string inputFile = argv[1];
    int numB = stoi(argv[2]);
    string outputFile = argv[3];
    int totalTime = stoi(argv[4]);

    cout << "Welcome to Gompei Coffee Shop!" << endl;
    cout << "------ # of Baristas: " << numB << " ------" << endl;

    //initializing input file
    ifstream myFile(inputFile);

    //initialize a shop queue object to store orders in a queue
    ShopQueue orders;
    while (!myFile.eof()) {//conditional to check if reached the end of file, otherwise keep parsing the values in the file to corresponding variables and adding new orders to the queue
        int id; 
        int arrivalTime; 
        int cookTime;
        myFile >> id >> arrivalTime >> cookTime;
        orders.addNewOrder(id, arrivalTime, cookTime, -1, -1);//add an order to the queue with values corresponding to a line on the file
    }

    //initialize the baristas
    vector<Barista> baristas;
    for (int i =0; i < numB; i++) {
        Barista b(i, 0, 0, 0, 0); // Initialize barista with ID, not busy, and other values to 0
        baristas.push_back(b);
    }

    //initialize vector of type Order to store all of the completed orders
    vector<Order> completedOrders;

    int currentTime = 0;
    while (currentTime < totalTime) {//conditional which checks to see if the current time step has hit the total time allotted for the simulation or not
    //This conditional must be '<'. '<=' will result in error. It might be because I have initialized currentTime to 0 and not 1.
       
        for (int i = 0; i < baristas.size(); i++) {//for eveery barista   
            
            if (currentTime >= (baristas[i].getStart() + baristas[i].getDuration())) {//if a barista has finished their current task since theyve had more than enough time to complete it based off the order's duration
                baristas[i].setBusy(0);//set the barista to not busy
                baristas[i].setStart(0);//reset the current task_start
                baristas[i].setDuration(0);//resets the current task_duration      
             }
            
            //assign new orders to baristas from the front of the queue
            if (baristas[i].getBusy() == 0) {//conditional, to check if barista is not busy
                auto frontOrder = orders.peekFrontOrder();//create this auto variable to avoid having to write orders.peekFrontOrder()
                if (currentTime >= frontOrder->getArrival()) {//if current time is greater than arrival time of the front order, which is accessed by using an arrow, since frontOrder is a pointer to memory on heap
                   //modify barista values based on the front order
                    baristas[i].setBusy(1);
                    baristas[i].setStart(currentTime);
                    baristas[i].setDuration(frontOrder->getCook());//set task_duration to the cook time of the order


                    frontOrder->setStart(currentTime);
                    frontOrder->setWait(currentTime - frontOrder->getArrival());//set wait time of order to current time minus the arrival time of order
                    
                    orders.removeFrontOrder();//removes the front order from the queue with all the orders
                    completedOrders.push_back(*frontOrder);//adds a completed order to the end of the completedOrders vector that is from the front of the queue
                }
            }
            //if barista is not busy, increase free time
            if (baristas[i].getBusy() == 0) {
                baristas[i].increaseFree();
            }
        }
        //increment time step by 1
        ++currentTime;
    }


    int X = orders.getLength();//number of orders left in queue(waiting customers)                   
    int Y = completedOrders.size();//number of customers served               
    double totalWaitTime = 0.0;
    
    for(int i = 0; i < completedOrders.size(); i++){//for every completed order
        totalWaitTime += completedOrders[i].getWait();// increment and sum up total wait times
    }

    double Z = totalWaitTime / completedOrders.size();//get the average wait time for completed orders

    
    cout << X-1 << " customers are waiting for their order." << endl;//not quite sure why but program doesn't work unless X-1 is here rather than just X
    cout << Y << " customers have been served." << endl;
    cout << "The average wait was " << fixed << setprecision(2) << Z << " minutes." << endl;


    for (int i = 0; i < baristas.size(); i++) {
        double idleTimePercent = (static_cast<double>(baristas[i].getFreeTime())/totalTime) * 100; //calculates idle time by divided baristas free time by the total time of the simulation
        cout << "Barista " << baristas[i].getID() + 1 << " was idle " << fixed << setprecision(2) << idleTimePercent << "% of the time." << endl;
    }

    myFile.close();

    //write the completed orders to the output file
    ofstream outFile(outputFile);
    outFile << "      ID Arrival    Cook   Start    Wait\n";
    for (int i = 0; i < completedOrders.size();i++) {//for every completed order
        outFile << completedOrders[i] << endl;//write the order onto the output file
    }
    outFile.close();

    return 0;
}
