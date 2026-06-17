# 🌿 Kosmetikos ir Odos Priežiūros Produktų Valdymo Sistema

Sveiki! Tai Struktūrinio programavimo ir algoritmų kurso projektinis darbas, realizuotas naudojant C++ programavimo kalbą. Programa sukurta siekiant padėti patogiai sekti, analizuoti ir valdyti kosmetikos priemonių bei odos priežiūros produktų asortimentą.

---

## 📋 Projekto turinys (7 Privalomi punktai)

### 1. Projekto pavadinimas
**Kosmetikos produktų apskaitos ir valdymo konsolinė sistema.**

### 2. Projekto tikslas
Sukurti veikiančią C++ konsolinę programą, skirtą prekių duomenų bazei administruoti. Projekto tikslas – praktiškai pritaikyti kurso metu įgytas struktūrinio programavimo teorines žinias: duomenų tipų valdymą, ciklinius ir sąlyginius procesus, darbą su srautais (tekstinių failų nuskaitymas/rašymas), vartotojo sukurtas struktūras (`struct`) bei dinamines kolekcijas (`std::vector`).

### 3. Pasirinktos temos aprašymas
Pasirinkta tema apima kosmetikos bei kasdienės odos priežiūros priemonių (prausiklių, drėkinamųjų kremų, serumų, SPF apsaugos priemonių) katalogavimą. Kiekvienas sistemoje užregistered produktas turi šiuos laukus:
* **ID** – unikalus sveikasis skaičius prekės identifikavimui.
* **Pavadinimas** – prekės brendas ir pavadinimas (pvz., *CeraVe Hydrating Cleanser*).
* **Tipas** – produkto kategorija (pvz., *Prausiklis*, *Kremas*, *SPF*).
* **Odos tipas** – odos būklė, kuriai produktas yra skirtas (pvz., *Sausa*, *Jautri*, *Riebi*, *Visiems*).
* **Kaina** – produkto kaina eurais (realusis skaičius).
* **Įvertinimas** – vartotojų atsiliepimų vidurkis 10-balėje sistemoje (sveikasis skaičius).

### 4. Programos funkcionalumo aprašymas
Programa pilnai realizuoja **CRUD** (Create, Read, Update, Delete) architektūros gyvavimo ciklą ir suteikia vartotojui galimybę interaktyviai valdyti duomenis realiu laiku per patogų konsolinį meniu:
* **Create (Pridėjimas):** Leidžia įvesti naują kosmetikos priemonę. Sistema automatiškai suranda didžiausią esamą ID ir priskiria naujam produktui unikalų ID.
* **Read (Peržiūra):** * Galima išvesti visą prekių sąrašą, kuris sugeneruojamas vizualiai tvarkingoje, lygiuotoje lentelėje.
    * Galima peržiūrėti tik vieną konkretų produktą, konsolėje įvedus jo unikalų ID numerį.
* **Update (Redagavimas):** Leidžia modifikuoti pasirinkto produkto informaciją. Sistema išveda esamas reikšmes, o vartotojas gali įrašyti naujas arba paspausti *ENTER* ir palikti senąsias nekeistas.
* **Delete (Pašalinimas):** Ištrina pasirinktą produktą iš dinaminės atminties su papildomu saugumo patvirtinimu, kad veiksmas nebūtų atliktas netyčia.

Pakeitus duomenis (pridėjus, redagavus ar ištrynus), programa automatiškai sinchronizuoja pakeitimus su išoriniu failu.

### 5. Naudojamų failų aprašymas
* **`main.cpp`** – Pagrindinis programos išeities kodas. Jame aprašyta duomenų struktūra, meniu valdymas, srautų operacijos ir visos CRUD bei papildomos funkcijų realizacijos.
* **`care.txt`** – Išorinis tekstinis failas, atliekantis vietinės duomenų bazės vaidmenį. Jame saugoma 15 struktūrizuotų įrašų eilučių. Kiekviena eilutė atitinka vieną produktą, o jo duomenų laukai atskirti specialiu skyrikliu – kabliataškiu (`;`), pavyzdžiui:
    `1;CeraVe Hydrating Cleanser;Prausiklis;Sausa;12.99;9`

### 6. Programos paleidimo instrukcija
1. Atsisiųskite arba suklonuokite šią repozitoriją į savo kompiuterį.
2. Įsitikinkite, kad duomenų failas `care.txt` yra **tame pačiame aplanke** kaip ir jūsų `main.cpp` failas.
3. Atidarykite VS Code terminalą tame aplanke ir sukompiliuokite kodą rankiniu būdu naudojant C++ kompiliatorių:
   ```bash
   g++ main.cpp -o main.exe
