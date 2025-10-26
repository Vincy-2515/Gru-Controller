<!-- omit from toc -->
# Guida


<!-- omit from toc -->
## Tabella dei contenuti
- [Tasti](#tasti)
  - [Ordine di Pressione dei Tasti](#ordine-di-pressione-dei-tasti)
  - [Azioni (frecce direzionali)](#azioni-frecce-direzionali)
  - [Marce (macro1, macro2, macro3)](#marce-macro1-macro2-macro3)
  - [Modalità Tasti](#modalità-tasti)
- [Comandi](#comandi)
  - [SetMotorsGearsSpeeds](#setmotorsgearsspeeds)
  - [GetMotorsInformations](#getmotorsinformations)
  - [WriteMotorsValuesToEeprom](#writemotorsvaluestoeeprom)
  - [EraseMotorsValuesFromEeprom](#erasemotorsvaluesfromeeprom)
  - [ActiveBraking](#activebraking)
  - [Help](#help)
  - [Informations](#informations)

## Tasti

### Ordine di Pressione dei Tasti

| Ordine | Azione                             |
| ------ | ---------------------------------- |
| 1      | MARCIA, Macro4 (quando necessarie) |
| 2      | Frecce direzionali                 |

### Azioni (frecce direzionali)

| Azione   | Tasti                            | Descrizione                                |
| -------- | -------------------------------- | ------------------------------------------ |
| BRACCIO  | FrecciaDestra, FrecciaSinistra   | Rotazione oraria e antioraria del braccio  |
| BOBINA   | FrecciaSu, FrecciaGiù            | Arrotolamento e rilascio del cavo          |
| CARRELLO | Macro4 + (FrecciaSu, FrecciaGiù) | Scorrimento avanti e indietro del carrello |

### Marce (macro1, macro2, macro3)

| Marcia      | Tasti                              |
| ----------- | ---------------------------------- |
| PREDEFINITA | Nessun tasto: velocità predefinita |
| PRIMA       | Macro1: velocità bassa             |
| SECONDA     | Macro2: velocità media             |
| TERZA       | Macro3: velocità alta              |

DOPO la marcia poi vanno usati i controlli per CARRELLO, BRACCIO, BOBINA.

### Modalità Tasti

| Tasto           | Modalità      |
| --------------- | ------------- |
| FrecciaSu       | TIENI PREMUTO |
| FrecciaGiù      | TIENI PREMUTO |
| FrecciaDestra   | TIENI PREMUTO |
| FrecciaSinistra | TIENI PREMUTO |
| Macro1          | TIENI PREMUTO |
| Macro2          | TIENI PREMUTO |
| Macro3          | TIENI PREMUTO |
| Macro4          | PREMI         |

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
- **_Descrizione_**: Mostra il menù di aiuto che mostra i comandi disponibili e un link a questa guida.
- **_Sintassi_**: `Help`


### Informations
- **_Descrizione_**: Mostra informazioni riguardo la versione e altro.
- **_Sintassi_**: `Informations`
