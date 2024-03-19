#include "SlaveFile.h"

SlaveFile::SlaveFile(Client_Reservation& cl_rs) {
    c_client_reservation = cl_rs;
}

SlaveFile::SlaveFile() {
}

int SlaveFile::Save(const Reservation* clientReservation, const size_t position) {

    FILE* file;

    int ret = fopen_s(&file, FilePath, "rb+");

    if (ret != 0) {
        fclose(file);
        perror("Error opening the file for reading and writing");
        return ret;
    }

    ret = fseek(file, position * sizeof(Reservation), SEEK_SET);

    if (ret != 0) {
        fclose(file);
        perror("Error setting file position");
        return ret;
    }

    if (fwrite(clientReservation, sizeof(Reservation), 1, file) != 1) {
        fclose(file);
        perror("Error writing data to the file");
        return -1;
    }

    fclose(file);
    printf("Reservation saved to file %s at position %u\n", FilePath, position);
    return 0;
};



int SlaveFile::Read(const size_t position) {

    FILE* file;

    int ret = fopen_s(&file, FilePath, "rb");

    if (ret != 0) {
        perror("Error opening the file for reading");
        return ret;
    }

    ret = fseek(file, position * sizeof(struct Reservation), SEEK_SET);

    if (ret != 0) {
        printf("Can't seek through the file: %s\n", FilePath);
        fclose(file);
        return ret;
    }

    if (fread(&c_reservation, sizeof(struct Reservation), 1, file) != 1) {
        printf("Reservation can't be read from file: %s\n", FilePath);
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
};



int SlaveFile::CalculateSize() {
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


void SlaveFile::Get_S(size_t id) {
    if (Read(id) != 0) {
        std::cout << "There is no reservation with such id" << std::endl;
        return;
    }

    if (c_reservation.IsAlive() != 0) {
        c_reservation.ShowInfo();
        return;
    }

    std::cout << "You've deleted reservation with such id" << std::endl;
};

void SlaveFile::Del_S(size_t id) {
    if (Read(id) == 0) {
        if (c_reservation.IsAlive() != 0) {
            c_reservation.MakeDead();
            Save(&c_reservation, id);
            c_client_reservation.DeleteReservationID(c_reservation.GetClientID(), id);
        }
        else {
            std::cout << "You have already deleted this Reservation" << std::endl;
        }
    }
};

void SlaveFile::Update_S(size_t id, const int clientID, const char info[MAX_INFO_LENGTH], const char date[MAX_DATE_LENGTH], const char time[MAX_TIME_LENGTH]) {

    if (Read(id) == 0) {
        if (c_reservation.IsAlive() != 0) {
            c_reservation.Update(clientID, info, date, time);
            Save(&c_reservation, id);
            c_client_reservation.InsertReservationID(clientID, id);
        }
    }
};


void SlaveFile::Insert_S(const int clientID, const char info[MAX_INFO_LENGTH], const char date[MAX_DATE_LENGTH], const char time[MAX_TIME_LENGTH]) {

    int fileSize = CalculateSize();

    if (fileSize != -1) {
        int reservationsCount = fileSize / sizeof(struct Reservation);
        Reservation reservation = Reservation(reservationsCount, clientID, info, date, time);
        Save(&reservation, reservationsCount);
        c_client_reservation.InsertReservationID(clientID, reservationsCount);
    }
};


void SlaveFile::Calc_S() {

    long fileSize = CalculateSize();
    int aliveReservationsCount = 0;

    if (fileSize != -1) {

        size_t reservationsCount = fileSize / sizeof(struct Reservation);

        for (int i = 0; i < reservationsCount; i++) {
            if (Read(i) == 0) {
                if (c_reservation.IsAlive() != 0) {
                    aliveReservationsCount++;
                }
            }
        }
        printf("Reservation count = %u", aliveReservationsCount);
    }
};

void SlaveFile::Ut_S() {

    long fileSize = CalculateSize();

    if (fileSize != -1) {

        size_t reservationsCount = fileSize / sizeof(struct Reservation);

        for (int i = 0; i < reservationsCount; i++) {
            if (Read(i) == 0) {
                if (c_reservation.IsAlive() != 0) {
                    c_reservation.ShowInfo();
                }
            }
        }
    }
};