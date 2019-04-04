#include <stdio.h>
#include <stdlib.h>

void menu()
{
    printf("1 - Oyuna basla --> (1)\n2 - Oyunu Bitir --> (-1)\n---------------------\n");
    printf("Seciminizi giriniz: ");
}
void OyunaBasla()
{
    int tahmin;
    int sayi = 12;
    printf("\n..OYUN BASLATILDI..\n");
    printf("Sayiyi tahmin ediniz: ");

    do
    {
        scanf("%d", &tahmin);
        if(tahmin > sayi)
            printf("Daha kucuk bir sayi giriniz: ");
        else if(tahmin < sayi)
            printf("Daha buyuk bir sayi giriniz: ");
        else
            printf("\nTEBRIKLER!! Sayiyi dogru tahmin ettiniz..\n---------------------\n");
    }
    while(tahmin != sayi);

}

int main()
{
    int secim;
    do
    {
        menu();
        scanf("%d", &secim);

        switch(secim)
        {
            case 1: OyunaBasla(); break;

            case -1: printf("\nOyun Bitirildi.."); break;

            default: printf("Hatali Giris..\n\n");
        }

    }
    while(secim != -1);

    return 0;
}
