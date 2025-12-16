#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX_ACCOUNTS 100

typedef struct {
    char name[30];
    char id[20];
    char pass[10];
    int balance=0;
    int locked;
    int failLogin=0;
    int loaigd=0;
    int lsgd=0;
    time_t time=0;
} Taikhoan;

void solanchay() {
    FILE *file;
    int runCount = 0;
    file = fopen("run_count.txt", "r+");
    if (file == NULL) {
        file = fopen("run_count.txt", "w+");
    }
    fscanf(file, "%d", &runCount);
    runCount++;
    rewind(file);
    fprintf(file, "%d", runCount);
    fclose(file);
    printf("chuong trinh da chay %d lan.\n", runCount);
}

void luutaikhoan(Taikhoan *taikhoan, int i) {
    FILE *file;
    file = fopen("Danhsachtaikhoan.txt", "a");
    if (file == NULL) {
        printf("Loi khi mo tep!");
        return;
    }
    fprintf(file, "%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%ld\n",
            taikhoan[i].name,
			taikhoan[i].id, 
			taikhoan[i].pass, 
			taikhoan[i].balance, 
			taikhoan[i].locked, 
			taikhoan[i].failLogin, 
			taikhoan[i].loaigd, 
			taikhoan[i].lsgd, 
			taikhoan[i].time);
    fclose(file);
}

void doctaikhoan(Taikhoan *danhsachtk, int *sotaikhoan) {
    FILE *file;
    file = fopen("Danhsachtaikhoan.txt", "r");
    if (file == NULL) {
        return;
    }
    while (fscanf(file, "%s %s %s %d %d %d %d %d %ld",
                danhsachtk[*sotaikhoan].name, 
				danhsachtk[*sotaikhoan].id, 
				danhsachtk[*sotaikhoan].pass,
                &danhsachtk[*sotaikhoan].balance, 
				&danhsachtk[*sotaikhoan].locked, 
				&danhsachtk[*sotaikhoan].failLogin,
                &danhsachtk[*sotaikhoan].loaigd, 
				&danhsachtk[*sotaikhoan].lsgd, 
				&danhsachtk[*sotaikhoan].time) != EOF) {
        (*sotaikhoan)++;
    }
    fclose(file);
}

void menu() {
	system("cls");
    printf("\n====== Menu ATM ======\n");
    printf("1. Xem so du\n");
    printf("2. Nap tien\n");
    printf("3. Rut tien\n");
    printf("4. Chuyen tien\n");
    printf("5. Lich su giao dich\n");
    printf("6. Dang xuat\n");
}

void inThoiGian(time_t epochTime) {
    char buffer[26];
    struct tm *timeinfo;
    timeinfo = localtime(&epochTime);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("%s", buffer);
}

void lichsugd(Taikhoan *taikhoan, Taikhoan danhsachtk[], int sotaikhoan) {
    printf("Lich su giao dich:\n");
    for (int i = 0; i <=sotaikhoan+10; i++) {
        if (strcmp(taikhoan->id, danhsachtk[i].id) == 0) {
            if (danhsachtk[i].loaigd == 2) {
                printf("- Nap tien: +%d VND\t\t\t\tThoi gian: ", danhsachtk[i].lsgd);
                inThoiGian(danhsachtk[i].time);
                printf("\n");
            } else if (danhsachtk[i].loaigd == 3) {
                printf("- Rut tien: -%d VND\t\t\t\tThoi gian: ", danhsachtk[i].lsgd);
                inThoiGian(danhsachtk[i].time);
                printf("\n");
            } else if (danhsachtk[i].loaigd == 4) {
                printf("- Chuyen tien: -%d VND\t\t\t\tThoi gian: ", danhsachtk[i].lsgd);
                inThoiGian(danhsachtk[i].time);
                printf("\n");
            } else if (danhsachtk[i].loaigd == 5) {
                printf("- Nhan tien tu nguoi khac: +%d VND\t\t\t\tThoi gian: ", danhsachtk[i].lsgd);
                inThoiGian(danhsachtk[i].time);
                printf("\n");
            } else if (danhsachtk[i].loaigd == 6) {
                printf("- Nap tien tu quan tri vien: +%d VND\t\tThoi gian: ", danhsachtk[i].lsgd);
                inThoiGian(danhsachtk[i].time);
                printf("\n");
            }
        }
    }
    getch();
}


void kiemtrasodu(Taikhoan *taikhoan, Taikhoan danhsachtk[], int sotaikhoan) {
    for (int i = sotaikhoan+5; i>=0; i--){
        if (strcmp(taikhoan->id, danhsachtk[i].id) == 0) {
            printf("So du cua ban la: %d VND\n", danhsachtk[i].balance);
			printf("Nhan phim bat ky de tiep tuc!");
			getch();    
            break;
        }
    }
}

void naptien(Taikhoan *taikhoan, Taikhoan danhsachtk[], int sotaikhoan) {
    int sotien;
    printf("Nhap so tien nap vao (VND): ");
    scanf("%d", &sotien);
    for (int i = sotaikhoan+5; i>=0; i--) {
        if (strcmp(taikhoan->id, danhsachtk[i].id) == 0) {
            danhsachtk[i].balance += sotien;
            danhsachtk[i].loaigd = 2;
            danhsachtk[i].lsgd = sotien;
            danhsachtk[i].time = time(NULL);
            luutaikhoan(danhsachtk, i);
            printf("Nap tien thanh cong! So du hien tai: %d VND\n", danhsachtk[i].balance);
            printf("Nhan phim bat ky de tiep tuc!");
			getch();   
            return;
        }
    }
}

void ruttien(Taikhoan *taikhoan, Taikhoan danhsachtk[], int sotaikhoan) {
    int sotien;
    printf("Nhap so tien can rut (VND): ");
    scanf("%d", &sotien);
    for (int i = sotaikhoan+5; i>=0; i--) {
        if (strcmp(taikhoan->id, danhsachtk[i].id) == 0) {
            if (sotien > danhsachtk[i].balance) {
                printf("So du khong du!\n");
                printf("Nhan phim bat ky de tiep tuc!");
				getch();    
                return;
            } else {
                danhsachtk[i].balance -= sotien;
                danhsachtk[i].loaigd = 3;
                danhsachtk[i].lsgd = sotien;
                danhsachtk[i].time = time(NULL);
                luutaikhoan(danhsachtk, i);
                printf("Rut tien thanh cong! So du hien tai: %d VND\n", danhsachtk[i].balance);
                printf("Nhan phim bat ky de tiep tuc!");
				getch();    
                return;
            }
        }
    }
}

void chuyentien(Taikhoan *taikhoan, Taikhoan danhsachtk[], int sotaikhoan) {
    char nguoinhan[20];
    int sotien;
    printf("Nhap so tai khoan nguoi nhan: ");
    scanf("%s", nguoinhan);
    for (int i = sotaikhoan+5; i >= 0; i--) {
        if (strcmp(taikhoan->id, danhsachtk[i].id) == 0) {
            for (int k = sotaikhoan+5; k >=0; k--) {
                if (strcmp(nguoinhan, danhsachtk[k].id) == 0) {
                    printf("Nhap so tien can chuyen (vnd):");
                    scanf("%d", &sotien);
                    if (sotien <= danhsachtk[i].balance) {
                        danhsachtk[k].balance += sotien;
                        danhsachtk[k].loaigd = 5;
                        danhsachtk[k].time = time(NULL);
                        danhsachtk[k].lsgd = sotien;
                        danhsachtk[i].balance -= sotien;
                        danhsachtk[i].loaigd = 4;
                        danhsachtk[i].lsgd = sotien;
                        danhsachtk[i].time = time(NULL);
                        printf("Ban da chuyen tien thanh cong den so tai khoan: %s !\nSo du hien tai cua ban la: %d vnd\nSo du cua nguoi nhan: +%d vnd",
                               danhsachtk[k].id, danhsachtk[i].balance, sotien);
                        luutaikhoan(taikhoan, k);
                        luutaikhoan(taikhoan, i);
                        printf("\nNhan phim bat ky de tiep tuc!");
						getch();    
                        return;
                    } else {
                        printf("So du khong du de thuc hien giao dich!\n");
                        printf("Nhan phim bat ky de tiep tuc!");
						getch();    
                        return;
                    }
                }
            }
        }
    }
    printf("Khong tim thay nguoi nhan\n");
    printf("Nhan phim bat ky de tiep tuc!");
	getch();    
}

void dangky(Taikhoan *danhsachtk, int *sotaikhoan) {
    printf("Nhap ho va ten: ");
    fgets(danhsachtk[*sotaikhoan].name, sizeof(danhsachtk[*sotaikhoan].name), stdin);
    char sotaikhoanmoi[10];
    printf("Nhap so tai khoan dang ky: ");
    scanf("%s", sotaikhoanmoi);
    for (int i = 0; i < *sotaikhoan; i++) {
        if (strcmp(sotaikhoanmoi, danhsachtk[i].id) == 0) {
            printf("Tao tai khoan khong thanh cong. So tai khoan da ton tai.\n");
            printf("Nhan phim bat ky de tiep tuc!");
			getch();    
            return;
        }
    }
    strcpy(danhsachtk[*sotaikhoan].id, sotaikhoanmoi);
    printf("Nhap mat khau dang ky: ");
    scanf("%s", danhsachtk[*sotaikhoan].pass);
    danhsachtk[*sotaikhoan].balance = 0;
    danhsachtk[*sotaikhoan].locked = 0;
    danhsachtk[*sotaikhoan].failLogin = 0;
    printf("Tai khoan da duoc dang ky thanh cong!\n");
    luutaikhoan(danhsachtk, *sotaikhoan);
    (*sotaikhoan)++;
	printf("Nhan phim bat ky de tiep tuc!");
	getch();    
}

void xoatk(Taikhoan *danhsachtk, int sotaikhoan) {
    char sotkxoa[20];
    printf("Nhap so tai khoan can xoa: ");
    scanf("%s", sotkxoa);
    for (int i = sotaikhoan+5; i>=0; i--) {
        if (strcmp(sotkxoa, danhsachtk[i].id) == 0) {
            for (int j = i; j < sotaikhoan - 1; j++) {
                strcpy(danhsachtk[j].name, danhsachtk[j + 1].name);
                strcpy(danhsachtk[j].id, danhsachtk[j + 1].id);
                strcpy(danhsachtk[j].pass, danhsachtk[j + 1].pass);
                danhsachtk[j].balance = danhsachtk[j + 1].balance;
                danhsachtk[j].locked = danhsachtk[j + 1].locked;
            }
            (sotaikhoan)--;
            printf("Tai khoan da duoc xoa thanh cong!\n");
            luutaikhoan(danhsachtk, sotaikhoan);
            printf("Nhan phim bat ky de tiep tuc!");
			getch();    
            return;
        }
    }
    printf("Khong tim thay tai khoan can xoa!\n");
    printf("Nhan phim bat ky de tiep tuc!");getch();    
	
}

void mokhoa(Taikhoan *danhsachtk, int sotaikhoan) {
    char sotkmokhoa[20];
    printf("Nhap so tai khoan can mo khoa: ");
    scanf("%s", sotkmokhoa);
    for (int i = sotaikhoan+5; i>=0; i--) {
        if (strcmp(sotkmokhoa, danhsachtk[i].id) == 0) {
            danhsachtk[i].locked = 0;
            printf("Tai khoan da duoc mo khoa!\n");
            luutaikhoan(danhsachtk, i);
            printf("Nhan phim bat ky de tiep tuc!");
			getch();    
            return;
        }
    }
    printf("Khong tim thay tai khoan can mo khoa!\n");
    printf("Nhan phim bat ky de tiep tuc!");getch();    
	
}

void khoatk(Taikhoan *danhsachtk, int sotaikhoan) {
    char sotkkhoa[20];
    printf("Nhap so tai khoan can khoa: ");
    scanf("%s", sotkkhoa);
    for (int i = sotaikhoan+5; i>=0; i--) {
        if (strcmp(sotkkhoa, danhsachtk[i].id) == 0) {
            danhsachtk[i].locked = 1;
            printf("Tai khoan da duoc khoa!\n");
            luutaikhoan(danhsachtk, i);
            printf("Nhan phim bat ky de tiep tuc!");
			getch();    
            return;
        }
    }
    printf("Khong tim thay tai khoan can khoa!\n");
}

void naptiennguoidung(Taikhoan *danhsachtk, int sotaikhoan) {
    char stknguoidung[20];
    int sotien = 0;
    printf("Nhap so tai khoan nguoi dung: ");
    scanf("%s", stknguoidung);
    getchar();
    for (int i = sotaikhoan+5; i>=0; i--) {
        if (strcmp(stknguoidung, danhsachtk[i].id) == 0) {
            printf("Nhap so tien can nap: ");
            scanf("%d", &sotien);
            danhsachtk[i].balance += sotien;
            danhsachtk[i].loaigd = 6;
            danhsachtk[i].lsgd = sotien;
            danhsachtk[i].time = time(NULL);
            printf("Nap tien thanh cong! So tai khoan %s: +%d vnd\n", stknguoidung, sotien);
            luutaikhoan(danhsachtk, i);
            printf("Nhan phim bat ky de tiep tuc!");
			getch();    
            return;
        }
    }
    printf("Khong tim thay so tai khoan\n");
    printf("Nhan phim bat ky de tiep tuc!");getch();    
}

/*
void doimatkhau(Taikhoan *danhsachtk , int sotaikhoan) {
    int sotien;
    char sotk[10];
    char matkhaumoi[10];
    printf("Nhap so tai khoan nguoi dung: ");
    scanf("%s", sotk);
    for (int i = sotaikhoan+5; i>=0; i--) {
        if (strcmp(sotk, danhsachtk[i].id) == 0) {
        	printf("Nhap mat khau moi: ");
        	scanf("%s",matkhaumoi);
            danhsachtk[i].pass = matkhaumoi;
            printf("Doi mat khau thanh cong! \n");
            printf("Nhan phim bat ky de tiep tuc!");
			getch();   
            return;
        }
    }
}
*/

void Admin(Taikhoan *danhsachtk, int sotaikhoan) {
    char PASS[10] = "admin123";
    char matkhau[10];
    printf("Nhap mat khau quan tri vien: ");
    scanf("%s", matkhau);
    getchar();
    if (strcmp(matkhau, PASS) == 0) {
        while (1) {
        	system("cls");
            printf("\n====== Menu ADMIN ======\n");
            printf("1. Dang ky tai khoan\n");
            printf("2. Xoa tai khoan\n");
            printf("3. Mo khoa tai khoan\n");
            printf("4. Khoa tai khoan\n");
            printf("5. Doi mat khau\n");
            printf("6. Nap tien cho nguoi dung\n");
            printf("7. Thoat\n");
            printf("Nhap lua chon cua ban: ");
            int aluachon;
            scanf("%d", &aluachon);
            fflush(stdin);
            switch (aluachon) {
                case 1:
                    dangky(danhsachtk, &sotaikhoan);
                    break;
                case 2:
                    xoatk(danhsachtk, sotaikhoan);
                    break;
                case 3:
                    mokhoa(danhsachtk, sotaikhoan);
                    break;
                case 4:
                    khoatk(danhsachtk, sotaikhoan);
                    break;
                case 5:
                	//doimatkhau(danhsachtk, sotaikhoan);
                	printf("Tinh nang dang duoc cap nhat, an nut bat ki de tiep tuc!"); 
                	getch();
                	break; 
                case 6:
                    naptiennguoidung(danhsachtk, sotaikhoan);
                    break;
                case 7:
                    printf("Thoat...\n");
                    return;
                default:
                    printf("Lua chon khong hop le! Vui long thu lai\n");
            }
        }
    }
    printf("Nhan phim bat ky de tiep tuc!");
	getch();    
}

void dangnhap(Taikhoan *danhsachtk, int sotaikhoan) {
	doctaikhoan(danhsachtk,&sotaikhoan);
    char sotkdangnhap[20];
    char matkhau[10];
    char admin[10] = "admin";

    printf("Nhap so tai khoan dang nhap: ");
    scanf("%s", sotkdangnhap);
    getchar(); // Consume newline

    if (strcmp(sotkdangnhap, admin) == 0) {
        Admin(danhsachtk, sotaikhoan);
        printf("Nhan phim bat ky de tiep tuc!");
        getchar();
        return;
    }

    printf("Nhap mat khau dang nhap: ");
    scanf("%s", matkhau);
    getchar(); // Consume newline

    for (int i = 0; i <= sotaikhoan+10; i++) {
        if (strcmp(sotkdangnhap, danhsachtk[i].id) == 0 && strcmp(matkhau, danhsachtk[i].pass) == 0) {
            if (danhsachtk[i].locked == 1) {
                printf("Tai khoan cua ban da bi khoa! Vui long lien he quan tri vien de duoc ho tro.\n");
                printf("Nhan phim bat ky de tiep tuc!");
                getchar();
            } else {
                printf("Dang nhap thanh cong!\n");
                printf("Nhan phim bat ky de tiep tuc!");
                getchar();

                int luachon;
                do {
                    menu();
                    printf("Nhap lua chon cua ban: ");
                    scanf("%d", &luachon);
                    fflush(stdin);
                    switch (luachon) {
                        case 1:
                            kiemtrasodu(&danhsachtk[i], danhsachtk, sotaikhoan);
                            break;
                        case 2:
                            naptien(&danhsachtk[i], danhsachtk, sotaikhoan);
                            break;
                        case 3:
                            ruttien(&danhsachtk[i], danhsachtk, sotaikhoan);
                            break;
                        case 4:
                            chuyentien(&danhsachtk[i], danhsachtk, sotaikhoan);
                            break;
                        case 5:
                            lichsugd(&danhsachtk[i], danhsachtk, sotaikhoan);
                            break;
                        case 6:
                            printf("Da dang xuat!\n");
                            return;
                        default:
                            printf("Lua chon khong hop le! Vui long lua chon lai\n");
                    }
                } while (1);
            }
            return;
        }
    }

    printf("Dang nhap that bai! So tai khoan hoac mat khau khong dung\n");
    for (int i = 0; i <= sotaikhoan+10; i++) {
        if (strcmp(sotkdangnhap, danhsachtk[i].id) == 0) {
            danhsachtk[i].failLogin++;
            if (danhsachtk[i].failLogin >= 3) {
                danhsachtk[i].locked = 1;
                printf("Tai khoan da bi khoa sau 3 lan dang nhap that bai.\n");
                printf("Nhan phim bat ky de tiep tuc!");
                getchar();
            }
            return;
        }
    }

    printf("Nhan phim bat ky de tiep tuc!");
    getchar();
}


int main() {
	solanchay();
	printf("Nhan phim bat ki de bat dau chuong trinh!");
	getch(); 
    int luachon;
    Taikhoan danhsachtk[MAX_ACCOUNTS];
    int sotaikhoan = 0;
    doctaikhoan(danhsachtk, &sotaikhoan);
    do {
    	system("cls");
        printf("\n====== Menu ATM ======\n");
        printf("1. Dang nhap\n");
        printf("2. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luachon);
        fflush(stdin);
        switch (luachon) {
            case 1:
                dangnhap(danhsachtk, sotaikhoan);
                break;
            case 2:
                printf("Thoat...\n");
                exit(0);
            default:
                printf("Lua chon khong hop le! Vui long thu lai\n");
        }
    } while (1);
    return 0;
}

