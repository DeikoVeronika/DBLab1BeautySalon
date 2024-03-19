#pragma once

#define MAX_NAME_LENGTH 32
#define MAX_EMAIL_LENGTH 64
#define MAX_PHONE_LENGTH 64


struct Client {

private:
	size_t c_clientID;
	char c_name[MAX_NAME_LENGTH];
	char c_phone[MAX_PHONE_LENGTH];
	char c_email[MAX_EMAIL_LENGTH];
	size_t c_alive = 1;
	int c_reservationsIDs[20] = { -1 };

public:
	Client() {}

	Client(const size_t id, const char name[MAX_NAME_LENGTH], const char phone[MAX_PHONE_LENGTH], const char email[MAX_EMAIL_LENGTH]);

	void Update(const char name[MAX_NAME_LENGTH], const char phone[MAX_PHONE_LENGTH], const char email[MAX_EMAIL_LENGTH]);
	void ShowInfo();
	void MakeDead();
	size_t IsAlive();
};