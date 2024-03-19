#pragma once

#include <iostream>
#include "Client_Reservation.h"
#include "Reservation.h"


class SlaveFile {

private:

	const char* FilePath = "Reservations.sf";
	Client_Reservation c_client_reservation;
	Reservation c_reservation;
	size_t clientID;

public:

	SlaveFile(Client_Reservation& cl_rs);
	SlaveFile();

	int Save(const Reservation* clientReservation, const size_t position);
	int Read(const size_t position);
	int CalculateSize();

	void Get_S(size_t id);
	void Del_S(size_t id);
	void Update_S(size_t id, const int clientID, const char info[MAX_INFO_LENGTH], const char date[MAX_DATE_LENGTH], const char time[MAX_TIME_LENGTH]);
	void Insert_S(const int clientID, const char info[MAX_INFO_LENGTH], const char date[MAX_DATE_LENGTH], const char time[MAX_TIME_LENGTH]);
	void Calc_S();
	void Ut_S();
};