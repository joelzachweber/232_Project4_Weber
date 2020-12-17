#ifndef TABLE_T	
#define TABLE_T



template<class Key, typename T>
void Table<Key, T>::print()
{
    for (int i = 0; i < tableSize; i++)
        cout << the_table[i].first.first << "      " << the_table[i].first.second << "      " << the_table[i].second << "\n";
}

template<class Key, typename T>
Table<Key, T>::Table(int n, int(*map)(Key k))
{
    Mapping = map;
    tableSize = n;
    the_table = new Pair<Key, T>[tableSize];
  //  for (int i = 0; i < tableSize; i++)
  //      the_table[i] = Pair<Key, T>();
}

template<class Key, typename T>      //INT CHAR
inline bool Table<Key, T>::insert(Pair<Key, T> kvpair)
{
    if (Mapping(kvpair.first) < 0 || Mapping(kvpair.first) >= tableSize) // If out of bounds
        return false;
    else the_table[Mapping(kvpair.first)] = kvpair;
    return true;
}

template<class Key, typename T>
bool Table<Key, T>::remove(const Key aKey)
{
    if (Mapping(aKey) < 0 || Mapping(aKey) >= tableSize) // If out of bounds
        return false;
    else the_table[Mapping(aKey)] = Pair<Key, T>();
        return true;
}

template<class Key, typename T>
T Table<Key, T>::lookUp(const Key aKey)
{
    Mapping(aKey);          //Returns the index of the pair
    if (Mapping(aKey) < 0 || Mapping(aKey) >= tableSize) // If out of bounds
        return T();
    else 
        return the_table[Mapping(aKey)].second;

}



#endif