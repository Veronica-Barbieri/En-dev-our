# Progetto P2 - Model V 0.3.1

## Table of contents

<!-- toc -->

- [Meta-documentazione](#Meta-documentazione)
  * [Convezioni](#Convezioni)
    + [Nomenclatura](#Nomenclatura)
    + [Sintassi e highlight nei documenti](#Sintassi-e-highlight-nei-documenti)
    + [Convenzioni di sintassi del codice](#Convenzioni-di-sintassi-del-codice)
  * [Cambiamenti rispetto alla V0.2](#Cambiamenti-rispetto-alla-V02)
  * [Update/Rework/Adds rispetto alla V0.3](#UpdateReworkAdds-rispetto-alla-V03)
    + [Metodologia di esposizione dei contenuti](#Metodologia-di-esposizione-dei-contenuti)
    + [Tabella di tracking](#Tabella-di-tracking)
    + [Note aggiuntive sui cambiamenti](#Note-aggiuntive-sui-cambiamenti)
- [Gerarchia di classi: visione d'insieme](#Gerarchia-di-classi-visione-dinsieme)
  * [Classe `Item`](#Classe-Item)
    + [Campi dati](#Campi-dati)
    + [Definizione dei campi dati](#Definizione-dei-campi-dati)
    + [Metodi e comportamento](#Metodi-e-comportamento)
  * [Classe `Spell`](#Classe-Spell)
    + [Campi dati](#Campi-dati-1)
    + [Definizione dei campi dati](#Definizione-dei-campi-dati-1)
    + [Metodi e comportamento](#Metodi-e-comportamento-1)
  * [Classe `Generic`](#Classe-Generic)
    + [Campi dati](#Campi-dati-2)
    + [Definizione dei campi dati](#Definizione-dei-campi-dati-2)
    + [Metodi e comportamento](#Metodi-e-comportamento-2)
  * [Classe `Equip`](#Classe-Equip)
    + [Campi dati](#Campi-dati-3)
    + [Definizione dei campi dati](#Definizione-dei-campi-dati-3)
    + [Metodi e comportamento](#Metodi-e-comportamento-3)
  * [Classe `MagicGeneric`](#Classe-MagicGeneric)
    + [Campi dati](#Campi-dati-4)
    + [Definizione dei campi dati](#Definizione-dei-campi-dati-4)
    + [Metodi e comportamento](#Metodi-e-comportamento-4)
  * [Classe `Weapon`](#Classe-Weapon)
    + [Campi dati](#Campi-dati-5)
    + [Definizione dei campi dati](#Definizione-dei-campi-dati-5)
    + [Metodi e comportamento](#Metodi-e-comportamento-5)
  * [Classe `Armor`](#Classe-Armor)
    + [Campi dati](#Campi-dati-6)
    + [Definizione dei campi dati](#Definizione-dei-campi-dati-6)
    + [Metodi e comportamento](#Metodi-e-comportamento-6)

<!-- tocstop -->

## Meta-documentazione
### Convezioni 
#### Nomenclatura

Possibili convenzioni di nomenclatura:

- I nomi assegnati alle classi sono in lingua inglese con lettera maiuscola. (es: Item) 
- I nomi assegnati alle variabili sono in lingua inglese composti unicamente da lettere minuscole. Se composti devono essere intervallati dal carattere '_' (es: weapon_name);
- I nomi dei metodi in lingua inglese. Se il metodo e' composto da più termini il primo ha lettera minuscola, tutte le iniziali dei successivi hanno lettera maiuscola (es. setName);
- Devono essere dichiarate le direttive d'uso che si vogliono usare per i metodi appartenenti a un namespace (es. se voglio non dover riscrivere std::endl ogni volta che lo utilizzo, devo notificare che viene dichiarata quella direttiva d'uso e in quale file);
- TUTTI i nomi che vengono utilizzati devono essere quanto più concisi possibile, prendendo come lunghezza indicativa tra i 5 e i 7 caratteri (non tassativo ma utile)

#### Sintassi e highlight nei documenti

- I nomi delle classi vengono evidenziate in modo da rendere chiaro che si parla di classi (es. `Item`).
- Per ogni classe sono definiti Campi dati e il significato degli stessi
- I campi dati delle classi sono presentati in forma tabulare
- Le descrizioni per i campi dati sono presentate in forma tabulare espansa

#### Convenzioni di sintassi del codice

- I costruttori utilizzano le liste di inizializzazione che non sono riportate nel documento (TODO)

### Cambiamenti rispetto alla V0.2

Nella V02 della gerarchia c'erano alcuni problemi fondamentali di struttura e contenuto per i dati:
 1) Le classi `Armor` e le sottoclassi di `Weapon` contenevano una grande quantita' informazioni simili, portando a ripetizione del codice in fase di definizione. Per ovviare al problema, vengono disposte come figlie di un unica interfaccia che racchiude quelle caratteristiche comuni, delegando alle sottoclassi l'onere di implementare aspetti piu' specifici. Questo permette inoltre di unificare tutti quegli oggetti che sono utilizzati come armamentario/equipaggiamento sotto un unica interfaccia, alleggerendo la gerarchia.Questo cambiamento comporta una serie di vantaggi:  
  - viene introdotta una distinzione tra oggetti *riproducibili* e *unici*. Per esemplificare: una spada lunga e' un arma generica, sia che essa     possieda proprieta' magiche sia che non ne possieda. Una spada che esiste     come oggetto unico e dotato di proprieta' uniche puo' essere introdotta       attraverso l'implementazione di una sottoclasse che ne incapsuli i comportamenti unici.
  - nel caso si desideri introdurre una nuova tipologia di oggetti che ricadono nella categoria degli equipaggiamenti sara' sufficiente introdurre una nuova sottoclasse di `EquipItem` che ne incapsuli le caratteristiche.
 2) `Generic` (sottoclasse di `Item`), nella gerarchia precedente fungeva da interaccia per eventuali sottotipi di oggetto (tipi specializzati). A conti fatti pero' tutto quello che deve fare e' permettere la definizione di oggetti che non hanno proprieta' particolari al di fuori dell'essere esse stesse un oggetto. In questa iterazione non e' piu' interfaccia ma classe concreta che funge solo da implementazione elementare per la classe Item e che assolve al compito di permettere la definizione di oggetti "elementari", che non hanno alcuna proprieta' particolare (es. sasso, corda, torcia).
 3) Come conseguenza del punto precedente, diventava difficoltoso definire in che modo si differenziassero gli oggetti che possiedevano proprieta' magiche (e che quindi assumevano una rilevanza maggiore) da quelli che invece erano definiti senza quelle proprieta'. Per ovviare al problema viene introdotta la classe `Magic Item` che appunto si prende carico di definire le proprieta' generiche di un oggetto magico. 

### Update/Rework/Adds rispetto alla V0.3

#### Metodologia di esposizione dei contenuti

*Rework* indica un cambiamento sostanziale in alcuni aspetti del conenuto o del contenuto nella sua interezza. 
*Update* indica cambiamenti minori che non impattano in maniera considerevole il lavoro svolto in versioni precedenti.
*Adds* indica l'aggiunta di aspetti/componenti non presenti in versioni precedenti.

#### Tabella di tracking

| TIPOLOGIA | CONTENUTO |               
| :----: | :----: |
| **ADDS** | aggiunta firma metodi e loro comportamento |
| **REWORK** | modifica progettuale alla classe Spell che diventa concreta |
| **REWORK** | modifica progettuale alla classe Magic Item che diventa concreta |
| **REWORK** | modifica dei nomi della classi | 
| **UPDATE** | aggiunta campo dati "num" alla classe `Generic` |
| **UPDATE** | aggiunta campo dati "is_magic" alla classe `EquipItem` |
| **UPDATE** | aggiunta campo dati "equipped" alla classe `EquipItem` |
| **UPDATE** | aggiunta campo dati "side_material" alla classe `EquipItem`|
| **REWORK** | modifica della classe `Armor` |

#### Note aggiuntive sui cambiamenti

REWORK di `Spell` 
~ non è realmente necessario andare a ridefinire ogni volta i metodi che la classe Spell deve fornire, a conti fatti il comportamento dei metodi propri della classe rimane sempre lo stesso. E' nelle classi figlie che viene utilizzato per valutare parametri propri dell'oggetto.
REWORK di `MagicItem` 
~ cosi come per Generic viene definita un unica classe dalla quale possono essere derivate specializzazioni là dove lo si ritiene necessario, MagicItem diventa una classe i cui oggetti rappresentano oggetti magici di qualsiasi natura e che può essere estesa nel caso si vogliano creare specializzazioni o sottoinsieme di questi.
REWORK di nomi delle classi
~ - EquipItem -> Equip
  - MagicItem -> MagicGeneric

---

## Gerarchia di classi: visione d'insieme

La gerarchia si compone di:
- 1 classi base virtuale pura 
  - Item
- 1 classe base concreta
  - Spell
- 3 classi di prima derivazione 
  - Generic (concreta)
  - Equip (virtuale)
  - MagicGeneric (concreta)

Da EquipItem derivano due classi concrete
- Weapon
- Armor

che rivestono un ruolo meno importante nella gerarchia generale e sono utili ai fini del progetto.

!!!hint  Sidenote

La classe **Inventario** identifica il container di item

La classe **Personaggio** identifica l'oggetto a cui viene associato il container

Non viene specificato nulla di aggiuntivo qui circa queste due classi
!!!

Le due classi base permettono la definizione di qualunque oggetto rappresentabile e utilizzabile in un gioco di ruolo moderno.
L'idea fondante consiste nel derivare da queste due classi qualora si volesse creare una nuova categoria di oggetti, oppure rafffinare le categorie gia' presenti implementando classi che sono figlie di EquipItem, Generic o MagicItem.


![](/home/giacomo/Boostnote/img/Ger3_1.jpg)

### Classe `Item`

Classe base virtuale pura che rappresenta le caratteristiche generiche di un oggetto.

#### Campi dati

| Campo Dati | Tipo |
| :---: | :-----------: |
| name | string |
| value | int | 
| weight | int |
| material | string |

#### Definizione dei campi dati

name 
~ Il nome dell'oggetto. 
val
~ Il valore dell'oggetto
weight
~ Il peso dell'oggetto
material
~ Il materiale di cui é composto l'oggetto

#### Metodi e comportamento

**Costruttori**

`Item(string, int, int, string)`
~ Costruttore ridefinito che assegna su ogni campo dati

**Metodi propri non virtuali**

`void setName(const string&)`
~ Modifica il nome dell'oggetto.
`void setVal(const int&)`
~ Modifica il valore dell'oggetto.
`int getWeight() const`
~ Recupera il peso dell'oggetto.

**Metodi propri virtuali**

`virtual string getMaterial() const`
~ Recupera il materiale di cui e' composto l'oggetto

**Metodi virtuali puri**

`virtual string getName() const=0`
~ Recupera le informazione sul nome dell'oggetto. Virtuale perche' (ad esempio) negli equipaggiamenti risulta utile riferire il nome dell'oggetto e il materiale di cui e' composto in un unica sede (es. Spada in acciaio e non solo Spada)
`virtual int getVal() const=0`
~ Recupera il valore dell'oggetto. Virtuale per coprire il caso di oggetti di equipaggiamento o magici in cui potrebbe essere utile ridefinirlo in modo che il valore tenga in considerazione altri aspetti dell'oggetto stesso




### Classe `Spell`

Classe base concreta che rappresenta la magia come proprietà che può essere associata ad un item.
!!!hint  N.B.
Da osservare che la non presenza di proprietà magiche in un Equip Item viene rappresentata come una magia nulla e che quindi viene richiesto un costruttore nullo
!!!

#### Campi dati

| Campo Dati | Tipo |
| :---: | :-----------: |
| spell_name | string |
| spell_type | string |
| spell_level | int |
| spell_power | int |
| spell_duration | int |

#### Definizione dei campi dati

spell_name 
~ Il nome della magia
spell_type
~ Il tipo di magia (es. Fuoco)
spell_level
~ Il livello della magia
spell_power
~ L'intensità della magia
spell_duration
~ La durata della magia, espressa in turni

#### Metodi e comportamento

**Costruttori**

`Spell()`
~ Costruttore nullo, per rispettare la nota che si trova nell'overview della classe
`Spell(string, string, int, int, int): campi dati propri`
~ Costruttore che assegna su ogni campo dati
`Spell(string, string, int, int): campi dati propri`
~ Costruttore che assegna su ogni campo dati tranne duration

**Metodi propri non virtuali**

`string getSpellName() const`
~ Recupera il nome della magia
`string getSpellType() const`
~ Recupera il tipo (elemento) della magia
`int getSpellLevel() const`
~ Recupera il livello della magia
`int getSpellPower() const`
~ Recupera l'indice di potere della magia
`int getSpellDuration() const`
~ Recupera il tempo di durata della magia
`void setSpellName(const string&)`
~ Modifica il nome della magia
`void setSpellType(const string&)`
~ Modifica il tipo (elemento) della magia
`void setSpellLevel(const int&)`
~ Modifica il livello della magia
`void setSpellPower(const int&)`
~ Recupera l'indice di potere della magia
`void setSpellDuration(const int&)`
~ Modifica il tempo di durata della magia

---

### Classe `Generic`

Classe derivata unicamente da Item che rappresenta un item che non possiede proprieta' magiche. 

#### Campi dati

| Campo Dati | Tipo |
| :---: | :-----------: |
| num | int |


#### Definizione dei campi dati

num 
~ Se si possiedono più oggetti identici a questo, num > 1

#### Metodi e comportamento

**Costruttori**

`Generic(string, int, int, string, num): campi dati propri`
~ Costruttore ridefinito che assegna su ogni campo dati

**Metodi di cui viene fatto Override**

`override string getName() const`
~ Recupera il nome dell'oggetto.
`override int getVal() const`
~ Recupera il valore dell'oggetto. 
`override int getWeight() const`
~ Recupera il peso dell'oggetto. 
`ostream& operator<<(ostream&, const Generic&)`
~ Operatore di output
`istream& operator>>(istream&, Generic&)`
~ Operatore di input


**Metodi propri non virtuali**

`void setNum(const int&)`
~ Modifica il campo dati num 
`int getNum() const`
~ Recupera il valore del campo dati num

### Classe `Equip`

Classe derivata da Item e Magic che rappresenta il concetto generico di equipaggiamento da battaglia

#### Campi dati

| Campo Dati | Tipo |
| :---: | :-----------: |
| equip_power | int |
| type | string |
| rarity | string |
| side_material | string |
| is_magic | bool |
| equipped | bool |

#### Definizione dei campi dati

equip_power
~ Il valore di potenza dell'equipaggiamento
type
~ Il tipo di equipaggiamento, distinguibile in:
  - leggero
  - pesante
rarity
~ La rarità dell'arma che ha come valori possibili:
  - commmon
  - rare
  - epic
  - legendary
  !!!attention  N.B.
  Questa classe indica una generalizzazione di un oggetto, quindi non ha senso andare a definire un livello di rarita' **Unique** per identificare un oggetto non categorizzabile (es. Excalibur e' un oggetto unico, non riproducibile). Nel caso in cui si volesse creare un oggetto unico si deve creare una nuova classe che deriva da `EquipItem` e che identifica quello specifico oggetto.  
  !!!
side_material
~ Eventuali materiali aggiuntivi di cui è composta l'arma
is_magic
~ Parametro che traccia la presenza o meno di proprieta' magiche nell'oggetto
equipped
~ Parametro che traccia se l'oggetto e' equipaggiato o meno

#### Metodi e comportamento

**Costruttori**

`Equip(int, string, string, string, bool, bool, string, int, int, string, string, string, int, int, int): Item(...), Spell(...), elenco campi dati propri`
~ Costruttore che assegna su ogni campo dati e sui sottoggetti *Item* e *Spell*
`Equip(int, string, string, string, bool, bool, string, int, int, string): Item(...), Spell(), elenco campi dati propri`
~ Costruttore che assegna su tutti i campo dati e SOLO sul sottoggetto *Item*

**Metodi di cui viene fatto Override**

`override string GetName() const`
~ Recupera il nome dell'oggetto e lo concatena al materiale e al fatto che sia un equipaggiamento Magico oppure no (es. Spada magica in diamante).
`override int GetVal() const`
~ Recupera il valore dell'oggetto e lo aumenta sulla base del materiale e sulla presenza o meno di proprieta' magiche. 
`override string getMaterial() const`
~ Recupera le informazioni sui materiali (Item::material e EquipItem::side_material) di cui è composto l'oggetto.

**Metodi di cui NON viene fatto Override**

!!!note  Motivazione
Teoricamente, non ho necessita' di creare oggetti del tipo EquipItem ma solo sue derivazioni, quindi non implemento input e output perche' non necessari
!!!

`override ostream& operator<<(ostream&, const Generic&)`
~ Operatore di output
`override istream& operator>>(istream&, Generic&)`
~ Operatore di input

**Metodi propri non virtuali**

`int getEquipPower() const`
~ Recupera il valore di potenza dell'oggetto
`string getType() const`
~ Recupera il tipo dell'oggetto 
`string getRarity() const`
~ Recupera il livello di rarita' dell'oggetto
`bool getIsEquipped() const`
~ Recupera lo status di equipaggiamento dell'oggetto
`bool getIsMagic() const`
~ Recupera lo status magico dell'oggetto
`void setEquipPower(const in&)`
~ Setta il valore di potenza dell'oggetto
`void setType(const string&)`
~ Settaa il tipo dell'oggetto 
`void setRarity(const string&)`
~ Setta il livello di rarita' dell'oggetto
`virtual void setIsEquipped(const bool&)`
~ Setta lo status di equipaggiamento dell'oggetto
`void setIsMagic(const bool&)`
~ Setta lo status magico dell'oggetto



### Classe `MagicGeneric`

La classe MagicItem identifica un oggetto generico che pero' gode di proprieta' magiche e che quindi richiede una specifica rappresentazione.

#### Campi dati

| Campo Dati | Tipo |
| :---: | :-----------: |
| range | int |
| description | string |

#### Definizione dei campi dati

range 
~ L' area di effetto della magia
description
~ La descrzione dell' effetto della magia

#### Metodi e comportamento

**Costruttori**

`MagicItem()`
~ Costruttore vuoto
`MagicItem(string, int, int, string, string, string, int, int, int): Item(...), Spell(...)`
~ Costruttore che assegna su tutti i campi dati
`MagicItem(string, int, int, string, string, string, int, int): Item(...), Spell(...)`
~ Costruttore che assegna su tutti i campi dati tranne duration (usa il secondo costruttore di Spell)

**Metodi virtuali ridefiniti**

`virtual string getName() const`
~ Recupera il nome dell'oggetto concatenandolo alla sua proprietà magica
`virtual int getVal() const`
~ Recupera il valore dell'oggetto. 

**Metodi propri non virtuali**

`int getRange() const`
~ Recupera il range a cui può agire l'oggetto/Incantesimo
`string getDescription() const`
~ Recupera la descrizione dell'oggetto
`void setRange(const int&)`
~ Modifica il range
`void setDescription(const string&)`
~ Modifica la descrizione dell'oggetto
`override ostream& operator<<(ostream&, const Generic&)`
~ Operatore di output
`override istream& operator>>(istream&, Generic&)`
~ Operatore di input

---


### Classe `Weapon`

#### Campi dati

| Campo Dati | Tipo |
| :---: | :-----------: |
| melee_type_dmg | string |
| ranged_type_dmg | string |
| min_range | int |
| max_range | int |

#### Definizione dei campi dati

melee_type_dmg
~ Il tipo di danno che l'arma e' in grado di infliggere corpo a corpo
ranged_type_dmg
~ Il tipo di danno che l'arma e' in grado di infliggere dalla distanza, se vi e' modo di farne. 
min_range
~ La distanza minima a cui e' possibile colpire
max_range
~ La distanza massima a cui e' possibile colpire

#### Metodi e comportamento

**Costruttori**

`Weapon(int, string, string, string, bool, bool, string, int, int, string, string, string, int, int, int, string, string, int, int): Equip(...), campi dati propri`
~ Costruttore che assegna su tutti i campi dati
`Weapon(int, string, string, string, bool, bool, string, int, int, string, string, string, int, int): Equip(...), campi dati propri`
~ Costruttore che assegna sui campi dati dai Equip

**Metodi propri non virtuali**

`override ostream& operator<<(ostream&, const Generic&)`
~ Operatore di output
`override istream& operator>>(istream&, Generic&)`
~ Operatore di input
`string getMeleeTypeDmg() const`
~ Recupera il tipo di danno che l'arma e' in grado di infliggere corpo a corpo
`string getRangedTypeDmg() const`
~ Recupera tipo di danno che l'arma e' in grado di infliggere dalla distanza.
`int getMinRange() const`
~ Recupera la distanza minima a cui è possibile colpire
`int getMaxRange() const`
~ Recupera la distanza massima a cui è possibile colpire
`string getMeleeTypeDmg() const`
~ Recupera il tipo di danno che l'arma e' in grado di infliggere corpo a corpo
`string getRangedTypeDmg() const`
~ Recupera tipo di danno che l'arma e' in grado di infliggere dalla distanza.
`int getMinRange() const`
~ Recupera la distanza minima a cui è possibile colpire
`int getMaxRange() const`
~ Recupera la distanza massima a cui è possibile colpire
`void setMeleeTypeDmg()`
~ Setta il tipo di danno che l'arma e' in grado di infliggere corpo a corpo
`void setRangedTypeDmg()`
~ Recupera tipo di danno che l'arma e' in grado di infliggere dalla distanza.
`void setMinRange()`
~ Recupera la distanza minima a cui è possibile colpire
`void setMaxRange()`
~ Recupera la distanza massima a cui è possibile colpire

**Metodi che grazie a dio non sono getter o setter**

`bool isMagic()` 
~ Recupera le informazioni circa la natura magica (o meno) dell'arma
`int weaponDmg()`
~ Recupera il danno che l'arma è in grado di infliggere, tenendo conto del fatto che sia magica o meno

### Classe `Armor`

Classe derivata da EquipItem che rappresenta un armatura nella sua interezza.

#### Campi dati

| Campo Dati | Tipo |
| :---: | :-----------: |
| damaged | bool |

#### Definizione dei campi dati

damaged
~ Traccia lo stato di integrita' o meno dell'armatura

#### Metodi e comportamento

**Costruttori**

`Weapon(int, string, string, string, bool, bool, string, int, int, string, string, string, int, int, int, bool): Equip(...), campi dati propri`
~ Costruttore che assegna su tutti i campi dati

**Metodi propri non virtuali**

`bool getDamaged() const`
~ Recupera le informazioni circa lo stato di integrità dell'armatura
`void setDamaged()`
~ Setta le informazioni circa lo stato di integrità dell'armatura