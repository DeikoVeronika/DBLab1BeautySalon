#include "Client_Reservation.h"


Client_Reservation::Client_Reservation() {

}

const reservationsRow& Client_Reservation::GetReservations() {

    return c_reservationsIDs;
}

const int Client_Reservation::LoadReservations(const size_t position) {
    FILE* file;

    int ret = fopen_s(&file, FilePath, "rb");

    if (ret != 0) {
        fclose(file);
        perror("Error opening the file for reading");
        return ret;
    }

    ret = fseek(file, position * sizeof(reservationsRow), SEEK_SET);

    if (ret != 0) {
        fclose(file);
        printf("Can't seek through the file: %s\n", FilePath);
        return ret;

    }

    if (fread(&c_reservationsIDs, sizeof(reservationsRow), 1, file) != 1) {
        fclose(file);
        printf("ReviewsRow can't read from file: %s\n", FilePath);
        return -1;
    }

    fclose(file);
    return 0;

}

const int Client_Reservation::SaveReservations(reservationsRow* reservationsIDs, const size_t position) {
    FILE* file;

    int ret = fopen_s(&file, FilePath, "rb+");

    if (ret != 0) {
        fclose(file);
        perror("Error opening the file for reading and writing");
        return ret;
    }

    ret = fseek(file, position * sizeof(reservationsRow), SEEK_SET);

    if (ret != 0) {
        fclose(file);
        perror("Error setting file position");
        return ret;
    }

    if (fwrite(reservationsIDs, sizeof(reservationsRow), 1, file) != 1) {
        fclose(file);
        perror("Error writing data to the file");
        return -1;
    }


    fclose(file);
    printf("ReservationsRow saved to file %s at position %u\n", FilePath, position);
    return 0;

}


void Client_Reservation::InsertReservationID(const size_t rowNumber, const size_t value) {

    if (LoadReservations(rowNumber) == 0) {
        for (int i = 0; i < MAX_RESERVATIONS_COUNT; i++) {
            if (c_reservationsIDs[i] == value) {
                break;
            }
            if (c_reservationsIDs[i] == DEFAULT_NO_CONNECTION_VALUE) {
                c_reservationsIDs[i] = value;
                break;
            }
        }
        SaveReservations(&c_reservationsIDs, rowNumber);
    }
}

void Client_Reservation::DeleteReservationID(const size_t rowNumber, const size_t value) {

    if (LoadReservations(rowNumber) == 0) {
        for (int i = 0; i < MAX_RESERVATIONS_COUNT; i++) {
            if (c_reservationsIDs[i] == value) {
                c_reservationsIDs[i] = DEFAULT_NO_CONNECTION_VALUE;
                break;
            }
        }
        SaveReservations(&c_reservationsIDs, rowNumber);
    }
}

void Client_Reservation::AddReservationsRow(const size_t rowNumber) {
    reservationsRow rr;
    for (int i = 0; i < MAX_RESERVATIONS_COUNT; i++) {
        rr[i] = DEFAULT_NO_CONNECTION_VALUE;
    }
    SaveReservations(&rr, rowNumber);
}

