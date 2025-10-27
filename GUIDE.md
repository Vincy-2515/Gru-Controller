<!-- omit from toc -->
# Guida


<!-- omit from toc -->
## Tabella dei contenuti
- [Tasti](#tasti)
  - [Ordine di Pressione](#ordine-di-pressione)
  - [Azioni (Frecce Direzionali)](#azioni-frecce-direzionali)
  - [Marce (Velocità)](#marce-velocità)
- [Comandi](#comandi)
  - [SetMotorsGearsSpeeds](#setmotorsgearsspeeds)
  - [GetMotorsInformations](#getmotorsinformations)
  - [WriteMotorsValuesToEeprom](#writemotorsvaluestoeeprom)
  - [EraseMotorsValuesFromEeprom](#erasemotorsvaluesfromeeprom)
  - [ActiveBraking](#activebraking)
  - [Help](#help)
  - [Informations](#informations)


## Tasti
I controlli sono divisi in **Marce** (velocità) e **Azioni** (movimenti dei motori). Le Marce vanno selezionate **prima** delle Azioni.

### Ordine di Pressione
1.  **Marcia**, **Macro4** (se necessarie)
2.  **Azione** (Frecce direzionali)

---

### Azioni (Frecce Direzionali)
Tutte le frecce direzionali funzionano in modalità "**TIENI PREMUTO**": il movimento inizia quando sono premute e si blocca quando vengono rilasciate.

Il tasto **Macro4** funziona in modalità "**PREMI**" scambia i controlli di **CARRELLO** e **BOBINA** sulle frecce Su/Giù.

| Motore controllato | Tasti (Macro4 NON premuto)     | Descrizione                                                       |
| :----------------- | :----------------------------- | :---------------------------------------------------------------- |
| **BRACCIO**        | FrecciaDestra, FrecciaSinistra | Rotazione oraria e antioraria                                     |
| **CARRELLO**       | FrecciaSu, FrecciaGiù          | Scorrimento avanti e indietro (Controlli Standard)                |
| **BOBINA**         | **Nessuna Azione**             | Arrotolamento e rilascio del cavo (Controlli Scambiati da Macro4) |

---

### Marce (Velocità)
Le Marce modificano la velocità dei motori e devono essere tenute premute **prima** di eseguire un'Azione. La loro modalità è **TIENI PREMUTO**.

| Marcia          | Tasto        | Velocità    | Azione al Rilascio                       |
| :-------------- | :----------- | :---------- | :--------------------------------------- |
| **Predefinita** | Nessun tasto | Predefinita | N/A                                      |
| **Prima**       | Macro1       | Bassa       | Nessuna, **SE** rilasciato dopo l'azione |
| **Seconda**     | Macro2       | Media       | Nessuna, **SE** rilasciato dopo l'azione |
| **Terza**       | Macro3       | Alta        | Nessuna, **SE** rilasciato dopo l'azione |


## Comandi


### SetMotorsGearsSpeeds
- **_Descrizione_**: Permette l'impostazione delle velocità delle marce dei motori, velocità regolata con valori da 0 a 255, dove 0 è il minimo e 255 è il massimo.
- **_Sintassi_**: `SetMotorsGearsSpeeds a,b,c,d; e,f,g,h; i,k,l,m;`
- **_Parametri_**:

| Parametro | Motore controllato | Marcia      | Valori accettati |
| --------- | ------------------ | ----------- | ---------------- |
| a         | BRACCIO            | 1°          | 0-255            |
| b         | BRACCIO            | 2°          | 0-255            |
| c         | BRACCIO            | 3°          | 0-255            |
| d         | BRACCIO            | Predefinita | 0-255            |
| e         | CARRELLO           | 1°          | 0-255            |
| f         | CARRELLO           | 2°          | 0-255            |
| g         | CARRELLO           | 3°          | 0-255            |
| h         | CARRELLO           | Predefinita | 0-255            |
| i         | BOBINA             | 1°          | 0-255            |
| k         | BOBINA             | 2°          | 0-255            |
| l         | BOBINA             | 3°          | 0-255            |
| m         | BOBINA             | Predefinita | 0-255            |

> [!IMPORTANT]
> Per preservare la memoria interna della scheda, i valori assegnati con questo comando sono **TEMPORANEI**, quindi vengono cancellati al riavvio della scheda. Solo dopo aver effettuato tutte le varie prove e aver scelto i valori finali è possibile eseguire il comando [WriteMotorsValuesToEeprom](#writemotorsvaluestoeeprom) per salvare effettivamente i valori nella memoria.


### GetMotorsInformations
- **_Descrizione_**: Restituisce valori e impostazioni relativi ai motori.
- **_Sintassi_**: `GetMotorsInformations`


### WriteMotorsValuesToEeprom
- **_Descrizione_**: Salva in memoria i valori impostati precedentemente con i comandi [SetMotorsGearsSpeeds](#setmotorsgearsspeeds) e [ActiveBraking](#activebraking).
- **_Sintassi_**: `WriteMotorsValuesToEeprom`


### EraseMotorsValuesFromEeprom
- **_Descrizione_**: Elimina i valori salvati in memoria.
- **_Sintassi_**: `EraseMotorsValuesFromEeprom`


### ActiveBraking
- **_Descrizione_**: Permette l'abilitazione della "frenata attiva" per singolo motore, permettendo di scegliere anche l'intensità con cui essa avviene. E' possibile l'abilitazione e la disabilitazione impostando rispettivamente 1 e 0  ai parametri corrispondenti. E' inoltre possibile la regolazione dell'intensità di frenata con valori da 0 a 255 ai parametri corrispondenti, dove 0 è il minimo e 255 è il massimo.
- **_Sintassi_**: `ActiveBraking a,b,c; d,e,f;`
- **_Parametri_**:

| Parametro | Motore controllato | Scopo                        | Valori accettati |
| --------- | ------------------ | ---------------------------- | ---------------- |
| a         | BRACCIO            | abilitazione/disabilitazione | 1,0              |
| b         | CARRELLO           | abilitazione/disabilitazione | 1,0              |
| c         | BOBINA             | abilitazione/disabilitazione | 1,0              |
| d         | BRACCIO            | controllo intensità          | 0-255            |
| e         | CARRELLO           | controllo intensità          | 0-255            |
| f         | BOBINA             | controllo intensità          | 0-255            |


### Help
- **_Descrizione_**: Mostra il menù di aiuto che elenca i comandi disponibili e un link a questa guida.
- **_Sintassi_**: `Help`


### Informations
- **_Descrizione_**: Mostra informazioni riguardo la versione e altro.
- **_Sintassi_**: `Informations`
