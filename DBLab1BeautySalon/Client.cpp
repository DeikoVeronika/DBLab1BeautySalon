#include <string.h>
#include <iostream>
#include "Client.h"

Client::Client(const size_t id, const char name[MAX_NAME_LENGTH], const char phone[MAX_PHONE_LENGTH], const char email[MAX_EMAIL_LENGTH])
	: c_alive(1), c_clientID(id) {
	strcpy_s(c_name, name);
	strcpy_s(c_phone, phone);
	strcpy_s(c_email, email);
}

void Client::ShowInfo() {
	std::cout << "{ ClientID: " << c_clientID << " }, ";
	std::cout << "{ Name: " << c_name << " }, ";
	std::cout << "{ Phone: " << c_phone << " }, ";
	std::cout << "{ Email: " << c_email << " }." << std::endl;
}

void Client::MakeDead() {
	c_alive = 0;
}

size_t Client::IsAlive() {
	return c_alive;
}

void Client::Update(const char name[MAX_NAME_LENGTH], const char phone[MAX_PHONE_LENGTH], const char email[MAX_EMAIL_LENGTH]) {
	strcpy_s(c_name, name);
	strcpy_s(c_phone, phone);
	strcpy_s(c_email, email);
}
	