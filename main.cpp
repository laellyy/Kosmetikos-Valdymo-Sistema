#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// 1. REIKALAVIMAS: Vartotojo sukurta struktūra (struct) duomenims saugoti
struct Produktas {
    int id;
    string pavadinimas;
    string tipas;
    string odosTipas;
    double kaina;
    int ivertinimas;
};

// Globalus pastovus failo pavadinimas
const string FAILO_VARDAS = "care.txt";

// Funkcijų prototipai
void nuskaitytiIsFailo(vector<Produktas>& produktai);
void irasytiIFaila(const vector<Produktas>& produktai);
void rodytiVisiems(const vector<Produktas>& produktai);
void rodytiViena(const vector<Produktas>& produktai);
void pridetiProdukta(vector<Produktas>& produktai);
void redaguotiProdukta(vector<Produktas>& produktai);
void istrintiProdukta(vector<Produktas>& produktai);
void paieskaPagalOdosTipa(const vector<Produktas>& produktai); 
void skaiciuotiStatistika(const vector<Produktas>& produktai);   
void spausdintiEilute(const Produktas& p);

int main() {
    // Užtikrina, kad konsolė teisingai atvaizduotų lietuviškus simbolius
    system("chcp 65001 > nul");

    vector<Produktas> produktai;

    // Pradinių duomenų nuskaitymas iš failo programos pradžioje
    nuskaitytiIsFailo(produktai);

    int pasirinkimas;

    // Vartotojo sąsaja, veikianti konsolinio meniu principu
    do {
        cout << "\n=========================================\n";
        cout << "  KOSMETIKOS PRODUKTŲ VALDYMO SISTEMA\n";
        cout << "=========================================\n";
        cout << "[1] Rodyti visus produktus (Read)\n";
        cout << "[2] Rodyti konkretaus produkto informaciją (Read)\n";
        cout << "[3] Pridėti naują produktą (Create)\n";
        cout << "[4] Redaguoti esamą produktą (Update)\n";
        cout << "[5] Pašalinti produktą (Delete)\n";
        cout << "[6] Paieška pagal odos tipą (Papildoma funkcija 1)\n";
        cout << "[7] Rodyti kainų ir įvertinimų statistiką (Papildoma funkcija 2)\n";
        cout << "[0] Išeiti iš programos ir išsaugoti pakeitimus\n";
        cout << "-----------------------------------------\n";
        cout << "Pasirinkite veiksmą: ";

        if (!(cin >> pasirinkimas)) {
            cout << "Klaida! Įveskite skaičių iš meniu sąrašo.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            pasirinkimas = -1; 
            continue;
        }

        switch (pasirinkimas) {
        case 1:
            rodytiVisiems(produktai);
            break;
        case 2:
            rodytiViena(produktai);
            break;
        case 3:
            pridetiProdukta(produktai);
            irasytiIFaila(produktai); 
            break;
        case 4:
            redaguotiProdukta(produktai);
            irasytiIFaila(produktai);
            break;
        case 5:
            istrintiProdukta(produktai);
            irasytiIFaila(produktai);
            break;
        case 6:
            paieskaPagalOdosTipa(produktai);
            break;
        case 7:
            skaiciuotiStatistika(produktai);
            break;
        case 0:
            cout << "Duomenys sėkmingai išsaugoti faile. Programa baigia darbą.\n";
            break;
        default:
            if (pasirinkimas != -1) cout << "Tokio pasirinkimo nėra! Bandykite vėl.\n";
        }
    } while (pasirinkimas != 0);

    return 0;
}

void nuskaitytiIsFailo(vector<Produktas>& produktai) {
    ifstream failas(FAILO_VARDAS);

    if (!failas.is_open()) {
        cout << "\n[ĮSPĖJIMAS] Nepavyko atidaryti failo '" << FAILO_VARDAS << "'.\n";
        cout << "Bus sukurta nauja tuščia duomenų bazė.\n";
        return;
    }

    string eilute;
    produktai.clear(); 

    while (getline(failas, eilute)) {
        if (eilute.empty()) continue;

        stringstream ss(eilute);
        string tempId, pavadinimas, tipas, odosTipas, tempKaina, tempIvertinimas;

        getline(ss, tempId, ';');
        getline(ss, pavadinimas, ';');
        getline(ss, tipas, ';');
        getline(ss, odosTipas, ';');
        getline(ss, tempKaina, ';');
        getline(ss, tempIvertinimas, ';');

        try {
            Produktas p;
            p.id = stoi(tempId);
            p.pavadinimas = pavadinimas;
            p.tipas = tipas;
            p.odosTipas = odosTipas;
            p.kaina = stod(tempKaina);
            p.ivertinimas = stoi(tempIvertinimas);
            produktai.push_back(p);
        }
        catch (...) {
            continue; 
        }
    }
    failas.close();
    cout << "\n[SĖKMINGAI] Nuskaityta įrašų iš failo: " << produktai.size() << "\n";
}

void irasytiIFaila(const vector<Produktas>& produktai) {
    ofstream failas(FAILO_VARDAS);

    if (!failas.is_open()) {
        cout << "Klaida! Nepavyko pasiekti failo duomenų išsaugojimui.\n";
        return;
    }

    for (size_t i = 0; i < produktai.size(); i++) {
        failas << produktai[i].id << ";"
            << produktai[i].pavadinimas << ";"
            << produktai[i].tipas << ";"
            << produktai[i].odosTipas << ";"
            << produktai[i].kaina << ";"
            << produktai[i].ivertinimas;

        if (i < produktai.size() - 1) {
            failas << "\n";
        }
    }
    failas.close();
}

void spausdintiEilute(const Produktas& p) {
    cout << "| " << setw(3) << left << p.id
        << "| " << setw(32) << left << p.pavadinimas
        << "| " << setw(18) << left << p.tipas
        << "| " << setw(17) << left << p.odosTipas
        << "| " << setw(7) << fixed << setprecision(2) << right << p.kaina << " EUR "
        << "| " << setw(11) << right << p.ivertinimas << " |\n";
}

void rodytiVisiems(const vector<Produktas>& produktai) {
    if (produktai.empty()) {
        cout << "Sąrašas tuščias. Nėra duomenų peržiūrai.\n";
        return;
    }

    cout << "\n" << string(103, '-') << "\n";
    cout << "| ID | Pavadinimas                     | Tipas             | Odos tipas       | Kaina       | Įvertinimas |\n";
    cout << string(103, '-') << "\n";

    for (const auto& p : produktai) {
        spausdintiEilute(p);
    }
    cout << string(103, '-') << "\n";
}

void rodytiViena(const vector<Produktas>& produktai) {
    int paieskosId;
    cout << "Įveskite produkto ID informacijos peržiūrai: ";
    cin >> paieskosId;

    bool rasta = false;
    for (const auto& p : produktai) {
        if (p.id == paieskosId) {
            cout << "\n--- PRODUKTO INFORMACIJA ---\n";
            cout << "ID: " << p.id << "\n";
            cout << "Pavadinimas: " << p.pavadinimas << "\n";
            cout << "Tipas: " << p.tipas << "\n";
            cout << "Odos tipas: " << p.odosTipas << "\n";
            cout << "Kaina: " << p.kaina << " EUR\n";
            cout << "Įvertinimas: " << p.ivertinimas << "/10\n";
            rasta = true;
            break;
        }
    }

    if (!rasta) {
        cout << "Produktas, kurio ID " << paieskosId << ", nerastas.\n";
    }
}

void pridetiProdukta(vector<Produktas>& produktai) {
    Produktas naujas;

    int maxId = 0;
    for (const auto& p : produktai) {
        if (p.id > maxId) maxId = p.id;
    }
    naujas.id = maxId + 1;

    cin.ignore(10000, '\n');
    cout << "Įveskite naujo produkto pavadinimą: ";
    getline(cin, naujas.pavadinimas);

    cout << "Įveskite tipą: ";
    getline(cin, naujas.tipas);

    cout << "Įveskite odos tipą: ";
    getline(cin, naujas.odosTipas);

    cout << "Įveskite kainą (EUR): ";
    while (!(cin >> naujas.kaina) || naujas.kaina < 0) {
        cout << "Klaida! Įveskite teigiamą skaičių kainai: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Įveskite įvertinimą (skaičių nuo 1 iki 10): ";
    while (!(cin >> naujas.ivertinimas) || naujas.ivertinimas < 1 || naujas.ivertinimas > 10) {
        cout << "Klaida! Įvertinimas privalo būti rėžiuose [1-10]: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    produktai.push_back(naujas);
    cout << "Produktas sėkmingai pridėtas! Jam suteiktas ID: " << naujas.id << "\n";
}

void redaguotiProdukta(vector<Produktas>& produktai) {
    int redaguojamasId;
    cout << "Įveskite produkto ID, kurį norite redaguoti: ";
    cin >> redaguojamasId;

    for (auto& p : produktai) {
        if (p.id == redaguojamasId) {
            cout << "Rastas įrašas: " << p.pavadinimas << "\n";
            cout << "Paspauskite ENTER (palikite tuščią), jei nenorite keisti reikšmės.\n\n";

            cin.ignore(10000, '\n');
            string ivestimas;

            cout << "Naujas pavadinimas [" << p.pavadinimas << "]: ";
            getline(cin, ivestimas);
            if (!ivestimas.empty()) p.pavadinimas = ivestimas;

            cout << "Naujas tipas [" << p.tipas << "]: ";
            getline(cin, ivestimas);
            if (!ivestimas.empty()) p.tipas = ivestimas;

            cout << "Naujas odos tipas [" << p.odosTipas << "]: ";
            getline(cin, ivestimas);
            if (!ivestimas.empty()) p.odosTipas = ivestimas;

            cout << "Nauja kaina [" << p.kaina << " EUR] (Įveskite 0, jei palikti esamą): ";
            double naujaKaina;
            if (cin >> naujaKaina && naujaKaina > 0) {
                p.kaina = naujaKaina;
            }
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Naujas įvertinimas (1-10) [" << p.ivertinimas << "] (Įveskite 0, jei palikti esamą): ";
            int naujasIvertinimas;
            if (cin >> naujasIvertinimas && naujasIvertinimas >= 1 && naujasIvertinimas <= 10) {
                p.ivertinimas = naujasIvertinimas;
            }
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Duomenys sėkmingai atnaujinti!\n";
            return;
        }
    }
    cout << "Produktas su ID " << redaguojamasId << " nerastas.\n";
}

void istrintiProdukta(vector<Produktas>& produktai) {
    int trinamasId;
    cout << "Įveskite produkto ID, kurį norite visiškai pašalinti: ";
    cin >> trinamasId;

    for (auto it = produktai.begin(); it != produktai.end(); ++it) {
        if (it->id == trinamasId) {
            cout << "Ar tikrai norite ištrinti produktą '" << it->pavadinimas << "'? (y/n): ";
            char sutikimas;
            cin >> sutikimas;
            if (sutikimas == 'y' || sutikimas == 'Y') {
                produktai.erase(it);
                cout << "Produktas sėkmingai pašalintas iš sistemos!\n";
            }
            else {
                cout << "Trynimo veiksmas atšauktas.\n";
            }
            return;
        }
    }
    cout << "Produktas su ID " << trinamasId << " nerastas.\n";
}

void paieskaPagalOdosTipa(const vector<Produktas>& produktai) {
    cin.ignore(10000, '\n');
    string kriterijus;
    cout << "Įveskite odos tipą, pagal kurį filtruoti (pvz., Sausa, Jautri, Riebi, Visiems): ";
    getline(cin, kriterijus);

    bool rasta = false;
    cout << "\nFiltravimo rezultatai pagal odos tipą: '" << kriterijus << "':\n";
    cout << string(103, '-') << "\n";
    cout << "| ID | Pavadinimas                     | Tipas             | Odos tipas       | Kaina       | Įvertinimas |\n";
    cout << string(103, '-') << "\n";

    for (const auto& p : produktai) {
        if (p.odosTipas == kriterijus) {
            spausdintiEilute(p);
            rasta = true;
        }
    }
    cout << string(103, '-') << "\n";

    if (!rasta) {
        cout << "Nėra jokių produktų, atitinkančių įvestą odos tipą.\n";
    }
}

void skaiciuotiStatistika(const vector<Produktas>& produktai) {
    if (produktai.empty()) {
        cout << "Nėra duomenų statistiniams skaičiavimams atlikti.\n";
        return;
    }

    double bendraKaina = 0;
    double bendrasIvertinimas = 0;
    Produktas brangiausias = produktai[0];
    Produktas pigiausias = produktai[0];

    for (const auto& p : produktai) {
        bendraKaina += p.kaina;
        bendrasIvertinimas += p.ivertinimas;

        if (p.kaina > brangiausias.kaina) brangiausias = p;
        if (p.kaina < pigiausias.kaina) pigiausias = p;
    }

    double vidutineKaina = bendraKaina / produktai.size();
    double vidutinisIvertinimas = bendrasIvertinimas / produktai.size();

    cout << "\n=========================================\n";
    cout << "           SISTEMOS STATISTIKA\n";
    cout << "=========================================\n";
    cout << "Iš viso sistemoje registruota produktų: " << produktai.size() << " vnt.\n";
    cout << "Vidutinė vieno produkto kaina: " << fixed << setprecision(2) << vidutineKaina << " EUR\n";
    cout << "Vidutinis naudotojų įvertinimas: " << setprecision(1) << vidutinisIvertinimas << " / 10\n";
    cout << "-----------------------------------------\n";
    cout << "Brangiausias produktas: " << brangiausias.pavadinimas << " (" << brangiausias.kaina << " EUR)\n";
    cout << "Pigiausias produktas: " << pigiausias.pavadinimas << " (" << pigiausias.kaina << " EUR)\n";
    cout << "=========================================\n";
}