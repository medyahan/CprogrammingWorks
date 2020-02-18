#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <math.h>

typedef struct T_Esya {
    int kontrol;           /// Silinecek elemanlari isaretlemek icin kontrol degiskeni belirliyoru. Silinecekse 0, silinmeyecekse 1 deðeri verilir
    char esya_ismi [50];
    char esya_sahibi[50];
    char esya_turu[50];
    int esya_ID;
} Esya;

void menu()
{
    system("cls");
    printf("***********************************\n IKINCI EL ESYA ALIM-SATIM SISTEMI \n***********************************\n\n");
    printf(" 1) Kayit Ekle\n");
    printf(" 2) Kayit Sil\n");
    printf(" 3) Kayit Guncelle\n");
    printf(" 4) Kayit Ara\n");
    printf(" 5) Tum Kayitlari Yazdir\n\n");
    printf(" 0) Sistemi Sonlandir\n\n");
    printf("***********************************\n\n");
    printf(" >> Seciminizi yapiniz: ");
}

void kayitEkle(Esya esya)
{
    FILE *dosya = fopen("kayitlar.txt", "a+");
    FILE *gecici = fopen("gecici1.txt", "a+");

    if(dosya == NULL)
    {
        puts("DOSYA ACILAMADI.. !!\n");
        exit(1);
    }

    int sayac = 0;
    int bulundu = 0;
    int var = 0;
    int i, j;
    int arama[50];
    int silinecek;

    while(!feof(dosya))             /// Dosyadaki silinecek olarak isaretlenen kayitlarin sayisini buluyoruz
    {
        fscanf(dosya, "%s %s %s %d %d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, &esya.esya_ID, &esya.kontrol);
        if(esya.kontrol == 0)
            sayac++;
    }

    rewind(dosya);                  /// Dosya imlecini tekrardan basa aliyoruz

    i = 0;
    while(!feof(dosya))             /// Dosyadaki kayitlarin ID'sini arama adli diziye elman olarak atiyoruz
    {                               /// Amacimiz ekledigimiz ID'nin dosyada bulunup bulunmadigini kontrol etmek
        fscanf(dosya, "%s %s %s %d %d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, &esya.esya_ID, &esya.kontrol);
        arama[i] = esya.esya_ID;
        i+=1;
    }

    rewind(dosya);                   /// Dosya imlecini tekrardan basa aliyoruz

    printf("\n YENI KAYIT:\n------------------------\n");

    if(sayac == 0)                   /// Erisim listemiz bossa dosya sonuna ekleme islemleri yapilir
    {
        fflush(stdin);
        printf(" Esya Ismi   : ");
        gets(esya.esya_ismi);
        printf(" Esya Sahibi : ");
        gets(esya.esya_sahibi);
        printf(" Esya Turu   : ");
        gets(esya.esya_turu);
        printf(" Esya ID     : ");
        scanf("%d", &esya.esya_ID);
        printf("\n");

        for(i=0 ; i<50 ; i++)       /// Kullanicidan aldigimiz ID'nin dosyada olup olmadigini arama dizisi uzerinden kontrol ediyoruz
        {
            if(arama[i] == esya.esya_ID)
            {
                var = 1;
                break;
            }
        }

        if(var == 0)
        {
            fprintf(dosya, "%25s\t%25s\t%25s\t%6d\t%6d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, esya.esya_ID, 1);
            /// Dosyanin sonuna kontrolu 1 yaparak yaziyoruz
            puts("\n KAYIT BASARIYLA EKLENDI..");
        }
        else
            puts(" KAYIT EKLENEMEDI..\n Girilen ID'ye sahip baska bir kayit bulunmaktadir..\n");

        fclose(dosya);
        fclose(gecici);
        remove("gecici1.txt");
    }
    else                        /// Erisim listesi dolu ise
    {
        while(!feof(dosya))     /// Dosya sonuna gelmedigi surece dosyadan kontrolu 0 olan ilk kaydin üzerine yeni kayit eklenir
        {
            fscanf(dosya, "%s %s %s %d %d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, &esya.esya_ID, &esya.kontrol);

            if(esya.kontrol == 0 && bulundu == 0)      /// Kontrolu 0 olan kayit bulunur
            {
                silinecek = esya.esya_ID;

                fflush(stdin);
                printf(" Esya Ismi   : ");
                gets(esya.esya_ismi);
                printf(" Esya Sahibi : ");
                gets(esya.esya_sahibi);
                printf(" Esya Turu   : ");
                gets(esya.esya_turu);
                printf(" Esya ID     : ");
                scanf("%d", &esya.esya_ID);
                printf("\n");

                for(j=0 ; j<50 ; j++)              /// Kullanicidan aldigimiz ID arama adli dizinin icinde var ise var adli degiskene 1 atiyoruz
                {
                    if(arama[j] == esya.esya_ID)
                    {
                        var = 1;
                        break;
                    }
                }

                fprintf(gecici, "%25s\t%25s\t%25s\t%6d\t%6d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, esya.esya_ID, 1);
                /// Kontrolu 1 yaparak yeni kaydi gecici dosyaya yaziyorux

                bulundu = 1;                      /// Silinen elemanin üzerine yazma isleminin yapildigini belirtmek için

            }
            else
                fprintf(gecici, "%25s\t%25s\t%25s\t%6d\t%6d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, esya.esya_ID, esya.kontrol);
                /// Dosyada kontrolu 0 olan ilk kayit haricindekileri gecici dosyaya yaziyoruz
        }
        fclose(dosya);
        fclose(gecici);

        if(var == 0 && bulundu == 1)                /// Eklenecek id dosyada mevcut degilse ve silinecek uzerine yazma islemi yapildiysa
        {
            erisimdenSil(silinecek);                /// Bulunan kaydin ID'sini fonksiyona gonderip erisim listesinden siliyoruz
            remove("kayitlar.txt");                 /// kayitlar.txt dosyasi silinir
            rename("gecici1.txt","kayitlar.txt");   /// gecici1.txt adli dosyanin ismi kayitler.txt olarak degistirilir
            puts("\n KAYIT BASARIYLA EKLENDI..");
        }
        else                                        /// Eklenecek id dosyada mevcutsa ekleme islemi yapilmaz
        {
            remove("gecici1.txt");
            puts(" KAYIT EKLENEMEDI..\n Girilen ID'ye sahip baska bir kayit bulunmaktadir..\n");
        }
    }

    fflush(stdin);
    getch();
}

void kayitSil(Esya esya)
{
    int id;
    int bulundu = 0;

    printf("\n >> Silinecek kaydin ID'sini giriniz : ");
    scanf("%d",&id);

    FILE *dosya = fopen("kayitlar.txt","a+");
    FILE *gecici = fopen("gecici1.txt","w");
    FILE *erisim = fopen("erisimliste.txt","a+");

    if(dosya == NULL)
    {
        puts("DOSYA ACILAMADI.. !!\n");
        exit(1);
    }

    while(!feof(dosya))                         /// Silinecek id'yi aramak icin dosya sonuna gelene kadar asagidaki islemleri yapiyoruz
    {
        fscanf(dosya, "%s %s %s %d %d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, &esya.esya_ID, &esya.kontrol);

        if(id == esya.esya_ID)                  /// Eger girilen id dosyada okunan kaydin ID'sine esit ise
        {
            fprintf(erisim, "%d\n", id);        /// id'yi erisim listesine silinecek olarak yaziyoruz

            fprintf(gecici, "%25s\t%25s\t%25s\t%6d\t%6d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, esya.esya_ID, 0);
            /// Kaydin kontrolunu 0 yaparak gecici dosyaya yaziyoruz

            bulundu = 1;                        /// Kayit bulundu, silinecek olarak isaretlendi
        }
        else                                    /// Girilen id dosyada okunan kaydin ID'sine esit deðil ise gecici dosyaya yaziyoruz
            fprintf(gecici, "%25s\t%25s\t%25s\t%6d\t%6d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, esya.esya_ID, esya.kontrol);
    }

    fclose(dosya);
    fclose(gecici);
    fclose(erisim);

    if(bulundu == 1)                           /// Silinecek kayit bulunduysa
    {
        remove("kayitlar.txt");                /// kayitlar.txt dosyasi silinir
        rename("gecici1.txt","kayitlar.txt");  /// gecici1.txt adli dosyanin ismi kayitler.txt olarak degistirilir
        puts("\nKAYIT SILINDI...");
    }

    else                                       /// Kayit bulunamadiysa actiðimiz gecici1.txt dosyasini siliyoruz
    {
        remove("gecici1.txt");
        puts("\nKAYIT BULUNAMADI...");
    }

    fflush(stdin);
    getch();
}

void kayitGuncelle(Esya esya)
{
    int id;
    int bulundu = 0;

    printf("\n >> Guncellenecek kaydin ID'sini giriniz: ");
    scanf("%d",&id);

    FILE *dosya = fopen("kayitlar.txt","a+");
    FILE *gecici = fopen("gecici1.txt","w");

    if(dosya == NULL)
    {
        puts("DOSYA ACILAMADI.. !!\n");
        exit(1);
    }

    while(!feof(dosya))
    {
        fscanf(dosya, "%s %s %s %d %d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, &esya.esya_ID, &esya.kontrol);
        if(id != esya.esya_ID)      /// Kullanicinin girdigi id dosyamizdaki kaydin ID'sine esit degilse kayit gecici dosyaya yazilir
        {
            fprintf(gecici, "%25s\t%25s\t%25s\t%6d\t%6d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, esya.esya_ID, esya.kontrol);
        }
        else                        /// Kullanicinin girdigi id dosyamizdaki kaydin ID'sine eþit ise guncelleme islemi gerceklestirilir
        {
            if(esya.kontrol == 1)   /// Silenecek olarak isaretledigimiz kaydi guncelleyemeyecegimiz icin kontrolun 1 olup olmadigi kontrol edilir
            {
                fflush(stdin);
                printf("Esya Ismi   : ");
                gets(esya.esya_ismi);
                printf("Esya Sahibi : ");
                gets(esya.esya_sahibi);
                printf("Esya Turu   : ");
                gets(esya.esya_turu);
                printf("Esya ID     : ");
                scanf("%d", &esya.esya_ID);
                printf("\n");

                fprintf(gecici, "%25s\t%25s\t%25s\t%6d\t%6d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, esya.esya_ID, esya.kontrol);
                                    /// Guncellenen kayit gecici dosyaya yazilir

                bulundu = 1;        /// Kayit bulundu, guncelleme yapildi
            }
        }
    }

    fclose(dosya);
    fclose(gecici);

    if(bulundu == 1)                            /// Guncelleme yapildiysa
    {
        remove("kayitlar.txt");                 /// kayitlar.txt dosyasi silinir
        rename("gecici1.txt","kayitlar.txt");   /// gecici1.txt adli dosyanin ismi kayitler.txt olarak degistirilir
        puts("\nKAYIT GUNCELLENDI...");
    }
    else                                        /// Guncellenecek kayit dosyanin icinde yoksa gecici1.txt dosyasi silinir
    {
        remove("gecici1.txt");
        puts("KAYIT BULUNAMADI...");
    }

    fflush(stdin);
    getch();
}

void kayitAra(Esya esya)
{
    int id;
    int bulundu = 0;

    printf("\n >> Aranacak Kaydin ID'sini giriniz: ");
    scanf("%d", &id);
    printf("\n");

    FILE *dosya = fopen("kayitlar.txt","a+");

    if(dosya == NULL)
    {
        puts("DOSYA ACILAMADI.. !!\n");
        exit(1);
    }

    while(!feof(dosya))               /// Dosya sonuna kadar okunur. Eger aranan id dosyadan okudugumuz ID'ye esit ise ekrana yazdirilir
    {
        fscanf(dosya, "%s %s %s %d %d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, &esya.esya_ID, &esya.kontrol);
        if(id == esya.esya_ID)
        {
            printf(" >>%25s %25s %25s %6d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, esya.esya_ID);

            bulundu = 1;              /// Aranan kayit bulundu
        }
    }

    fclose(dosya);

    if(bulundu == 0)                  /// Aranan kayit bulunamadiysa
    {
        puts("KAYIT BULUNAMADI..\n");
    }

    getch();
}

void kayitlariYazdir(Esya esya)
{
    FILE *dosya = fopen("kayitlar.txt", "a+");

    if(dosya == NULL)
    {
        printf("DOSYA ACILAMADI.. !!\n");
        exit(1);
    }

    int sayac = 1;       /// Kayitlari sira numarasi ile yazmak icin sayac adli degisken tanimliyoruz

    printf(" SIRA NO \t   ESYA ISMI \t\t   ESYA SAHIBI \t\t       ESYA TURU     ID      KONTROL");
    printf("\n---------------------------------------------------------------------------------------------------------\n");

    while(!feof(dosya))  /// Dosyanin sonuna gelmedigi surece kayitlari dosyadan cekip ekrana yazar
    {
        fflush(stdout);
        fscanf(dosya, "%s %s %s %d %d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, &esya.esya_ID, &esya.kontrol);
        printf(" %d-%25s %25s %25s %6d %6d\n", sayac, esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, esya.esya_ID, esya.kontrol);
        sayac++;
    }

    fclose(dosya);

    printf("\n\nKAYITLAR LISTELENDI..");
    getch();
}

void dosyadanOku(Esya esya)                      /// Kayitlarin tutuldugu dosyayi okuyoruz
{
    FILE *dosya = fopen("kayitlar.txt", "a+");

    if(dosya == NULL)
    {
        printf("DOSYA ACILAMADI.. !!\n");
        exit(1);
    }

    for(int i=0 ; i<50 ; i++)
    {
        fscanf(dosya, "%s %s %s %d %d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, &esya.esya_ID, &esya.kontrol);

        if(feof(dosya))
            break;
    }
    fclose(dosya);
}

void erisimdenSil(int silinecek)
{
    FILE *erisimliste = fopen("erisimliste.txt", "r");
    FILE *gecicierisim = fopen("gecici2.txt", "w");

    int id;

    do                                         /// Erisim listesinin sonuna kadar okunur. Silinecek adli deger okunan id'ye esit oldugunda..
    {
        fscanf(erisimliste,"%d\n", &id);       /// ..onu atlayip geri kalanlari gecici dosyayay yaziyoruz

        if(silinecek != id)
            fprintf(gecicierisim,"%d\n", id);

    }while(!feof(erisimliste));

    fclose(erisimliste);
    fclose(gecicierisim);

    remove("erisimliste.txt");                  /// erisimliste.txt dosyasi silinir
    rename("gecici2.txt","erisimliste.txt");    /// gecici2.txt adli dosyanin ismi erisimliste.txt olarak degistirilir

    fflush(stdin);
}

void erisimOku()                                /// Silineceklerin id'sinin tutuldugu erisim listesini okuyoruz
{
    FILE *erisim = fopen("erisimliste.txt", "a+");

    if(erisim == NULL)
    {
        printf("ERISIM LISTESI ACILAMADI.. !!\n");
        exit(1);
    }

    int i, id;
    for(i=0 ; i<50 ; i++)
    {
        fscanf(erisim, "%d\n", &id);

        if(feof(erisim))
            break;
    }

    fclose(erisim);
}

void sonHal(Esya esya)                          /// Program sonlandiginda dosyayi compact hale getirir
{
    FILE *dosya = fopen("kayitlar.txt", "a+");
    FILE *gecici = fopen("gecici2.txt", "a+");

    do
    {
        fscanf(dosya, "%s %s %s %d %d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, &esya.esya_ID, &esya.kontrol);

        fprintf(gecici, "%25s\t%25s\t%25s\t%6d\n", esya.esya_ismi, esya.esya_sahibi, esya.esya_turu, esya.esya_ID);

    }while(!feof(dosya));

    fclose(dosya);
    fclose(gecici);

    remove("kayitlar.txt");                       /// kayitlar.txt dosyasi silinir
    rename("gecici2.txt","kayitlar.txt");         /// gecici2.txt adli dosyanin ismi kayitlar.txt olarak degistirilir

    fflush(stdin);
}

int main()
{
    int secim;
    int devam = 1;

    Esya esya;

    dosyadanOku(esya);
    erisimOku();

    while(devam == 1)                         /// Cikis yapilmadigi surece asagidaki islemler yapilir
    {
        menu();                               /// Ekranda secim yapacaklarimizi gormek adina menu acilir
        scanf("%d", &secim);

        switch(secim)
        {
            case 1:
                system("cls");
                kayitEkle(esya);               /// Kayit ekleme islemi
                break;
            case 2:
                system("cls");
                kayitSil(esya);                /// Kayit silme islemi
                break;
            case 3:
                system("cls");
                kayitGuncelle(esya);           /// Kayit guncelleme islemi
                break;
            case 4:
                system("cls");
                kayitAra(esya);                /// Kayit arama islemi
                break;
            case 5:
                system("cls");
                kayitlariYazdir(esya);         /// Tum Kayitlari konsola yazdirma islemi
                break;
            case 0:
                system("cls");
                devam = 0;
                sonHal(esya);
                printf("\nSistemden cikmak icin bir tusa basiniz..");   /// Programdan cikma islemi
                break;
            default:
                printf("YANLIS SECIM YAPTINIZ!\n");
        }
        getch();
    }

    return 0;
}
