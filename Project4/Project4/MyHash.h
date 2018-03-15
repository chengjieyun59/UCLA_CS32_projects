// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

// TODO: You must put these implementations in one of your .cpp files, not in MyHash.h. It will simplify our grading scripts if, when you turn in your project, the .cpp file you put the hash() implementations in is WordList.cpp.

#ifndef MYHASH_INCLUDED
#define MYHASH_INCLUDED
// open hash table: each array bucket points to a linked list of key-value pairs
template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    
    const ValueType* find(const KeyType& key) const
    {
        int index = getBucketNumber(key);
        Bucket* currBucket = table[index];
        while(currBucket->m_next != nullptr)
        {
            if(currBucket->m_key == key)
                return &(currBucket->m_value);
        }
        return nullptr;
    }
    
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }
    
    int getNumItems() const;
    double getLoadFactor() const;
    // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash<KeyType, ValueType>&) = delete;
    MyHash<KeyType, ValueType>& operator=(const MyHash<KeyType, ValueType>&) = delete;

private:
    unsigned int getBucketNumber(const KeyType& key) const;
    void doubleSize();
    void insert(const KeyType& key, const ValueType& value);
    
    // similar to project 2, map.h and map.cpp
    struct Bucket
    {
        KeyType m_key;
        ValueType m_value;
        Bucket* m_next;
    };
    
    Bucket** table;
    
    double m_loadfactor;
    int m_numBuckets;
    int m_numItems;
    // Bucket m_buckets[m_numBuckets];
};

// The constructor must initialize your hash table, setting the size of its initial dynamic array to 100 buckets
template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
:m_numBuckets(100), m_numItems(0)
{
    if(maxLoadFactor <= 0.0)
        m_loadfactor = 0.5;
    if(maxLoadFactor > 2.0)
        m_loadfactor = 2.0;
    
    table = new Bucket* [m_numBuckets];
    for(int i = 0; i < m_numBuckets; i++)
    {
        table[i] = nullptr;
        // m_buckets[i] = new item;
        // m_buckets[i]->key = "empty";
        // m_buckets[i].used = false;
    }
}

// free all memory associated with hash table
template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash()
{
    for(int i = 0; i < m_numBuckets; i++)
    {
        // delete m_buckets[i];
        if(table[i] != nullptr)
        {
            Bucket* prevBucket = nullptr;
            Bucket* currBucket = table[i];
            while(currBucket != nullptr)
            {
                prevBucket = currBucket;
                currBucket = currBucket->m_next;
                delete prevBucket;
            }
        }
        delete[] table;
    }
}
    
// must free all of the memory associated with the current hash table, then allocate a new empty hash table of the default size of 100 buckets
template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
    double temp_loadfactor = getLoadFactor();
    
    // delete current hash table
    for(int i = 0; i < m_numBuckets; i++)
    {
        // delete m_buckets[i];
        if(table[i] != nullptr)
        {
            Bucket* prevBucket = nullptr;
            Bucket* currBucket = table[i];
            while(currBucket != nullptr)
            {
                prevBucket = currBucket;
                currBucket = currBucket->m_next;
                delete prevBucket;
            }
        }
        delete[] table;
    }
    
    // allocate a new empty hash table of default size of 100 buckets
    m_numBuckets = 100;
    m_numItems = 0;
    m_loadfactor = temp_loadfactor;
    
    table = new Bucket* [m_numBuckets];
    for(int i = 0; i < m_numBuckets; i++)
    {
        table[i] = nullptr;
    }
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    insert(key, value);
    // if too many items affect efficiency, resize the hash table
    if(m_numItems/m_numBuckets > m_loadfactor)
        doubleSize();
}

template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const
{
    return m_numItems;
}

template<typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
    return m_loadfactor;
}

// Transform the values returned by the hash functions in WordList.cpp to produce a bucket number within the range of your array. p.17
template<typename KeyType, typename ValueType>
unsigned int MyHash<KeyType, ValueType>::getBucketNumber(const KeyType& key) const
{
    unsigned int hash(const KeyType& k); // prototype
    unsigned int h = hash(key);
    return (h % m_numBuckets);
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::doubleSize()
{
    // prepare
    int prev_numBuckets = m_numBuckets;
    m_numBuckets = m_numBuckets * 2;
    m_loadfactor = m_loadfactor/2;
    
    // make new hash table
    Bucket** prevTable = table;
    table = new Bucket*[m_numBuckets];
    m_numItems = 0;
    for(int i = 0; i < m_numBuckets; i++)
    {
        table[i] = nullptr;
    }
    
    // delete the previous hash table
    for(int i = 0; i < prev_numBuckets; i++)
    {
        if(prevTable[i] != nullptr)
        {
            Bucket* prevBucket;
            Bucket* currBucket = prevTable[i];
            while(currBucket != nullptr)
            {
                // move all of the items from the old array to the new array
                insert(currBucket->m_key, currBucket->m_value);
                // iterate
                prevBucket = currBucket;
                currBucket = currBucket->m_next;
                delete prevBucket;
            }
        }
        delete[] prevTable;
    }
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
    // get the bucket number of where to insert
    int index = getBucketNumber(key);
    // if there's an empty slot/ bucket
    if(table[index] == nullptr)
    {
        table[index] = new Bucket;
        table[index]->m_key = key;
        table[index]->m_value = value;
        m_numItems++;
    }
    // if the bucket isn't empty, keep traversing down the linked list
    else
    {
        Bucket* currBucket = table[index];
        while(currBucket->m_next != nullptr)
        {
            if(currBucket->m_key == key)
            {
                currBucket->m_value = value; // replace the value if same key is found
            }
            currBucket = currBucket->m_next;
        }
        table[index] = new Bucket;
        table[index]->m_key = key;
        table[index]->m_value = value;
        m_numItems++;
    }
}

// for a map that can't be modified, return a pointer to const ValueType
/*
template<typename KeyType, typename ValueType>
typename MyHash<KeyType, ValueType>::ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
    Bucket* currBucket = table[index];
    while(currBucket->m_next != nullptr)
    {
        if(currBucket->m_key == key)
            return &(currBucket->m_value);
    }
    return nullptr;
}

// for a modifiable map, return a pointer to modifiable ValueType
template<typename KeyType, typename ValueType>
typename MyHash<KeyType, ValueType>::ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key)
{
    return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
}
*/

#endif // MYHASH_INCLUDED
