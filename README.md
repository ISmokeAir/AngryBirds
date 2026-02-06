# Angry Birds OOP

### Acest proiect reprezintă o simulare complexă a jocului Angry Birds realizată în C++, rulată în terminal.

Jocul modelează interacțiunea fizică dintre păsări și structuri, influențată de condiții meteorologice variabile. Proiectul include un sistem economic, mecanici de salvare/încărcare a reluărilor (replay), statistici și un sistem de realizări (achievements) bazat pe evenimente.

| Laborant  | Link template                                |
|-----------|----------------------------------------------|
| Dragoș B  | https://github.com/Ionnier/oop-template      |
| Tiberiu M | https://github.com/MaximTiberiu/oop-template |
| Marius MC | https://github.com/mcmarius/oop-template     |

### Funcționalități Implementate

1.  **Sistem de Fizică și Meteo**: Calculul traiectoriei ține cont de gravitație, rezistența aerului și vânt (variabil în funcție de vreme: Soare, Ploaie, Furtună).
2.  **Entități Polimorfice**: 
    * Păsări: Red (Standard), Chuck (Viteză), Bomb (Explozie), Matilda (Egg Drop).
    * Ținte: Lemn, Piatră, Gheață (cu rezistențe diferite la impact).
3.  **Economie și Magazin**: Jucătorul câștigă bani din distrugerea țintelor și poate cumpăra upgrade-uri.
4.  **AI și Predictie**: Un modul "Super Computer" care simulează mii de traiectorii pentru a găsi unghiul optim de lansare.
5.  **Replay System**: Posibilitatea de a salva și revedea ultimul meci jucat.
6.  **Achievements**: Sistem reactiv care deblochează realizări în timp real (Observer Pattern).

---

## Tema 0

- [x] Nume proiect: Angry Birds OOP
- [x] Scurtă descriere a temei alese: Simulare fizică a lansării proiectilelor asupra unor ținte distructibile, cu elemente de meteo și economie.

## Tema 1

#### Cerințe
- [x] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi (`Game`, `Bird`, `Target`, `Stats`, `Vector2D`)
- [x] constructori de inițializare cu parametri pentru fiecare clasă
- [x] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor (`Game`, `Bird`)
- [x] `operator<<` pentru **toate** clasele pentru afișare (`std::ostream`)
- [x] cât mai multe `const` (unde este cazul) și funcții `private`
- [x] implementarea a minim 3 funcții membru publice pentru funcționalități netriviale (`PhysicsEngine::simulateTrajectory`, `Target::aplicaImpact`, `Game::lanseazaPasare`)
- [x] scenariu de utilizare **cu sens** a claselor definite
- [x] minim 50-55% din codul propriu să fie C++
- [x] tag de `git`: `V0.1.6.1`
- [x] serviciu de integrare continuă (CI) configurat

## Tema 2

#### Cerințe
- [x] separarea codului din clase în `.h` și `.cpp`
- [x] moșteniri:
  - Clasa de bază `Bird` (abstractă)
  - Derivate: `RedBird`, `ChuckBird`, `BombBird`, `MatildaBird`
  - [x] funcții virtuale pure: `calculeazaMomentum`, `clone`
  - [x] apelarea constructorului din clasa de bază din constructori din derivate
  - [x] clasă cu atribut de tip pointer la o clasă de bază (`Game` conține `std::vector<Bird*>`)
    - [x] suprascris cc/op= pentru copieri deep copy (folosind `clone`)
    - [x] `dynamic_cast` folosit pentru abilitatea specială a `BombBird` și `MatildaBird`
- [x] excepții
  - [x] ierarhie proprie: `GameException` (bază), `FileException`, `InputException`, `LogicException`
  - [x] utilizare cu sens: validare input, deschidere fișiere log/replay
- [x] funcții și atribute `static` (`Bird::numarPasari`, `MapGenerator` methods)
- [x] STL (`std::vector`, `std::string`, `std::map` pentru magazin)
- [x] cât mai multe `const` și referințe
- [x] minim 75-80% din codul propriu să fie C++
- [x] commit separat cu adăugarea unei noi clase derivate: `MatildaBird`
- [x] tag de `git`: `V0.2.1`

## Tema 3

#### Cerințe
- [x] 2 șabloane de proiectare (design patterns)
  1. **Observer Pattern**: Implementat în `AchievementSystem` (Observer) și `Game` (Subject) pentru notificarea evenimentelor (lovituri, distrugeri).
  2. **Prototype Pattern**: Implementat prin metoda `clone()` în ierarhia `Bird` pentru copierea corectă a obiectelor polimorfice.
  3. (Bonus) **Static Factory Method**: Implementat în `MapGenerator` pentru crearea nivelurilor.
- [x] o clasă șablon cu sens; minim **2 instanțieri**
  - Clasa `GameContainer<T>` folosită pentru:
    1. Istoricul acțiunilor (`GameContainer<std::string>`)
    2. Scoruri sesiune (`GameContainer<int>`)
- [x] o funcție șablon (template) cu sens; minim 2 instanțieri
  - Funcția `debugLog<T>` folosită pentru tipurile `int` și `double`.
- [ ] minim 85% din codul propriu să fie C++
- [x] tag de `git`: `V0.3.1.3`

## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

1. Configurare:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug