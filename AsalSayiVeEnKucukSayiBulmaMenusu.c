#include <stdio.h>
#include <stdlib.h>

void menu()
{
    printf("1 - Asal sayi bulma\n2 - En kucuk sayi bulma\n3 - Cikis\n---------------------\n");
}

void AsalSayiBulma()
{
    int baslangic, bitis;
    printf("---------------------\nASAL SAYI BULMA\nBaslangic ve bitis degerlerini giriniz: ");
    scanf("%d %d", &baslangic, &bitis);


    if(bitis>1)
    {
        printf("Aralikta bulunan asal sayilar: ");
        for(int i=baslangic ; i<bitis ; i++)
        {
            for(int j=2 ; j<i ; j++)
            {
                if(i%j == 0)
                    continue;

                else
                    printf("%d", i);
            }

        }
        printf("\n\n");
    }

    else
        printf("Bu aralikta asal sayi yoktur..\n\n");

}
void EnKucukSayiBulma()
{
    int s1, s2, s3, enkucuk;
    printf("---------------------\nEN KUCUK SAYI BULMA:\n");
    printf("3 adet sayi giriniz: ");
    scanf("%d %d %d", &s1, &s2, &s3);

    enkucuk = s1;

    if(enkucuk>s2)
        enkucuk = s2;

    if(enkucuk> s3)
        enkucuk = s3;

    printf("Girilen sayilardan en kucuk olani: %d\n\n", enkucuk);
}

int main()
{
    int secim;
    do
    {
        do
        {
            menu();
            printf("Seciniz: ");
            scanf("%d", &secim);

            if(secim>3 || secim<1)
            {
                printf("Hatali Giris..\n---------------------\n");
            }
        }
        while(secim>3 || secim<1);

        switch(secim)
        {
            case 1: AsalSayiBulma(); break;

            case 2: EnKucukSayiBulma(); break;

            case 3: printf("Cikis Yapildi.."); break;

        }
    }
    while(secim != 3);

    return 0;
}
