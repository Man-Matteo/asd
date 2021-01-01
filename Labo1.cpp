// Implementa le funzioni sulle liste realizzate con strutture doppiamente collegate, circolari, con sentinella, senza ordinamento

// FILE DA MODIFICARE

#include "ASD-doubly-linked-list.h"


using namespace list;

struct list::node {  // descrivo qui, fuori dal namespace, come e' fatta la struttura node: i dettagli interni non saranno visibili dal main
    Elem info;
    node *prev;
    node *next;
};

/*************************************************/
/* Implementazione delle operazioni di utilita' */
/*************************************************/

void readFromStream(istream& str, List& l) {
    createEmpty(l);
    Elem e;
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    // assumiamo che il segnale di fine input nel file sia  FINEINPUT
    while (e != FINEINPUT)  {
        addRear(e, l);   // aggiunge l'elemento alla fine della lista
        str>>e;
        if (!str) throw runtime_error("Errore inserimento dati\n");
    }
}

/* legge il contenuto di una lista da file */
void readFromFile(string nome_file, List& l) {
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    readFromStream(ifs, l);
}


/* legge il contenuto di una lista da standard input */
void readFromStdin(List& l) {
   cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
   readFromStream((std::cin), l);
}

/* stampa la lista */
void print(const List& l) {
   List q = l->next;  // q "salta la sentinella" e va alla testa della lista
   while (q != l) {   // avanza finche' non finisce la lista
      cout << q->info << "; ";
      q = q->next;
    }
}

/**************************************************/
/* Implementazione delle operazioni nel namespace */
/**************************************************/

/* crea la lista vuota */
void list::createEmpty(List& l) {
  l = new node;
  l->next = l;
  l->prev = l;
}

/* "smantella" la lista svuotandola */
void list::clear(const List& l) {

  node *p = l->next; //puntatore aux a tipo node che salta la sentinella che sta in "l"
  node *q;

  while (p != l) {
    q = p->next;
    delete p;
    p = q;
  }

  l->next = l;
  l->prev = l;

}

/* restituisce l'elemento in posizione pos se presente; restituisce un elemento
che per convenzione si decide che rappresenta l'elemento vuoto altrimenti*/
Elem list::get(int pos, const List& l) {

  if (pos > size(l) || pos < 0)
    return EMPTYELEM;

  node *aux = l->next;
  for (int i=0; i<pos; i++)
    aux=aux->next;

  return aux->info;

}

/* modifica l'elemento in posizione pos, se la posizione e' ammissibile */
void list::set(int pos, Elem e, const List& l) {

  if (pos < size(l) && pos > 0) {
    node *aux = l->next;
    for (int i=0; i<pos; i++)
      aux=aux->next;

    aux->info = e;
  }
}

/* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
void list::add(int pos, Elem e, const List& l) {
  if (pos == 0)
    addFront(e,l);
  if (pos == size(l))
    addRear(e,l);

  if (pos < size(l)-1 && pos >= 1) {

    node *p
    node *n
    node *aux

    for (int i=0; i<pos; i++)
      aux=aux->next;

    List p = new node;
    p->info = e;

    p->prev = aux
    p->next = aux->next;
    aux->next = p;
    p->next->prev = p;
  }
}

/* inserisce l'elemento alla fine della lista */
void list::addRear(Elem e,  const List& l) {

  List q = new node;
  q->info = e;

  q->prev = l->prev;
  q->prev->next = q;
  q->next = l;
  l->prev = q

}

/* inserisce l'elemento all'inizio della lista */
void list::addFront(Elem e, const List& l) {

  List q = new node;
  q->info = e;

  q->next = l->next;
  q->prev = l;
  l->next = q;
  q->next->prev = q;
}

/* cancella l'elemento in posizione pos dalla lista */
void list::removePos(int pos, const List& l) {
  if (pos >=0 && pos<size(l)){

    node *q = l->next;

    for(int i=0; i<pos; i++)
      q = q->next;

    q->prev->next = q->next;
    q->next->prev = q->prev;

    delete q;
  }
}

 /* cancella tutte le occorrenze dell'elemento elem, se presenti, dalla lista */
void list::removeEl(Elem e, const List& l) {

  node *p = l->next;

  while (p != l) {
    if (p->info == e)
      q = p->next; //SALVO PUNTATORE...MOLTO IMPORTANTE SENNO PERDO POSIZIONE NELLA LISTA

      p->prev->next = q;
      q->prev = p->prev;

      delete p;
    else
      q = q->next;
  }
}

/* restituisce true se la lista e' vuota (ed e' vuota se il next di l, e' l stessa */
bool list::isEmpty(const List& l) {
  return (l->next == l)
}

 /* restituisce la dimensione della lista */
int list::size(const List& l) {

  node *aux = l->next;
  int counter = 0;
  while (aux != l) {
    counter++;
    aux = aux->next;
  }
  return counter;
}
