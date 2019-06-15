#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITE 9999


	char kelime[50];
	const char *ayrac= "-";


    int main()
{
    FILE * dosya;

	if ((dosya = fopen("sehir kod.txt", "r")) == NULL) {
		printf("Dosya acilamadi!\n");
		exit(1);
	}

    int satir=0;
    fseek(dosya, 10, SEEK_SET);                                     // ilk satiri okumamak icin

    while(fscanf(dosya,"%s",kelime)!=EOF){                          // sehir kod dosyasininn satir sayisi
    satir++;
}

    int x=0;
    int uzunluk2;
	int **sehirDizisi;
    char sehir[20];

	sehirDizisi = (int**)malloc(satir * sizeof(int**));             // dinamik olarak bellekten yer alir

    fseek(dosya, 10, SEEK_SET);

	while(fscanf(dosya,"%s",kelime)!=EOF)
    {

        char *sehir=strtok(kelime,ayrac);

        uzunluk2=strlen(sehir);
        sehirDizisi[x]=(char*)malloc(uzunluk2 * sizeof(char*));
        strcpy(sehirDizisi[x],sehir);
        x++;

	}

	fclose(dosya);


    FILE * dosya2;

	if ((dosya2 = fopen("sehir mesafe.txt", "r")) == NULL) {
		printf("Dosya acilamadi!\n");
		exit(1);
	}

	int satir2=0;
    fseek(dosya2, 21, SEEK_SET);                                    // ilk satiri okumamak icin

    while(fscanf(dosya2,"%s",kelime)!=EOF){                         // sehir mesafe dosyasinin satir sayisi
    satir2++;
}

    int i=0;
    int j=0;
    int k=0;
    int uzunluk;
    char **sehir_Adi1;
    char **sehir_Adi2;
    int **uzaklik;
    char sehir1[20];
    char sehir2[20];
    char mesafeDizisi[4];

	sehir_Adi1 = (char**)malloc(satir2 * sizeof(char**));           // dinamik olarak bellekten yer alir
	sehir_Adi2 = (char**)malloc(satir2 * sizeof(char**));
	uzaklik = (int**)malloc(satir2 * sizeof(int**));


    fseek(dosya2, 21, SEEK_SET);

    while(fscanf(dosya2,"%s",kelime)!=EOF)
    {

        char *sehir1=strtok(kelime,ayrac);

        uzunluk=strlen(sehir1);
        sehir_Adi1[i]=(char*)malloc(uzunluk * sizeof(char*));
        strcpy(sehir_Adi1[i],sehir1);
        i++;

        char *sehir2=strtok(NULL,ayrac);

        uzunluk=strlen(sehir2);
        sehir_Adi2[j]=(char*)malloc(uzunluk * sizeof(char*));
        strcpy(sehir_Adi2[j],sehir2);
        j++;

        char *mesafeDizisi=strtok(NULL,"\n");

        uzunluk=strlen(mesafeDizisi);
        uzaklik[k]=(int*)malloc(uzunluk * sizeof(int*));
        strcpy(uzaklik[k],mesafeDizisi);
        k++;

	}

    fclose(dosya2);


// Komsuluk matrisini olustur

    int **komsulukMatrisi;
    int i1,i2;

    komsulukMatrisi = (int**)malloc(satir*sizeof(int**));

    for(i=0;i<satir;i++)
    {
        komsulukMatrisi[i]=(int*)malloc(satir*sizeof(int*));
    }


    for(i=0;i<satir;i++)
    {
        for(j=0;j<satir;j++)
        {
            komsulukMatrisi[i][j]=INFINITE;
        }

        komsulukMatrisi[i][i]=0;
    }

    for(i=0;i<satir2;i++)
    {
        for(j=0;j<satir;j++)
        {
            int sonuc=strcmp(sehir_Adi1[i],sehirDizisi[j]);

                if(sonuc==0)
                    {
                        i1=j;
                    }

            int sonuc2=strcmp(sehir_Adi2[i],sehirDizisi[j]);

                if(sonuc2==0)
                    {
                        i2=j;
                    }

        }
            komsulukMatrisi[i1][i2]=atoi(uzaklik[i]);
            komsulukMatrisi[i2][i1]=atoi(uzaklik[i]);
    }


    char ch;

    printf("Bir sehirden diger sehirlere olan en kisa mesafeyi bulmak icin 1'e basiniz:\n\n");
    printf("Girilen iki sehir arasindaki en kisa mesafeyi bulmak icin 2'ye basiniz:\n\n");
    scanf("%c",&ch);

    if(ch=='1')
    {
        char dizi[20];
        int s;
        int p;

        printf("\nSehir giriniz: ");
        scanf("%s",&dizi);

        for(p=0;p<satir;p++)
        {
            int cevap=strcmp(dizi,sehirDizisi[p]);

                if(cevap==0)
                    {
                        s=p;
                    }

        }

        dijkstra(komsulukMatrisi,satir,s,satir,sehirDizisi);
    }

    if (ch=='2')
    {
        char basDizi[20];
        char sonDizi[20];
        int bas,son;
        int n,m;


        printf("\nBaslangic sehri giriniz: ");
        scanf("%s", &basDizi);
        printf("\nGitmek istediginiz sehri giriniz: ");
        scanf("%s", &sonDizi);

        for(n=0;n<satir;n++)
        {
            for(m=0;m<satir;m++)
            {
                int cevap1=strcmp(basDizi,sehirDizisi[n]);
                int cevap2=strcmp(sonDizi,sehirDizisi[m]);

                if(cevap1==0&&cevap2==0)
                    {
                        bas=n;
                        son=m;
                    }

            }
        }

        dijkstra2(komsulukMatrisi,satir,son,bas,satir,sehirDizisi);     // Yolun ters yazdirilmamasi icin fonksiyona once varis
                                                                        // sonra baslangic degeri yollandi

    }

    return 0;
}


// Dijkstra algoritmasi kaynak

// http://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html

   void dijkstra(int **komsulukMatrisi,int boyut,int baslangic,int satir,int **sehirDizisi)
{
    int **maliyet;
    int *mesafe;
    int *onceki;
    int *visited;
    int sayac,enKisaMesafe,sonrakiDugum,i,j;

    maliyet = (int**)malloc(satir * sizeof(int**));

    for(i=0;i<satir;i++)
    {
        maliyet[i] = (int*)malloc(satir*sizeof(int));
    }

    mesafe =(int*)malloc(satir * sizeof(int*));
    onceki = (int*)malloc(satir * sizeof(int*));
    visited =(int*)malloc(satir * sizeof(int*));

    for(i=0;i<boyut;i++)
        for(j=0;j<boyut;j++)
            if(komsulukMatrisi[i][j]==0)
                maliyet[i][j]=INFINITE;
            else
                maliyet[i][j]=komsulukMatrisi[i][j];

    for(i=0;i<boyut;i++)
    {
        mesafe[i]=maliyet[baslangic][i];
        onceki[i]=baslangic;
        visited[i]=0;
    }

    mesafe[baslangic]=0;
    visited[baslangic]=1;
    sayac=1;

    while(sayac<boyut-1)
    {
        enKisaMesafe=INFINITE;

        for(i=0;i<boyut;i++)
            if(mesafe[i]<enKisaMesafe&&!visited[i])
            {
                enKisaMesafe=mesafe[i];
                sonrakiDugum=i;
            }

            visited[sonrakiDugum]=1;
            for(i=0;i<boyut;i++)
                if(!visited[i])
                    if(enKisaMesafe+maliyet[sonrakiDugum][i]<mesafe[i])
                    {
                        mesafe[i]=enKisaMesafe+maliyet[sonrakiDugum][i];
                        onceki[i]=sonrakiDugum;
                    }
        sayac++;
    }

    for(i=0;i<boyut;i++)
        if(i!=baslangic)
        {
            printf("\n%s ile %s arasi en kisa mesafe = %d km",sehirDizisi[i],sehirDizisi[baslangic],mesafe[i]);
            printf("\nYol = %s",sehirDizisi[i]);

            j=i;

            do
            {
                j=onceki[j];
                printf(" - %s",sehirDizisi[j]);
            }while(j!=baslangic);

            printf("\n");
        }
}



   void dijkstra2(int **komsulukMatrisi,int boyut,int baslangic,int varis,int satir, int **sehirDizisi)
{
    int **maliyet;
    int *mesafe;
    int *onceki;
    int *visited;
    int sayac,enKisaMesafe,sonrakiDugum,i,j;

    maliyet = (int**)malloc(satir * sizeof(int**));

    for(i=0;i<satir;i++)
    {
        maliyet[i] = (int*)malloc(satir*sizeof(int));
    }

    mesafe =(int*)malloc(satir * sizeof(int*));
    onceki = (int*)malloc(satir * sizeof(int*));
    visited =(int*)malloc(satir * sizeof(int*));

    for(i=0;i<boyut;i++)
        for(j=0;j<boyut;j++)
            if(komsulukMatrisi[i][j]==0)
                maliyet[i][j]=INFINITE;
            else
                maliyet[i][j]=komsulukMatrisi[i][j];

    for(i=0;i<boyut;i++)
    {
        mesafe[i]=maliyet[baslangic][i];
        onceki[i]=baslangic;
        visited[i]=0;
    }

    mesafe[baslangic]=0;
    visited[baslangic]=1;
    sayac=1;

    while(sayac<boyut-1)
    {
        enKisaMesafe=INFINITE;

        for(i=0;i<boyut;i++)
            if(mesafe[i]<enKisaMesafe&&!visited[i])
            {
                enKisaMesafe=mesafe[i];
                sonrakiDugum=i;
            }

            visited[sonrakiDugum]=1;
            for(i=0;i<boyut;i++)
                if(!visited[i])
                    if(enKisaMesafe+maliyet[sonrakiDugum][i]<mesafe[i])
                    {
                        mesafe[i]=enKisaMesafe+maliyet[sonrakiDugum][i];
                        onceki[i]=sonrakiDugum;
                    }
        sayac++;
    }

    for(i=0;i<boyut;i++)
        if(i!=baslangic && i==varis)
        {
            printf("\n%s ile %s arasi en kisa mesafe = %d km",sehirDizisi[i],sehirDizisi[baslangic],mesafe[i]);
            printf("\nYol = %s",sehirDizisi[i]);

            j=i;

            do
            {
                j=onceki[j];
                printf(" - %s",sehirDizisi[j]);
            }while(j!=baslangic);

            printf("\n");
        }
}

