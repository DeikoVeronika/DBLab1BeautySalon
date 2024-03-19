#pragma once
#include "SlaveFile.h"
#include "Client_Reservation.h"


class MasterFile {
private:
	Client_Reservation c_client_reservation;
	Client c_client;
	Reservation c_reservation;
	SlaveFile c_sf;
	const char* FilePath = "Client.mf";

public:
	MasterFile(Client_Reservation& cl_rs, SlaveFile& sf);

	int Save(const Client* client, const size_t position) const;
	int Read(const size_t position);
	int CalculateSize();

	void Get_M(const size_t id);
	void Del_M(size_t id);
	void Update_M(const size_t id, const char name[MAX_NAME_LENGTH], const char phone[MAX_PHONE_LENGTH], const char email[MAX_EMAIL_LENGTH]);
	void Insert_M(const char name[MAX_NAME_LENGTH], const char phone[MAX_PHONE_LENGTH], const char email[MAX_EMAIL_LENGTH]);
	void Calc_M();
	void Ut_M();

};
