#ifndef CONTAINER_H
#define CONTAINER_H

template<class T>
class Container
{
private:
    class Nodo{
    public:
        T info;
        Nodo* prev;
        Nodo* next;

        Nodo() : info(new T), prev(nullptr), next(nullptr){}
        Nodo(const T& t, Nodo* p = nullptr, Nodo* n = nullptr) : info(t), prev(p), next(n) {}
        Nodo(const Nodo& t) : info(t.info), prev(t.prev), next(t.next){}
        ~Nodo(){ if(next) delete next; }
    };

    Nodo* first;
    Nodo* last;
    int size;

public:
    Container() : first(nullptr), last(nullptr), size(0){}
    Container(const Container<T>&);
    ~Container() = default;

    Nodo* getNodoFromIndex (const int&) const; //
    Nodo* getNodoFromInfo (const T) const; //
    int getIndex (Nodo*) const; //
    //int getIndex (const T&) const; //useless??

    void pushFront (const T&); //
    void pushBack (const T&); //
    void insert (int, const T&); //
    void remove (Nodo*);
    void remove (const int&);
    void substitute(const T&, const T&);// AGGIUNTO DA GIACOMO
    void swap(const int&, const int&); //
    bool exists (const T&) const;
    int getSize () const{return size;} //
    Nodo* getFirst () const{return first;}
    Nodo* getLast () const{return last;}
    void clear();

    Container<T>& operator= (const Container<T>&);
    Container<T> operator+ (const Container<T>&);
    T& operator[] (const int&) const;
};

template<class T>
Container<T>::Container(const Container<T>& copy_cont){
    first = nullptr;
    last = nullptr;
    size = 0;
    Nodo* aux = copy_cont.first;
    while(size < copy_cont.size){
        this->pushBack(aux->info);
        aux = aux->next;
    }
}

template<class T>
typename Container<T>::Nodo* Container<T>::getNodoFromIndex(const int& index) const { //check if !exists
    Nodo* aux = first;
    for(int i=0; i<size && i<index; ++i){
        aux = aux->next;
    }
    return aux;
}

template<class T>
typename Container<T>::Nodo* Container<T>::getNodoFromInfo(const T toFind) const { //check if !exists
    Nodo* aux = first;
    for(int i=0; i<size && aux->info != toFind; ++i){
        aux = aux->next;
    }
    return aux;
}

template<class T>
int Container<T>::getIndex(Nodo* n) const {
    Nodo* aux = first;
    int count = 0;
    for(int i=0; i<size && aux->info != n->info; ++i){
        ++count;
        aux = aux->next;
    }
    return count;
}

template<class T>
void Container<T>::pushFront(const T& n) {
    if(size == 0){
        first = new Nodo(n);
        first->next = first;
        first->prev = first;
        last = first;
    }else{
        Nodo* aux = first;
        Nodo* temp = new Nodo(n, nullptr, aux);
        first = temp;
        aux->prev = first;
    }

    ++size;
}

template<class T>
void Container<T>::pushBack(const T& n) {
    if(size == 0){
        /*
         * first = new Nodo(n);
         * first->next = first;
         * first->prev = first;
         * last = first;
        */
        this->pushFront(n);
    }else{
        last->next = new Nodo (n, last, nullptr);
        last = last->next;
        ++size;
    }
    //++size;
}

template<class T>
void Container<T>::insert(int i, const T& n){
    if(i == 0){
        pushFront(n);
    }else if(i == size){
        pushBack(n);
    }else{
        ++size;
        Nodo* old_nodo = getNodoFromIndex(i);
        Nodo* new_nodo = new Nodo(n, old_nodo->prev, old_nodo);
        old_nodo->prev->next = new_nodo;
        old_nodo->prev = new_nodo;
    }
}

template<class T>
void Container<T>::remove(Nodo* n) {
    Nodo* temp = first;
    int pos = 0;
    for(pos=0; pos<size && temp!=n; ++pos){
        temp = temp->next;
    }
    remove(pos);
}

template<class T>
void Container<T>::remove(const int& pos) {
    Nodo* to_remove = nullptr;
    if(pos == 0){
        to_remove = first;
        if(size == 1){
            first = nullptr;
            last = nullptr;
        }else{
            first = to_remove->next;
            first->prev = nullptr;
        }
    }else if(pos == size-1){
        to_remove = last;
        last = to_remove->prev;
        last->next = nullptr;
    }else{
        to_remove = getNodoFromIndex(pos);
        to_remove->prev->next = to_remove->next;
        to_remove->next->prev = to_remove->prev;
    }
    to_remove->prev = nullptr;
    to_remove->next = nullptr;
    delete to_remove;
    --size;
}

template<class T>
void Container<T>::substitute(const T& tbs, const T& tsw) {
    Nodo* to_sub = this->getNodoFromInfo(tbs);
    delete to_sub->info;
    to_sub->info = tsw;
    return;
} // AGGIUNTO DA GIACOMO

template<class T>
void Container<T>::swap (const int& f, const int& s) {
    T fn = (getNodoFromIndex(f))->info;
    T sn = (getNodoFromIndex(s))->info;

    remove(f);
    insert(f, sn);
    remove(s);
    insert(s, fn);
}

template<class T>
bool Container<T>::exists(const T& n) const {
    Nodo* aux = first;
        for(int i=0; i<size; ++i){
            if(aux->info == n)
                return true;
            aux = aux->next;
        }
        return false;
}

template<class T>
void Container<T>::clear(){
    while (size>0) {
        remove(size-1);
    }
}

template<class T>
Container<T>& Container<T>::operator= (const Container<T>& copy_cont) {
    this->clear(); //first = next = prev = nullptr!
    if(copy_cont.first){
        first = new Nodo(copy_cont.first->info);
        ++size;
        Nodo* aux = copy_cont.first->next;
        Nodo* aux_this = first;
        while (size < copy_cont.size) {
            aux_this->next = new Nodo(aux->info, aux_this, nullptr);
            ++size;
            aux = aux->next;
            aux_this = aux_this->next;
        }
        last = aux_this;
    }
    return *this;
}

template<class T>
Container<T> Container<T>::operator+ (const Container<T>& cont) {
    Container<T>* aux = new Container<T>(*this);
    Nodo* aux2 = cont.first;
    for(int i=0; i<cont.size; ++i){
        (*aux).pushBack(aux2->info);
        aux2 = aux2->next;
    }
    /*size += cont.size;
    last->next = cont.first;
    last = cont.last;*/
    return *aux;
}

template<class T>
T& Container<T>::operator[] (const int& pos) const {
    return (getNodoFromIndex(pos))->info;
}

#endif // CONTAINER_H
