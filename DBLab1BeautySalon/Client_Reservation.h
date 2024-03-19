#include <unordered_map>
#include <vector>

#include "Client.h"
#include "Reservation.h"
#pragma once

#define MAX_RESERVATIONS_COUNT 6
typedef int reservationsRow[MAX_RESERVATIONS_COUNT];
#define DEFAULT_NO_CONNECTION_VALUE -1

class Client_Reservation {
private:
	const char* FilePath = "connectionTable.ct";
	reservationsRow c_reservationsIDs;

public:

	const reservationsRow& GetReservations();
	const int LoadReservations(const size_t position);
	const int SaveReservations(reservationsRow* reservationsIDs, const size_t position);
	void InsertReservationID(const size_t rowNumber, const size_t value);
	void DeleteReservationID(const size_t rowNumber, const size_t value);
	void AddReservationsRow(const size_t position);

	Client_Reservation();

};