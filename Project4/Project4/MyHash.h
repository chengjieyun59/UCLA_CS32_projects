// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    // The constructor must initialize your hash table, setting the size of its initial dynamic array to 100 buckets
    MyHash(double maxLoadFactor = 0.5)
    :m_size(100), m_numItems(0)
    {
        if(maxLoadFactor <= 0.0)
            m_loadfactor = 0.5;
        if(maxLoadFactor > 2.0)
            m_loadfactor = 2.0;
        for(int i = 0; i < m_size; i++)
        {
            HashTable[i] = new item;
            // HashTable[i]->name = "empty";
            HashTable[i]->next = NULL;
        }
    }
    
    // free all memory associated with hash table
    ~MyHash()
    {
        for(int i = 0; i < m_size; i++)
        {
            delete HashTable[i];
        }
    }
    
    // must free all of the memory associated with the current hash table, then allocate a new empty hash table of the default size of 100 buckets. The maximum load factor is unchanged. This method must run in O(B) time where B is the number of buckets in the table to be reset.
    void reset()
    {
        ~MyHash();
        MyHash(0.5);
    }
    
    // TODO: transform the values returned by the hash functions in WordList.cpp to produce a bucket number within the range of your array. p.17
    void associate(const KeyType& key, const ValueType& value)
    {
        
    }
    
    int getNumItems() const
    {
        return m_numItems;
    }
    double getLoadFactor() const
    {
        return m_loadfactor;
    }
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const
    {
        return <ValueType*>(<const MyHash*>(this)->find(key));
    }
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
    
private:
    unsigned int getBucketNumber(const KeyType& key) const {
        unsigned int hash(const KeyType& k); // prototype
        unsigned int h = hash(key);
        // TODO: ...
    }
    int m_size;
    int m_numItems;
    double m_loadfactor;
    item* HashTable[m_size];
};

// TODO: You must put these implementations in one of your .cpp files, not in MyHash.h. It will simplify our grading scripts if, when you turn in your project, the .cpp file you put the hash() implementations in is WordList.cpp.

