// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

// open hash table: each array bucket points to a linked list of key-value pairs
template<typename KeyType, typename ValueType>
class MyHash
{
public:
    // The constructor must initialize your hash table, setting the size of its initial dynamic array to 100 buckets
    MyHash(double maxLoadFactor = 0.5)
    :m_numBuckets(100), m_numItems(0)
    {
        if(maxLoadFactor <= 0.0)
            m_loadfactor = 0.5;
        if(maxLoadFactor > 2.0)
            m_loadfactor = 2.0;
        
        table = new Bucket* [m_numBuckets];
        for(int i = 0; i < m_numBuckets; i++)
        {
            table[i] = NULL;
            // m_buckets[i] = new item;
            // m_buckets[i]->key = "empty";
            // m_buckets[i].used = false;
        }
    }
    
    // free all memory associated with hash table
    ~MyHash()
    {
        for(int i = 0; i < m_numBuckets; i++)
        {
            // delete m_buckets[i];
            if(table[i] != NULL)
            {
                Bucket* prevBucket = NULL;
                Bucket* currBucket = table[i];
                while(currBucket != NULL)
                {
                    prevBucket = currBucket;
                    currBucket = currBucket->m_next;
                    delete prevBucket;
                }
            }
            delete[] table;
        }
    }
    
    // must free all of the memory associated with the current hash table, then allocate a new empty hash table of the default size of 100 buckets. The maximum load factor is unchanged. This method must run in O(B) time where B is the number of buckets in the table to be reset.
    void reset()
    {
        double temp_loadfactor = getLoadFactor();
        ~MyHash();
        MyHash(temp_loadfactor);
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
        return (h % m_numBuckets);
    }
    
    void doubleSize()
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
            table[i] = NULL;
        }
        
        // delete the previous hash table
        for(int i = 0; i < prev_numBuckets; i++)
        {
            if(prevTable[i] != NULL)
            {
                Bucket* prevBucket;
                Bucket* currBucket = prevTable[i];
                while(currBucket != NULL)
                {
                    // TODO: insert the key and values
                    prevBucket = currBucket;
                    currBucket = currBucket->m_next;
                    delete prevBucket;
                }
            }
            delete[] prevTable;
        }
    }
    
    void insert(const KeyType& key, const ValueType& value)
    {
        // get the bucket number of where to insert
        int index = getBucketNumber(key);
        // if there's an empty slot/ bucket
        if(table[index] == NULL)
        {
            table[index] = new Bucket(key, value);
            m_numItems++;
        }
        // if the bucket isn't empty, keep traversing down the linked list
        else
        {
            Bucket* currBucket = table[index];
            while(currBucket->m_next != NULL)
            {
                if(currBucket->m_key == key)
                {
                    currBucket->m_value = value; // replace the value if same key is found
                }
                currBucket = currBucket->m_next;
            }
            table[index] = new Bucket(key, value);
            m_numItems++;
        }
        // if too many items affect efficiency, resize the hash table
        if(m_numItems/m_numBuckets > m_loadfactor)
            doubleSize();
    }
    
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

// TODO: You must put these implementations in one of your .cpp files, not in MyHash.h. It will simplify our grading scripts if, when you turn in your project, the .cpp file you put the hash() implementations in is WordList.cpp.


