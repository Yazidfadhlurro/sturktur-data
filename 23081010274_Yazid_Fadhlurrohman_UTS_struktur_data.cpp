#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node {
    char nama[50];
    char jenisKelamin; 
    struct node* prev;
    struct node* next;
} node;

node* head = NULL; 
node* nyanyi = NULL; 


void tambah_mahasiswa(const char nama[], char jenisKelamin) {
    node* newnode = (node*)malloc(sizeof(node));
    strcpy(newnode->nama, nama);
    newnode->jenisKelamin = jenisKelamin;
    newnode->prev = newnode->next = NULL;

    if (head == NULL) {
        head = newnode;
        head->next = head;
        head->prev = head;
    } else {
        node* tail = head->prev;
        tail->next = newnode;
        newnode->prev = tail;
        newnode->next = head;
        head->prev = newnode;
    }

    if (nyanyi == NULL) {
        nyanyi = newnode;
    }
    node* temp = head;
    printf("lingkaran mahasiswa ");
    do{
    	printf(" %s -> ", temp->nama);
        temp = temp -> next;
		}
	while(temp != head);
}


void hapus_mahasiswa(const char nama[]) {
    if (head == NULL) {
        printf("Lingkaran kosong!\n");
        return;
    }
    node* temp = head;
    node* prevnode = NULL;
    do {
        if (strcmp(temp->nama, nama) == 0) {
            if (temp == head && temp->next == head) {
                free(head);
                head = NULL;
                nyanyi = NULL;
                return;
            }
            if (temp == head) {
                head = head->next;
            }
            
            node* prev = temp->prev;
            node* next = temp->next;
            prev->next = next;
            next->prev = prev;

            if (nyanyi == temp) {
                nyanyi = next;
            }

            free(temp);
            if (head != NULL) {
                node* current = head;
                printf("lingkaran mahasiswa: ");
                do {
                    printf("%s -> ", current->nama);
                    current = current->next;
                } while (current != head);
            }
            return;
        }
        temp = temp->next;
    } while (temp != head);

    printf("Mahasiswa %s tidak ditemukan!\n", nama);
}


void mahasiswa_nyanyi() {
    if (nyanyi != NULL) {
        printf("%s sedang bernyanyi.\n",nyanyi -> nama);
    } else {
        printf("Tidak ada yang bernyanyi.\n");
    }
}


void pindah_urutan_nyanyi() {
    if (nyanyi != NULL) {
        nyanyi = nyanyi -> next;
    }
    mahasiswa_nyanyi();
}


void pisah_lingkaran() {
    node* temp = head;
    printf("Lingkaran Mahasiswa:\n");
    do {
        if (temp->jenisKelamin == 'l') {
            printf("%s\n", temp->nama);
        }
        temp = temp->next;
    } while (temp != head);

    printf("\nLingkaran Mahasiswi:\n");
    temp = head;
    do {
        if (temp->jenisKelamin == 'p') {
            printf("%s\n", temp->nama);
        }
        temp = temp->next;
    } while (temp != head);
}


int main() {
    int pilihan;
    char nama[50];
    char jenisKelamin;

    while (1) {
        printf("\n ================== Menu ===================\n");
        printf("1. Tambah mahasiswa ke lingkaran\n");
        printf("2. Hapus mahasiswa dari lingkaran\n");
        printf("3. Lihat siapa yang sedang bernyanyi\n");
        printf("4. Pindah ke orang berikutnya untuk bernyanyi\n");
        printf("5. Pisahkan lingkaran berdasarkan jenis kelamin\n");
        printf("6. Keluar\n");
        printf("masukkan pilihan : ");
        scanf("%d", &pilihan);
        
        if(pilihan == 1){
        	printf("Masukkan nama: ");
            scanf("%s", nama);
            printf("Masukkan jenis kelamin (L/P): ");
            scanf(" %c", &jenisKelamin);
            
            if (strcmp(nama, "cindy") == 0) {
                if (head != NULL) {
                    node* tail = head->prev;
                    if (head->jenisKelamin == 'p' && tail->jenisKelamin == 'p') {
                        printf("Cindy bisa masuk karena sebelumnya perempuan.\n");
                        tambah_mahasiswa(nama, jenisKelamin);
                    } 
					else if (head->jenisKelamin == 'l' || tail->jenisKelamin == 'l') {
                        printf("Cindy keluar karena ada laki-laki di sebelahnya.\n");
                        hapus_mahasiswa("cindy");
                    }
                } 
				else {
                    tambah_mahasiswa(nama, jenisKelamin);
                }
            } else {
                tambah_mahasiswa(nama, jenisKelamin);
            }
		}
		else if(pilihan == 2){
			printf("Masukkan nama mahasiswa yang akan dihapus: ");
            scanf("%s", nama);
            hapus_mahasiswa(nama);
		}
		else if(pilihan == 3){
			mahasiswa_nyanyi();
		}
		else if(pilihan == 4){
			pindah_urutan_nyanyi();
		}
		else if (pilihan == 5){
			pisah_lingkaran();
		}
		else if(pilihan == 6){
			break;
		}
		else{
			printf("pilihan menu tidak ada ");
		}
	}
	return 0;
}
