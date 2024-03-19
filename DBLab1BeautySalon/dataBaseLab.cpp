// dataBaseLab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>

#include "Client.h"
#include "Reservation.h"
#include "MasterFile.h"
#include "SlaveFile.h"


#include <string> 
#include <unordered_map>

#include <sstream>
#include <regex>
#include <limits>




void parse_command(const std::string& command, MasterFile& mf, SlaveFile& sf) {
    std::smatch match;

    if (std::regex_match(command, match, std::regex("get -m (\\w+)"))) {
        mf.Get_M(std::stoi(match[1]));
    }

    else if (std::regex_match(command, match, std::regex("insert -m ([\\w\\.@]+) ([\\w\\.@]+) ([\\w\\.@]+)"))) {
        mf.Insert_M(match[1].str().c_str(), match[2].str().c_str(), match[3].str().c_str());
    }
    else if (std::regex_match(command, match, std::regex("update -m ([\\w\\.@]+) ([\\w\\.@]+) ([\\w\\.@]+) ([\\w\\.@]+)"))) {
        mf.Update_M(std::stoi(match[1]), match[2].str().c_str(), match[3].str().c_str(), match[4].str().c_str());
    }
    else if (std::regex_match(command, match, std::regex("delete -m (\\w+)"))) {
        mf.Del_M(std::stoi(match[1]));
    }
    else if (std::regex_match(command, match, std::regex("calculate -m"))) {
        mf.Calc_M();
    }
    else if (std::regex_match(command, match, std::regex("ut -m"))) {
        mf.Ut_M();
    }
    else if (std::regex_match(command, match, std::regex("get -s (\\w+)"))) {
        sf.Get_S(std::stoi(match[1]));
    }
    else if (std::regex_match(command, match, std::regex("insert -s ([\\w\\.@:]+) ([\\w\\.@:]+) ([\\w\\.@:]+) ([\\w\\.@:]+)"))) {
        sf.Insert_S(std::stoi(match[1]), match[2].str().c_str(), match[3].str().c_str(), match[4].str().c_str());
    }
    else if (std::regex_match(command, match, std::regex("update -s ([\\w\\.@:]+) ([\\w\\.@:]+) ([\\w\\.@:]+) ([\\w\\.@:]+) ([\\w\\.@:]+)"))) {
        sf.Update_S(std::stoi(match[1]), std::stoi(match[2]), match[3].str().c_str(), match[4].str().c_str(), match[5].str().c_str());
    }

    else if (std::regex_match(command, match, std::regex("delete -s (\\w+)"))) {
        sf.Del_S(std::stoi(match[1]));
    }
    else if (std::regex_match(command, match, std::regex("calculate -s"))) {
        sf.Calc_S();
    }
    else if (std::regex_match(command, match, std::regex("ut -s"))) {
        sf.Ut_S();
    }
    else {
        std::cout << "Invalid command" << std::endl;
    }
}

void help() {
    std::cout << "Welcome to dataBaseLabProgram :)" << std::endl;
    std::cout << "Avaialble commands for Clients: get(id), insert(name, phone, email), update(id, name, phone, email), delete(id), calculate()" << std::endl;
    std::cout << "Avaialble commands for Reservations: get(id), insert(clientID, info, date, time), update(id, clientID, info, date, time), delete(id), calculate()" << std::endl;
    std::cout << "They are followed by space and then -*, where '*' could be 's' or 'm'" << std::endl;
    std::cout << "Here is example: 'get -m 1'" << std::endl;
}

void emptyLines(const int count) {

    for (int i = 0; i < count; i++) {
        std::cout << std::endl;
    }
}



int main()
{


    Client_Reservation cl_rs = Client_Reservation();
    SlaveFile sf = SlaveFile(cl_rs);
    MasterFile mf = MasterFile(cl_rs, sf);


    std::string command;
    const char Answer = 'y';
    char letterIterator = Answer;
    
       //Client m0 = { 0, "Client0", "0978856944", "testemail0@gmail.com"};
       //Client m1 = { 1, "Client1", "0978856988", "testemail1@gmail.com" };
       //Client m2 = { 2, "Client2", "0978856975", "testemail2@gmail.com" };
       //Client m3 = { 3, "Client3", "0978856774", "testemail3@gmail.com" };

       //mf.Save(&m0, 0);
       //mf.Save(&m1, 1);
       //mf.Save(&m2, 2);
       //mf.Save(&m3, 3);



       //Reservation r0 = { 0, 0, "Reservation0", "25.02", "12:14" };
       //Reservation r1 = { 1, 1, "Reservation1", "25.03", "12:05" };
       //Reservation r2 = { 2, 0, "Reservation2", "25.05", "12:19" };
       //Reservation r3 = { 3, 1, "Reservation3", "25.04", "12:18" };
       //Reservation r4 = { 4, 3, "Reservation4", "21.02", "12:16" };
       //Reservation r5 = { 5, 2, "Reservation5", "14.03", "12:15" };


       //sf.Save(&r0, 0);
       //sf.Save(&r1, 1);
       //sf.Save(&r2, 2);
       //sf.Save(&r3, 3);
       //sf.Save(&r4, 4);
       //sf.Save(&r5, 5);



       //reservationsRow rr0 = { 0, 2, -1, -1, -1, -1 };
       //reservationsRow rr1 = { 1, 3, -1, -1, -1, -1 };
       //reservationsRow rr2 = { 5, -1, -1, -1, -1, -1 };
       //reservationsRow rr3 = { 4, -1, -1, -1, -1, -1 };

       //cl_rs.SaveReservations(&rr0, 0);
       //cl_rs.SaveReservations(&rr1, 1);
       //cl_rs.SaveReservations(&rr2, 2);
       //cl_rs.SaveReservations(&rr3, 3);

    while (letterIterator == Answer) {

        help();

        emptyLines(1);

        std::cout << "Enter command followed by number: ";
        std::getline(std::cin, command);

        emptyLines(2);

        parse_command(command, mf, sf);

        emptyLines(2);


        std::cout << "press any key to exit or 'y' to continue: ";
        std::cin >> letterIterator;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        system("cls");
    }


    return 0;
}

