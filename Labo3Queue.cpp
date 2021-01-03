#include "queueASD-array.h"

using namespace queue;


/****************************************************************/
/* 			FUNZIONI SULLE CODE 			*/
/****************************************************************/

/****************************************************************/
Queue queue::createEmpty()
{
   Queue q;
   q.size = 0;
   q.maxsize = BLOCKDIM;
   Elem* aux = new Elem[BLOCKDIM];
   q.queue = aux;
   return q;
}

/****************************************************************/
void queue::enqueue(Elem e, Queue& l) // aggiunge e in coda
{
  if (pos < 0 || pos > l.size) {
    cout<<"Posizione invalida";
    return;
  }

  if (l.size == l.maxsize) {
    l.maxsize = l.maxsize + BLOCKDIM;
    Elem* aux = new Elem[BLOCKDIM];
    q.size++;
    for(int i=0; i<pos; i++)            //copio prima parte
      aux[i] = l.queue[i];

    aux[pos] = e;                       //e in pos

    for(int i=pos+1; i<l.size; i++)     //copio la seconda parte
      aux[i] = l.queue[i-1];            // IMPORTANTE mettere "l.queue[i-1]"

    delete l.queue;                     //cancello vecchio array
    l.queue = aux;                      //assegno a q.queue nuovo array
  }

  l.size++;
  for (int i=l.size-1; i>pos; i++)
    l.queue[i] = l.queue[i+1];
  l.queue[pos] = e;

  return;
}


/****************************************************************/
Elem queue::dequeue(Queue& l) // rimuove il primo elemento e lo restituisce
{
  int deletedElem = l.queue[0];

  l.size--;
  Elem* aux = new Elem[l.maxsize];

  for (int i=1; i<l.size; i++)
    aux[i-1] = l.queue[i];

  delete l.queue;
  l.queue = aux;

  return deletedElem;

}


/****************************************************************/
Elem queue::first(Queue& l) // restituisce il primo elemento
{
   return l.queue[0];
}


/****************************************************************/
bool queue::isEmpty(const Queue& l)
{
   return (l.size == 0);
}



/****************************************************************/
Queue readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    return readFromStream(ifs);
}


/****************************************************************/
Queue readFromStdin()
{
    cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
    return readFromStream((std::cin));
}


/****************************************************************/
Queue readFromStream(istream& str)
{
    Queue l = createEmpty();
    int dato;
    str>>dato;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (dato!= FINEINPUT)  // assumiamo che il segnale di fine input nel file sia  FINEINPUT
        {
        enqueue(dato, l);   // aggiunge l'elemento alla fine della coda
        str>>dato;
        if (!str) throw runtime_error("Errore inserimento dati\n");
        }
return l;
}

/****************************************************************/
void print(const Queue& l)
{
cout << endl;
for (int i=0; i<l.size; ++i)
   cout << l.queue[i] << "; ";
cout << endl;
}
