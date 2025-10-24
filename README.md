### Ordine di Pressione dei Tasti

| Ordine | Azione                                              |
| ------ | --------------------------------------------------- |
| 1      | MARCIA (Macro1, Macro2, Macro3) (quando necessaria) |
| 2      | Macro4 (quando necessaria)                          |
| 3      | Frecce direzionali                                  |

### Azioni

| Azione   | Tasti                            | Descrizione                                |
| -------- | -------------------------------- | ------------------------------------------ |
| BRACCIO  | FrecciaDestra, FrecciaSinistra   | Rotazione oraria e antioraria del braccio  |
| BOBINA   | FrecciaSu, FrecciaGiù            | Arrotolamento e rilascio del cavo          |
| CARRELLO | Macro4 + (FrecciaSu, FrecciaGiù) | Scorrimento avanti e indietro del carrello |

### Marce

| Marcia      | Tasti                              |
| ----------- | ---------------------------------- |
| PREDEFINITA | Nessun tasto: velocità predefinita |
| PRIMA       | Macro1: velocità bassa             |
| SECONDA     | Macro2: velocità media             |
| TERZA       | Macro3: velocità alta              |

DOPO la marcia poi vanno usati i controlli per CARRELLO, BRACCIO, BOBINA

### Modalità Tasti

| Tasto           | Mdalità       |
| --------------- | ------------- |
| FrecciaSu       | TIENI PREMUTO |
| FrecciaGiù      | TIENI PREMUTO |
| FrecciaDestra   | TIENI PREMUTO |
| FrecciaSinistra | TIENI PREMUTO |
| Macro1          | TIENI PREMUTO |
| Macro2          | TIENI PREMUTO |
| Macro3          | TIENI PREMUTO |
| Macro4          | PREMI         |

---

### Valori assegnabili ai pin del driver L298N per il controllo dei motori

| **Stato**          | **IN1,IN3** | **IN2,IN4** | **ENA,ENB** | **Descrizione**                                                                   |
| ------------------ | ----------- | ----------- | ----------- | --------------------------------------------------------------------------------- |
| **Avanti**         | HIGH        | LOW         | PWM         | Ruota in avanti con velocità specificata da "PWM"                                 |
| **Indietro**       | LOW         | HIGH        | PWM         | Ruota all'indietro con velocità specificata da "PWM"                              |
| **Disabilitato**   | LOW         | LOW         | LOW         | Continua a girare liberamente se già in movimento o se applicata forza su di esso |
| **Frenata attiva** | HIGH        | HIGH        | HIGH        | Viene fermato velocemente e mantenuto bloccato in posizione                       |
