#pragma once

#define MAX_INFO_LENGTH 32
#define MAX_DATE_LENGTH 12
#define MAX_TIME_LENGTH 6
struct Reservation
{

private:
	size_t c_reservationID;
	size_t c_clientID;
	char c_info[MAX_INFO_LENGTH];
	size_t c_alive;
	bool c_recognizer;
	char c_date[MAX_DATE_LENGTH];
	char c_time[MAX_TIME_LENGTH];


public:
	Reservation() {}

	Reservation(const size_t reservationID, const size_t clientID, const char info[MAX_INFO_LENGTH], const char date[MAX_DATE_LENGTH], const char time[MAX_TIME_LENGTH]);

	void Update(const int clientID, const char info[MAX_INFO_LENGTH], const char date[MAX_DATE_LENGTH], const char time[MAX_TIME_LENGTH]);
	void ShowInfo();
	void MakeDead();
	size_t IsAlive();
	size_t GetClientID();
	size_t ClientID();
};

