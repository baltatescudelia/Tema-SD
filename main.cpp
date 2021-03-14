#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <chrono>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;
int v[1000000],n,ok,i,x[1000000],m, fr[1000000];

void bubblesort(int v[100000000], int n)
{
    int ok=0,aux;
    while(ok==0)
    {
        ok=1;
        for(i=0;i<n-1;i++)
        {
            if(v[i]>v[i+1])
            {
                aux=v[i];
                v[i]=v[i+1];
                v[i+1]=aux;
                ok=0;

            }
        }
    }

}

int pivot(int v[],int st,int dr)
{
    int x,p,q;
    x=v[st];
    p=st;
    q=dr;
    while(p<q)
    {
        while(p<q&&v[q]>=x)
        {
            q--;
        }
        v[p]=v[q];
        while(p<q&&v[p]<=x)
        {
            p++;
        }
        v[q]=v[p];
    }
    v[p]=x;
    return p;
}
int quicksort(int v[],int st,int dr)
{
    int m;
    if(st<dr)
    {
        m=pivot(v,st,dr);
        quicksort(v,st,m-1);
        quicksort(v,m+1,dr);
    }
}

void interclasare(int v[],int st,int dr)
{
    int i,j,k,w[100005],m;
    m=(st+dr)/2;
    i=st;
    j=m+1;
    k=st-1;
    while(i<=m && j<=dr)
    {
        if(v[i]<v[j]) w[++k]=v[i++];
        else w[++k]=v[j++];
    }
    while(i<=m)
    {
        w[++k]=v[i++];
    }
    while(j<=dr)
    {
        w[++k]=v[j++];
    }
    for(i=st;i<=dr;i++)
    {
        v[i]=w[i];
    }
}
void mergesort(int v[],int st,int dr)
{
    int m;
    if(st<dr)
    {
        m=(st+dr)/2;
        mergesort(v,st,m);
        mergesort(v,m+1,dr);
        interclasare(v,st,dr);
    }
}
void countSort(int v[], int n) {

  int fr[10];
  int count_v[10];
  int max = v[0];

  for (int i = 1; i < n; i++) {
    if (v[i] > max)
      max = v[i];
  }

  for (int i = 0; i <= max; ++i) {
    count_v[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    count_v[v[i]]++;
  }

  for (int i = 1; i <= max; i++) {
    count_v[i] += count_v[i - 1];
  }


  for (int i = n - 1; i >= 0; i--) {
    fr[count_v[v[i]] - 1] = v[i];
    count_v[v[i]]--;
  }

  for (int i = 0; i < n; i++)
    {
    v[i] = fr[i];
  }
}
int getMax(int v[], int n)
{
  int max = v[0];
  for ( i = 1; i < n; i++)
    if (v[i] > max)
      max = v[i];
  return max;
}
void countingSort(int v[], int n, int p)
{
  const int max = 10;
  int out[n];
  int count[n];

  for ( i = 0; i < max; ++i)
    count[i] = 0;

  // calculam numarul de elemente
  for ( i = 0; i < n; i++)
    count[(v[i] / p) % 10]++;

  for (i = 1; i < max; i++)
    count[i] += count[i - 1];

  // plasam elementele in ordine crescatoare
  for ( i = n - 1; i >= 0; i--) {
    out[count[(v[i] / p) % 10] - 1] = v[i];
    count[(v[i] / p) % 10]--;
  }

  for ( i = 0; i < n; i++)
    v[i] = out[i];
}
void radixsort(int v[], int n)
{
   //calculam elementul maxim din vetor
    int maxim = getMax(v, n);


  //aplicam countingSort pentru a sorta elementele in functie de pozitia valorii(x)
  for (int p = 1; maxim / p > 0; p *= 10)
    countingSort(v, n, p);
}

int main()
{
    int maxi;
    //Citirea
   cout<< "n=";
   cin >> n;
   cout<<"maxi=";
   cin>>maxi;


    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, maxi);

    for ( i=0; i<n; ++i)
        v[i]= distrib(gen);
        //facem o copie a vectorului pentru a face radix sort
    for(i=0;i<n;++i)
    {
        x[i]= v[i];
    }
    //calculam timpul de executare prin metoda radix sort
    auto start_r = std::chrono::steady_clock::now();
    radixsort(x,n);
    auto end_r = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff_r = end_r-start_r;
        std::cout << "timpul de executarea prin metoda radixsort" << std::setw(9)
                  << time  << diff_r.count() << " s\n";
    //verificam daca algoritmul radix sort implementat mai sus sorteaza corect
    ok=1;
    for(i=0;i<n-1; i++)
    {
        if(x[i]>x[i+1])
            ok= 0;
    }
    if(ok==1)
        cout<<"executare corecta";
    else
        cout<<"executare incorecta";
    cout<<endl;

    //facem o copie a vectorului pentru a face quick sort
    for(i=0;i<n;++i)
    {
        x[i]= v[i];
    }
    //calculam timpul de executare prin metoda quick sort
    auto start_q = std::chrono::steady_clock::now();
    quicksort(x,0,n-1);
    auto end_q = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff_q = end_q-start_q;
        std::cout << "timpul de executarea prin metoda quicksort" << std::setw(9)
                  << time  << diff_q.count() << " s\n";
    //verificam daca algoritmul quick sort implementat mai sus sorteaza corect
    ok=1;
    for(i=0;i<n-1; i++)
    {
        if(x[i]>x[i+1])
            ok= 0;
    }

    if(ok==1)
        cout<<"executare corecta";
    else
        cout<<"executare incorecta";
    cout<<endl;
    //facem o copie a vectorului pentru a face merge sort
    for(i=0;i<n;++i)
    {
        x[i]= v[i];
    }
    //calculam timpul de executare prin metoda merge sort
    auto start_m = std::chrono::steady_clock::now();
    mergesort(x,0,n-1);
    auto end_m = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff_m = end_m-start_m;
        std::cout << "timpul de executarea prin metoda mergesort" << std::setw(9)
                  << time << diff_m.count() << " s\n";
    //verificam daca algoritmul merge sort implementat mai sus sorteaza corect
    ok=1;
    for(i=0;i<n-1; i++)
    {
        if(x[i]>x[i+1])
            ok= 0;
    }
    if(ok==1)
        cout<<"executare corecta";
    else
        cout<<"executare incorecta";
    cout<<endl;


    //facem o copie a vectorului pentru a face sortarea prin bubble sort
    for(i=0;i<n;++i)
    {
        x[i]= v[i];
    }
    //calculam timpul de executare prin metoda bubble sort
    auto start_bubble = std::chrono::steady_clock::now();
    bubblesort(x,n);
    auto end_bubble = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff_bubble = end_bubble-start_bubble;
        std::cout << "timpul de executarea prin metoda bubblesort" << std::setw(9)
                  << time << diff_bubble.count() << " s\n";

    //verificam daca algoritmul bubble sort implementat mai sus sorteaza corect
    ok=1;
    for(i=0;i<n-1; i++)
    {
        if(x[i]>x[i+1])
            ok= 0;
    }
    if(ok==1)
        cout<<"executare corecta";
    else
        cout<<"executare incorecta";
    cout<<endl;

        //facem o copie a vectorului pentru a face Count sort
    for(i=0;i<n;++i)
    {
        x[i]= v[i];
    }
    //calculam timpul de executare prin metoda Count sort
    auto start_c = std::chrono::steady_clock::now();
    countSort(x,n/sizeof(v[0]));
    auto end_c = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff_c = end_c-start_c;
        std::cout << "timpul de executarea prin metoda countsort" << std::setw(9)
                  << time  << diff_c.count() << " s\n";
    //verificam daca algoritmul count sort implementat mai sus sorteaza corect
    ok=1;
    for(i=0;i<n-1; i++)
    {
        if(x[i]>x[i+1])
            ok= 0;
    }
    if(ok==1)
        cout<<"executare corecta";
    else
        cout<<"executare incorecta";
    cout<<endl;


    return 0;

}
