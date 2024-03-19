#include <string.h>
#include <iostream>
#include "Reservation.h"

Reservation::Reservation(const size_t reservationID, const size_t clientID, const char info[MAX_INFO_LENGTH], const char date[MAX_DATE_LENGTH], const char time[MAX_TIME_LENGTH])
	: c_alive(1), c_reservationID(reservationID), c_clientID(clientID)
{
	strcpy_s(c_info, MAX_INFO_LENGTH, info);
	strcpy_s(c_date, MAX_DATE_LENGTH, date);
	strcpy_s(c_time, MAX_TIME_LENGTH, time);
}



void Reservation::ShowInfo() {
	std::cout << "{ ReservationID: " << c_reservationID << " }, ";
	std::cout << "{ ClientID: " << c_clientID << " }, ";
	std::cout << "{ Info: " << c_info << " }, ";
	std::cout << "{ Date: " << c_date << " }, ";
	std::cout << "{ Time: " << c_time << " }, " << std::endl;;
}

void Reservation::MakeDead() {
	c_alive = 0;
}

size_t Reservation::IsAlive() {
	return c_alive;
}

size_t Reservation::GetClientID() {
	return c_clientID;
}

void Reservation::Update(const int clientID, const char info[MAX_INFO_LENGTH], const char date[MAX_DATE_LENGTH], const char time[MAX_TIME_LENGTH]) {
	strcpy_s(c_info, MAX_INFO_LENGTH, info);
	strcpy_s(c_date, MAX_DATE_LENGTH, date);
	strcpy_s(c_time, MAX_TIME_LENGTH, time);
	c_clientID = clientID;
}
