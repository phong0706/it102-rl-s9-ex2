#include <stdio.h>
#include <string.h>

struct FlightTicket {
    char pnrCode[15];
    char passengerName[50];
    int ticketClass;
    float baggageWeight;
    float baggageFee;
};

int main() {
    struct FlightTicket danhSachVe[100];
    int soLuong = 0;
    int choice;

    do {
        printf("\n=== HE THONG BAN VE VA CHECK-IN MAY BAY ===\n");
        printf("1. Them ve may bay moi\n");
        printf("2. Hien thi danh sach ve\n");
        printf("3. Cap nhat hanh ly theo PNR\n");
        printf("4. Xoa ve theo PNR\n");
        printf("5. Thoat\n");
        printf("Lua chon cua b?n: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("[LOI] Lua chon khong hop le!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (choice == 1) {
            if (soLuong >= 100) {
                printf("Danh sach ve da day, khong the them moi!\n");
                continue;
            }

            printf("Nhap ma PNR: ");
            fgets(danhSachVe[soLuong].pnrCode, sizeof(danhSachVe[soLuong].pnrCode), stdin);
            danhSachVe[soLuong].pnrCode[strcspn(danhSachVe[soLuong].pnrCode, "\n")] = '\0';

            printf("Nhap ho ten hanh khach: ");
            fgets(danhSachVe[soLuong].passengerName, sizeof(danhSachVe[soLuong].passengerName), stdin);
            danhSachVe[soLuong].passengerName[strcspn(danhSachVe[soLuong].passengerName, "\n")] = '\0';

            do {
                printf("Nhap hang ve (1-Eco, 2-Deluxe, 3-Business): ");
                scanf("%d", &danhSachVe[soLuong].ticketClass);
                while (getchar() != '\n');
                if (danhSachVe[soLuong].ticketClass < 1 || danhSachVe[soLuong].ticketClass > 3) {
                    printf("[LOI] Hang ve khong hop le! Nhap lai tu 1 den 3.\n");
                } else {
                    break;
                }
            } while (1);

            printf("Nhap kh?i lu?ng hành lý (kg): ");
            scanf("%f", &danhSachVe[soLuong].baggageWeight);
            while (getchar() != '\n');

            if (danhSachVe[soLuong].ticketClass == 3) {
                danhSachVe[soLuong].baggageFee = 0.0f;
            } else {
                if (danhSachVe[soLuong].baggageWeight <= 7.0f) {
                    danhSachVe[soLuong].baggageFee = 0.0f;
                } else {
                    danhSachVe[soLuong].baggageFee = (danhSachVe[soLuong].baggageWeight - 7.0f) * 50000.0f;
                }
            }

            soLuong++;
            printf("=> Them ve thanh cong! Cuoc phat hanh ly qua can: %.0f VNÐ.\n", danhSachVe[soLuong - 1].baggageFee);

        } else if (choice == 2) {
            if (soLuong == 0) {
                printf("Danh sach ve dang r?ng!\n");
                continue;
            }

            printf("\n========================================================================================\n");
            printf("%-5s | %-10s | %-25s | %-12s | %-12s | %-15s\n", "STT", "Mã PNR", "H? tên hành khách", "H?ng vé", "Hành lý (kg)", "Cu?c quá cu?c");
            printf("========================================================================================\n");

            for (int i = 0; i < soLuong; i++) {
                char className[15];
                if (danhSachVe[i].ticketClass == 1) sprintf(className, "Eco");
                else if (danhSachVe[i].ticketClass == 2) sprintf(className, "Deluxe");
                else sprintf(className, "Business");

                printf("%-5d | %-10s | %-25s | %-12s | %-12.1f | %.0f VNÐ\n",
                       i + 1,
                       danhSachVe[i].pnrCode,
                       danhSachVe[i].passengerName,
                       className,
                       danhSachVe[i].baggageWeight,
                       danhSachVe[i].baggageFee);
            }
            printf("========================================================================================\n");

        } else if (choice == 3) {
            if (soLuong == 0) {
                printf("Danh sach ve dang r?ng!\n");
                continue;
            }

            char pnrInput[15];
            printf("Nh?p mã PNR c?n c?p nh?t hành lý: ");
            fgets(pnrInput, sizeof(pnrInput), stdin);
            pnrInput[strcspn(pnrInput, "\n")] = '\0';

            int foundIndex = -1;
            for (int i = 0; i < soLuong; i++) {
                if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                    foundIndex = i;
                    break;
                }
            }

            if (foundIndex != -1) {
                printf("Tìm th?y hành khách: %s\n", danhSachVe[foundIndex].passengerName);
                printf("Nh?p tr?ng lu?ng hành lý m?i (kg): ");
                scanf("%f", &danhSachVe[foundIndex].baggageWeight);
                while (getchar() != '\n');

                if (danhSachVe[foundIndex].ticketClass == 3) {
                    danhSachVe[foundIndex].baggageFee = 0.0f;
                } else {
                    if (danhSachVe[foundIndex].baggageWeight <= 7.0f) {
                        danhSachVe[foundIndex].baggageFee = 0.0f;
                    } else {
                        danhSachVe[foundIndex].baggageFee = (danhSachVe[foundIndex].baggageWeight - 7.0f) * 50000.0f;
                    }
                }

                printf("=> C?p nh?t thành công! Phí hành lý quá cu?c m?i: %.0f VNÐ.\n", danhSachVe[foundIndex].baggageFee);
            } else {
                printf("Không tìm th?y vé có mã PNR dã nh?p!\n");
            }

        } else if (choice == 4) {
            if (soLuong == 0) {
                printf("Danh sach ve dang r?ng!\n");
                continue;
            }

            char pnrInput[15];
            printf("Nh?p mã PNR c?n xóa: ");
            fgets(pnrInput, sizeof(pnrInput), stdin);
            pnrInput[strcspn(pnrInput, "\n")] = '\0';

            int foundIndex = -1;
            for (int i = 0; i < soLuong; i++) {
                if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                    foundIndex = i;
                    break;
                }
            }

            if (foundIndex != -1) {
                for (int i = foundIndex; i < soLuong - 1; i++) {
                    danhSachVe[i] = danhSachVe[i + 1];
                }
                soLuong--;
                printf("=> Ðã xóa thành công vé có mã PNR: %s ra kh?i h? th?ng.\n", pnrInput);
            } else {
                printf("Không tìm th?y vé có mã PNR dã nh?p!\n");
            }

        } else if (choice == 5) {
            printf("C?m on b?n dã s? d?ng h? th?ng! T?m bi?t.\n");
            break;
        } else {
            printf("L?a ch?n không h?p l?! Vui lòng ch?n t? 1 d?n 5.\n");
        }

    } while (1);

    return 0;
}
