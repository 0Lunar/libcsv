# Guida per Principianti

## Indice

- [Introduzione](#introduzione)
- [Il tipo CSV](#il-tipo-csv)
- [Leggere un file CSV](#leggere-un-file-csv)
- [Scrivere su un file CSV](#scrivere-su-un-file-csv)
- [Manipolare oggetti CSV](#manipolare-oggetti-csv) 
  - [Creare un nodo CSV] 
  - [Ottenere un elemento](#ottenere-un-elemento)  
  - [Aggiornare il contenuto](#aggiornare-il-contenuto)  
  - [Aggiungere un nuovo nodo](#aggiungere-un-nuovo-nodo)  
  - [Trovare una stringa](#trovare-una-stringa)  
  - [Trovare una stringa in tutti i nodi](#trovare-una-stringa-in-tutti-i-nodi)  
  - [Trova e sostituisci](#trova-e-sostituisci)  
  - [Trova e sostituisci tutto](#trova-e-sostituisci-tutto)  
  - [Eliminare una colonna](#eliminare-una-colonna)  
  - [Eliminare una riga](#eliminare-una-riga)  
  - [Rimuovere celle vuote](#rimuovere-celle-vuote)  
  - [Ottenere il numero di righe](#ottenere-il-numero-di-righe)  
  - [Ottenere il numero di colonne](#ottenere-il-numero-di-colonne)  
  - [Liberare una lista CSV](#liberare-una-lista-csv)

## Introduzione

In questo file Markdown spiegheremo le funzioni della libreria `libcsv` e come utilizzarle.  

Questa guida è destinata a coloro che desiderano imparare a manipolare file CSV con il linguaggio di programmazione `C`.  
La libreria può essere utilizzata anche con il linguaggio `C++`.

## Il tipo CSV

La lista `CSV` è costituita da una struttura che contiene la riga, la colonna e il contenuto del file CSV.

```C
struct csvType {
    uint32_t row;
    uint32_t column;
    char *content;
    struct csvType *next;
};
```

L'ultimo parametro è un puntatore al prossimo elemento della lista.  

**ATTENZIONE**: La lista **deve essere ordinata per riga e colonna**, altrimenti la scrittura del file CSV potrebbe causare problemi.

## Leggere un file CSV

Per leggere un file CSV con `libcsv`, è disponibile la funzione `csvReadFile`, che richiede 2 parametri:  
- Il `puntatore FILE` che punta al file di input `(FILE *)`  
- Il `separatore`, che deve essere un singolo carattere `(const char sp)`

Il file deve essere aperto in modalità `lettura` e `testo`.

```C
CSV *csvReadFile(FILE *f, const char sp)
```

La funzione restituirà un `puntatore` a una `lista di tipo CSV` ordinata, che conterrà `riga`, `colonna` e `contenuto`.

## Scrivere su un file CSV

Per scrivere su un file CSV con `libcsv`, è disponibile la funzione `csvWriteFile`, che richiede 2 parametri:  
- Il `puntatore FILE` che punta al file di output `(FILE *f)`  
- Il `separatore`, che deve essere un singolo carattere `(const char sp)`

Il file deve essere aperto in modalità `scrittura` e `testo`.

```C
void csvWriteFile(FILE *f, CSV *root, const char sp)
```

## Manipolare oggetti CSV

Per manipolare gli `oggetti CSV` nella lista, ci sono molte funzioni disponibili. In questa sezione le elencheremo tutte.

### Creare un nodo CSV

Per creare un nodo CSV esiste la funzione `csvCreateNode` che richiede 2 parametri:
- La righa `(unsigned int)`
- La colonna `(unsigned int)`

```C
CSV *csvCreateNode(uint32_t row, uint32_t column)
```

La funzione restituirà il `puntatore` del nuovo nodo

### Ottenere un elemento

Per ottenere un elemento CSV in base alla riga e alla colonna, puoi utilizzare la funzione `csvGetElement`, che richiede 3 parametri:  
- Il **puntatore principale della lista** (cioè quello che punta al primo elemento) `(CSV *)`  
- La riga `(unsigned int)`  
- La colonna `(unsigned int)`

```C
CSV *csvGetElement(CSV *elements, uint32_t row, uint32_t column)
```

La funzione restituirà il `puntatore` dell'elemento desiderato.

---

### Aggiornare il contenuto

Per aggiornare il contenuto di un elemento nella lista, utilizza la funzione `csvUpdateElement`, che richiede 4 parametri:  
- Il **puntatore principale della lista** `(CSV *)`  
- La riga `(unsigned int)`  
- La colonna `(unsigned int)`  
- Il `contenuto` che **sostituirà l'originale** `(const char *)`

```C
void csvUpdateElement(CSV *root, uint32_t row, uint32_t column, const char *content)
```

---

### Aggiungere un nuovo nodo

Per aggiungere un nuovo nodo alla lista, utilizza la funzione `csvAddElement`, che richiede 4 parametri:  
- Il **puntatore principale della lista** `(CSV *)`  
- La riga `(unsigned int)`  
- La colonna `(unsigned int)`  
- Il contenuto `(const char *)`

```C
CSV *csvAddElement(CSV *root, uint32_t row, uint32_t column, const char *content)
```

La funzione creerà un **nuovo nodo**, che sarà aggiunto in ordine di posizione alla lista, e restituirà il **puntatore aggiornato**.

---

### Trovare una stringa

Per trovare una stringa in una lista CSV, puoi utilizzare la funzione `csvFindString`, che richiede 2 parametri:  
- Il **puntatore principale della lista** `(CSV *)`  
- La stringa da cercare `(const char *)`

```C
CSV *csvFindString(CSV *elements, const char *string)
```

La funzione restituirà il **puntatore del primo elemento** che contiene la stringa cercata. Se non viene trovato nulla, restituirà il **puntatore NULL**.

---

### Trovare una stringa in tutti i nodi

Per trovare tutti i nodi che contengono una determinata stringa, utilizza la funzione `csvFindAllStrings`, che richiede 2 parametri:  
- Il **puntatore principale della lista** `(CSV *)`  
- La stringa da cercare `(const char *)`

```C
CSV *csvFindAllStrings(CSV *root, const char *string)
```

La funzione restituirà una `lista` con tutti gli elementi che contengono la stringa fornita.

---

### Trova e sostituisci

Per cercare una stringa e sostituirla, utilizza la funzione `csvFindAndReplace`, che richiede 3 parametri:  
- Il **puntatore principale della lista** `(CSV *)`  
- La stringa da sostituire `(const char *)`  
- La nuova stringa `(const char *)`

```C
void csvFindAndReplace(CSV *root, const char *toFind, const char *string)
```

**ATTENZIONE**: Questa funzione sostituirà **solo il primo elemento** che contiene la stringa da sostituire.

---

### Trova e sostituisci tutto

Per sostituire **tutti** gli elementi che contengono una stringa, utilizza la funzione `csvFindAndReplaceAll`, che richiede 3 parametri:  
- Il **puntatore principale della lista** `(CSV *)`  
- La stringa da sostituire `(const char *)`  
- La nuova stringa `(const char *)`

```C
void csvFindAndReplaceAll(CSV *root, const char *toFind, const char *string)
```

---

### Eliminare una colonna

Per eliminare una colonna nella lista, utilizza la funzione `csvDeleteColumn`, che richiede 2 parametri:  
- Il **puntatore principale della lista** `(CSV *)`  
- La colonna `(unsigned int)`

```C
CSV *csvDeleteColumn(CSV *root, uint32_t column)
```

La funzione restituirà il puntatore della lista con i valori aggiornati.

---

### Eliminare una riga

Per eliminare una riga nella lista, utilizza la funzione `csvDeleteRow`, che richiede 2 parametri:  
- Il **puntatore principale della lista** `(CSV *)`  
- La riga `(unsigned int)`

```C
CSV *csvDeleteRow(CSV *root, uint32_t row);
```

La funzione restituirà il puntatore della lista con i valori aggiornati.

---

### Rimuovere celle vuote

Per rimuovere tutti gli elementi vuoti nella lista, utilizza la funzione `csvRemoveEmptyCells`, che richiede 1 parametro:  
- Il **puntatore principale della lista** `(CSV *)`

```C
CSV *csvRemoveEmptyCells(CSV *root)
```

La funzione restituirà il puntatore della lista con i valori aggiornati.

---

### Ottenere il numero di righe

Per ottenere il numero di righe nella lista, utilizza la funzione `csvRows`, che richiede 1 parametro:  
- Il **puntatore principale della lista** `(CSV *)`

```C
uint32_t csvRows(CSV *root)
```

---

### Ottenere il numero di colonne

Per ottenere il numero di colonne in una riga, utilizza la funzione `csvColumns`, che richiede 2 parametri:  
- Il **puntatore principale della lista** `(CSV *)`  
- La riga `(unsigned int)`

```C
uint32_t csvColumns(CSV *root, uint32_t row)
```

---

### Liberare una lista CSV

Per liberare una lista e tutto il suo contenuto, utilizza la funzione `csvFree`, che richiede 1 parametro:  
- Il **puntatore principale della lista** `(CSV *)`

```C
void csvFree(CSV *root)
```