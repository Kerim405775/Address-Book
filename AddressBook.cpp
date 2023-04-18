#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Osoba
{
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};

string wczytajLinie()
{
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak()
{
    string wejscie = "";
    char znak = {0};
    while (true)
    {
        getline(cin, wejscie);
        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        else
            cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}


int odczytajPlik(Osoba *osoby, int iloscOsob)
{
    fstream plik;
    plik.open("AddressBook.txt", ios::in);

    if (plik.good() == false)
    {
        cout << "Nie mozna otworzyc pliku. " << endl;
    }

    while (plik >> osoby[iloscOsob].id)
    {
        plik.ignore();
        getline(plik, osoby[iloscOsob].imie);
        getline(plik, osoby[iloscOsob].nazwisko);
        getline(plik, osoby[iloscOsob].numerTelefonu);
        getline(plik, osoby[iloscOsob].email);
        getline(plik, osoby[iloscOsob].adres);
        iloscOsob++;
    }

    plik.close();

    return iloscOsob;
}

int dodajOsobe (Osoba *osoby, int iloscOsob)
{

    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
    cout << "Podaj imie: ";
    imie = wczytajLinie();
    cout << "Podaj nazwisko: ";
    nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu: ";
    numerTelefonu = wczytajLinie();
    cout << "Podaj email: ";
    email = wczytajLinie();
    cout << "Podaj adres: ";
    adres = wczytajLinie();

    osoby[iloscOsob].id = iloscOsob + 1;
    osoby[iloscOsob].imie = imie;
    osoby[iloscOsob].nazwisko = nazwisko;
    osoby[iloscOsob].numerTelefonu = numerTelefonu;
    osoby[iloscOsob].email = email;
    osoby[iloscOsob].adres = adres;
    system("pause");

    fstream plik;
    plik.open("AddressBook.txt", ios::out | ios::app);

    if (plik.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych. " << endl;
    }
    else
    {
        plik << osoby[iloscOsob].id << endl;
        plik << osoby[iloscOsob].imie << endl;
        plik << osoby[iloscOsob].nazwisko << endl;
        plik << osoby[iloscOsob].numerTelefonu << endl;
        plik << osoby[iloscOsob].email << endl;
        plik << osoby[iloscOsob].adres << endl;
        plik.close();
    }
    return iloscOsob + 1;
}

void wyszukaj(Osoba *osoby, int iloscOsob, string pole, string wartosc)
{
    bool znaleziono = false;
    for (int i = 0; i < iloscOsob; i++)
    {
        if ((pole == "imie" && osoby[i].imie == wartosc) ||
            (pole == "nazwisko" && osoby[i].nazwisko == wartosc))
        {
            znaleziono = true;
            cout << "Znaleziono osobe,ktora ma " << pole << " " << wartosc << endl << endl;
            cout << "ID: " << osoby[i].id << endl;
            cout << osoby[i].imie << " " << osoby[i].nazwisko << endl;
            cout << "Telefon: " << osoby[i].numerTelefonu << endl;
            cout << "Email: " << osoby[i].email << endl;
            cout << "Adres: " << osoby[i].adres << endl << endl;
        }
    }

    if (!znaleziono)
    {
        cout << "Nie znaleziono osoby o wskazanym " << pole << endl;
    }
    system("pause");
}

void wyswietlWszystkie(Osoba *osoby, int iloscOsob)
{
    for (int i = 0; i < iloscOsob; i++)
    {
        cout << "ID: " << osoby[i].id << endl;
        cout << "Imie: " << osoby[i].imie << endl;
        cout << "Nazwisko: " << osoby[i].nazwisko << endl;
        cout << "Numer telefonu: " << osoby[i].numerTelefonu << endl;
        cout << "Email: " << osoby[i].email << endl;
        cout << "Adres: " << osoby[i].adres << endl << endl;
    }
    system("pause");
}


int main()
{
    int iloscOsob = 0;
    char wybor;
    string szukaneImie;
    string szukaneNazwisko;
    Osoba osoby[1000];
    iloscOsob = odczytajPlik(osoby, iloscOsob);

    while(1)
    {
        system("cls");
        cout << "<<<<< KSIAZKA ADRESOWA >>>>>" << endl << endl;
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie osoby" << endl;
        cout << "9. Zakoncz program" << endl;

        wybor = wczytajZnak();

        switch (wybor)
        {
        case '1':
            iloscOsob = dodajOsobe(osoby, iloscOsob);
            break;
        case '2':
            cout << "Podaj imie osoby do wyszukania: ";
            cin >> szukaneImie;
            wyszukaj(osoby, iloscOsob, "imie", szukaneImie);
            break;
        case '3':
            cout << "Podaj nazwisko osoby do wyszukania: ";
            cin >> szukaneNazwisko;
            wyszukaj(osoby, iloscOsob, "nazwisko", szukaneNazwisko);
            break;
        case '4':
            wyswietlWszystkie(osoby, iloscOsob);
            break;
        case '9':
            exit(0);
            break;
        }
    }

    return 0;
}
