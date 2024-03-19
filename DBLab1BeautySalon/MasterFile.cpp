#include <iostream>
#include "MasterFile.h"
#include "Client.h"

MasterFile::MasterFile(Client_Reservation& cl_rs, SlaveFile& sf) {
    c_client_reservation = cl_rs;
    c_sf = sf;
}



int MasterFile::Save(const Client* client, const size_t position) const {
    FILE* file;

    int ret = fopen_s(&file, FilePath, "rb+");

    if (ret != 0) {
        fclose(file);
        perror("Error opening the file for reading and writing");
        return ret;
    }

    ret = fseek(file, position * sizeof(Client), SEEK_SET);

    if (ret != 0) {
        fclose(file);
        perror("Error setting file position");
        return ret;
    }

    if (fwrite(client, sizeof(Client), 1, file) != 1) {
        fclose(file);
        perror("Error writing data to the file");
        return -1;
    }


    fclose(file);
    printf("Client saved to file %s at position %u\n", FilePath, position);
    return 0;
}



int MasterFile::Read(const size_t position) {

    FILE* file;

    int ret = fopen_s(&file, FilePath, "rb");

    if (ret != 0) {
        fclose(file);
        perror("Error opening the file for reading");
        return ret;
    }

    ret = fseek(file, position * sizeof(struct Client), SEEK_SET);

    if (ret != 0) {
        fclose(file);
        printf("Can't seek through the file: %s\n", FilePath);
        return ret;

    }

    if (fread(&c_client, sizeof(struct Client), 1, file) != 1) {
        fclose(file);
        printf("Client can't read from file: %s\n", FilePath);
        return -1;
    }

    fclose(file);
    return 0;


}


int MasterFile::CalculateSize() {
    FILE* file;


    if (fopen_s(&file, FilePath, "rb") != 0) {
        fclose(file);
        perror("Error opening the file for reading");
        return -1;
    }


    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        perror("Error seeking to the end of the file");
        return -1;
    }

    long fileSize = ftell(file);

    if (fileSize == -1) {
        fclose(file);
        return -1;
    }

    fclose(file);
    return fileSize;
}


void MasterFile::Get_M(const size_t id) {
    if (Read(id) != 0) {
        std::cout << "There is no client with such id" << std::endl;
        return;
    }

    if (c_client.IsAlive() != 0) {

        std::cout << "Client: ";
        c_client.ShowInfo();

        std::cout << std::endl;

        std::cout << "Reservations: " << std::endl;

        c_client_reservation.LoadReservations(id);
        auto reservationsIDs = c_client_reservation.GetReservations();
        for (int i = 0; i < MAX_RESERVATIONS_COUNT; i++) {
            if (reservationsIDs[i] != -1) {
                c_sf.Get_S(reservationsIDs[i]);
            }
        }
        return;
    }

    std::cout << "You've deleted client with such id" << std::endl;
}

void MasterFile::Del_M(size_t id) {
    if (Read(id) == 0) {
        if (c_client.IsAlive() != 0) {
            c_client.MakeDead();
            Save(&c_client, id);
        }
        else {
            std::cout << "You have already deleted this Client" << std::endl;
        }
    }
}

void MasterFile::Update_M(const size_t id, const char name[MAX_NAME_LENGTH], const char phone[MAX_PHONE_LENGTH], const char email[MAX_EMAIL_LENGTH]) {
    if (Read(id) == 0) {
        if (c_client.IsAlive() != 0) {
            c_client.Update(name, phone, email);
            Save(&c_client, id);
            c_client.ShowInfo();
        }
    }
}

void MasterFile::Insert_M(const char name[MAX_NAME_LENGTH], const char phone[MAX_PHONE_LENGTH], const char email[MAX_EMAIL_LENGTH]) {
    int fileSize = CalculateSize();

    if (fileSize != -1) {
        int clientsCount = fileSize / sizeof(struct Client);
        Client client = Client(clientsCount, name, phone, email);
        Save(&client, clientsCount);
        c_client_reservation.AddReservationsRow(clientsCount);
    };
}

void MasterFile::Calc_M() {

    long fileSize = CalculateSize();
    int aliveClientsCount = 0;

    if (fileSize >= 0) {
        size_t clientsCount = fileSize / sizeof(struct Client);

        for (int i = 0; i < clientsCount; i++) {
            if (Read(i) == 0) {
                if (c_client.IsAlive() != 0) {
                    aliveClientsCount++;
                }
            }
        }
        printf("Clients count = %u", aliveClientsCount);
    }
}

void MasterFile::Ut_M() {

    long fileSize = CalculateSize();

    if (fileSize >= 0) {
        size_t clientsCount = fileSize / sizeof(struct Client);

        for (int i = 0; i < clientsCount; i++) {
            if (Read(i) == 0) {
                if (c_client.IsAlive() != 0) {
                    c_client.ShowInfo();
                }
            }
        }
    }
}

