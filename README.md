# CercaPercorso 

## Descrizione

Il progetto "CercaPercorso" si concentra su un'autostrada composta da stazioni di servizio, ciascuna con un'identificazione basata sulla sua distanza dall'inizio dell'autostrada e dotata di veicoli elettrici con autonomie specifiche. L'obiettivo principale è identificare il percorso più breve tra due stazioni, con la necessità di cambiare veicolo ad ogni tappa.

## Comandi e Risposte

Il progetto supporta i seguenti comandi:

- `aggiungi stazione distanza numero auto auto1 ... autoN`: Aggiunge una stazione all'autostrada identificata dalla sua distanza. Specifica anche il numero di veicoli e le relative autonomie. Se una stazione con la stessa distanza esiste già, il comando non avrà effetto.

- `demolisci stazione distanza`: Rimuove la stazione di servizio situata alla distanza specificata. Se non esiste una stazione alla distanza indicata, il comando stampa "non demolita".

- `aggiungi auto distanza stazione autonomia auto`: Aggiunge un veicolo con un'autonomia specifica a una stazione esistente alla distanza specificata. Se la stazione non esiste, il comando non avrà effetto.

- `rottama auto distanza stazione autonomia auto`: Rimuove un veicolo con un'autonomia specifica dalla stazione situata alla distanza specificata. Se la stazione o il veicolo con l'autonomia indicata non esistono, il comando stampa "non rottamata".

- `pianifica percorso stazione partenza stazione arrivo`: Pianifica il percorso più breve tra la stazione di partenza e quella di arrivo, a condizione che esista un percorso valido. Il percorso è identificato dalla sequenza di stazioni in ordine di percorrenza, comprese la stazione di partenza e quella di arrivo. Se il percorso non esiste, verrà visualizzato "nessun percorso".

## Note Aggiuntive

- L'autostrada ha due sensi di percorrenza.

- In caso di più percorsi con la stessa lunghezza tra due stazioni, il sistema sceglierà il percorso che predilige le stazioni più vicine all'inizio dell'autostrada, indipendentemente dal senso di percorrenza.

- Ad esempio, se il percorso corretto tra 10 e 60 è 10→20→40→60, non saranno considerati percorsi che seguono stazioni con numeri più alti.

Questo progetto è stato realizzato come parte del corso di Algoritmi e Principi dell'Informatica ed è progettato per illustrare i concetti di algoritmi di percorso e decisionali.

---

