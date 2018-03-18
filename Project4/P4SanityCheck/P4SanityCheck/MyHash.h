// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

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
    const ValueType* find(const KeyType& key) const;
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
};

// The constructor must initialize your hash table, setting the size of its initial dynamic array to 100 buckets
template<typename KeyType, typename ValueType>
inline
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
:m_numBuckets(100), m_numItems(0)
{
    if(maxLoadFactor <= 0.0)
        m_loadfactor = 0.5;
    else if(maxLoadFactor > 2.0)
        m_loadfactor = 2.0;
    else
        m_loadfactor = maxLoadFactor;
    table = new Bucket* [m_numBuckets];
    for(int i = 0; i < m_numBuckets; i++)
        table[i] = nullptr;
}

// free all memory associated with hash table
template<typename KeyType, typename ValueType>
inline
MyHash<KeyType, ValueType>::~MyHash()
{
    // delete current hash table
    for(int i = 0; i < m_numBuckets; i++)
    {
        if(table != nullptr)
        {
            Bucket* currBucket = table[i];
            while(currBucket != nullptr)
            {
                table[i] = currBucket->m_next;
                delete currBucket;
                currBucket = nullptr;
                currBucket = table[i];
            }
        }
        delete[] table;
        table = nullptr;
    }
}

// must free all of the memory associated with the current hash table, then allocate a new empty hash table of the default size of 100 buckets
template<typename KeyType, typename ValueType>
inline
void MyHash<KeyType, ValueType>::reset()
{
    if(table == nullptr)
        return;
    // destruct
    for (int i=0; i < m_numBuckets; i++)
    {
        if (table[i] != nullptr)
        {
            Bucket* currBucket = table[i];
            while(currBucket != nullptr)
            {
                table[i] = currBucket->m_next;
                delete currBucket;
                currBucket = table[i];
            }
        }
    }
    delete [] table;
    // construct
    m_numBuckets = 100;
    m_numItems = 0;
    table = new Bucket* [m_numBuckets];
    for (int i = 0; i < m_numBuckets; i++)
        table[i] = nullptr;
}

template<typename KeyType, typename ValueType>
inline
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    ValueType* vptr = find(key);
    if(vptr != nullptr)
        *vptr = value;
    else
        insert(key, value);
    // if too many items affect efficiency, resize the hash table
    if((double)m_numItems/(double)m_numBuckets >= m_loadfactor)
        doubleSize();
}

template<typename KeyType, typename ValueType>
inline
int MyHash<KeyType, ValueType>::getNumItems() const
{
    return m_numItems;
}

template<typename KeyType, typename ValueType>
inline
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
    return (double)m_numItems/(double)m_numBuckets;
}

// Transform the values returned by the hash functions in WordList.cpp to produce a bucket number within the range of your array. p.17
template<typename KeyType, typename ValueType>
inline
unsigned int MyHash<KeyType, ValueType>::getBucketNumber(const KeyType& key) const
{
    unsigned int hash(const KeyType& k); // prototype
    unsigned int h = hash(key);
    return (h % m_numBuckets);
}

template<typename KeyType, typename ValueType>
inline
void MyHash<KeyType, ValueType>::doubleSize()
{
    // make new hash table
    int prev_numBuckets = m_numBuckets;
    m_numBuckets = m_numBuckets * 2;
    Bucket** prevTable = table;
    table = new Bucket*[m_numBuckets];
    m_numItems = 0;
    for(int i = 0; i < m_numBuckets; i++)
        table[i] = nullptr;
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
                prevBucket = currBucket;
                currBucket = currBucket->m_next;
                delete prevBucket;
            }
        }
    }
    delete[] prevTable;
}

template<typename KeyType, typename ValueType>
inline
void MyHash<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
    // get the bucket number of where to insert
    unsigned int index = getBucketNumber(key);
    Bucket* newBucket = new Bucket;
    newBucket->m_key = key;
    newBucket->m_value = value;
    newBucket->m_next = nullptr;
    if (table[index] == nullptr)
    {
        table[index] = newBucket;
        m_numItems++;
    }
    else
    {
        Bucket* currBucket = table[index];
        newBucket->m_next = currBucket;
        table[index] = newBucket;
        m_numItems++;
    }
}

template<typename KeyType, typename ValueType>
inline
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
    unsigned int index = getBucketNumber(key);
    Bucket* currBucket = table[index];
    while (currBucket != nullptr)
    {
        if (currBucket->m_key == key)
        {
            ValueType* value = &(currBucket->m_value);
            if(value != nullptr)
                return value;
        }
        currBucket = currBucket->m_next;
    }
    return nullptr;
}

#endif // MYHASH_INCLUDED


