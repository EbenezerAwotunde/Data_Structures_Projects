#include <cstddef>    // size_t
#include <functional> // std::hash
#include <ios>
#include <utility>    // std::pair
#include <iostream>

#include "primes.h"



template <typename Key, typename T, typename Hash = std::hash<Key>, typename Pred = std::equal_to<Key>>
class UnorderedMap {
    public:

    using key_type = Key;
    using mapped_type = T;
    using const_mapped_type = const T;
    using hasher = Hash;
    using key_equal = Pred;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    private:

    struct HashNode {
        HashNode *next;
        value_type val;

        HashNode(HashNode *next = nullptr) : next{next} {}
        HashNode(const value_type & val, HashNode * next = nullptr) : next { next }, val { val } { }
        HashNode(value_type && val, HashNode * next = nullptr) : next { next }, val { std::move(val) } { }
    };

    size_type _bucket_count;
    HashNode **_buckets;

    HashNode * _head;
    size_type _size;

    Hash _hash;
    key_equal _equal;

    HashNode* get_Head(){
        HashNode * head = nullptr;

        for(size_t index = 0; index < _bucket_count; index++){
            if(_buckets[index] != nullptr){
                head = _buckets[index];
                break;
            }
        }

        return head;
    }

    static size_type _range_hash(size_type hash_code, size_type bucket_count) {
        return hash_code % bucket_count;
    }

    public:

    template <typename pointer_type, typename reference_type, typename _value_type>
    class basic_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = _value_type;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        friend class UnorderedMap<Key, T, Hash, key_equal>;
        using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

        const UnorderedMap * _map;
        HashNode * _ptr;

        explicit basic_iterator(UnorderedMap const * map, HashNode *ptr) noexcept 
        { 
            /* TODO */ 
            _map = map;
            _ptr = ptr;
        }

    public:
        basic_iterator() 
        { 
            /* TODO */ 
            _map = nullptr;
            _ptr = nullptr;
        };

        basic_iterator(const basic_iterator &) = default;
        basic_iterator(basic_iterator &&) = default;
        ~basic_iterator() = default;
        basic_iterator &operator=(const basic_iterator &) = default;
        basic_iterator &operator=(basic_iterator &&) = default;
        reference operator*() const 
        { 
            /* TODO */ 
            return  _ptr->val;
        }
        pointer operator->() const 
        { 
            /* TODO */ 
            return &(_ptr->val);
        }
        basic_iterator &operator++() 
        { 
            /* TODO */ 
            if (_ptr->next != nullptr)
            {
                _ptr = _ptr->next;
                return *this;
            }
            else
            {
                size_type x = _map->_bucket(_ptr->val) + 1;
                for(size_type i = x; i < _map->_bucket_count;i++)
                {
                    if (_map->_buckets[i] != nullptr)
                    {
                        _ptr = _map->_buckets[i];
                        return *this;
                    }
                    
                }
            }
            _ptr = nullptr;
            return *this;
        }
        basic_iterator operator++(int) 
        { 
            /* TODO */ 
            basic_iterator copy = *this;
            operator++();
            return copy;
        }
        bool operator==(const basic_iterator &other) const noexcept 
        { 
            /* TODO */ 
            return this->_ptr == other._ptr;
        }
        bool operator!=(const basic_iterator &other) const noexcept 
        { 
            /* TODO */ 
            return this->_ptr != other._ptr;
        }
    };

    using iterator = basic_iterator<pointer, reference, value_type>;
    using const_iterator = basic_iterator<const_pointer, const_reference, const value_type>;

    class local_iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = std::pair<const key_type, mapped_type>;
            using difference_type = ptrdiff_t;
            using pointer = value_type *;
            using reference = value_type &;

        private:
            friend class UnorderedMap<Key, T, Hash, key_equal>;
            using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

            HashNode * _node;

            explicit local_iterator( HashNode * node ) noexcept 
            { 
                /* TODO */ 
                _node = node;
            }

        public:
            local_iterator() 
            { 
                /* TODO */ 
                _node = nullptr;
            }

            local_iterator(const local_iterator &) = default;
            local_iterator(local_iterator &&) = default;
            ~local_iterator() = default;
            local_iterator &operator=(const local_iterator &) = default;
            local_iterator &operator=(local_iterator &&) = default;
            reference operator*() const 
            { 
                /* TODO */ 
                return  _node->val;
            }
            pointer operator->() const 
            { 
                /* TODO */
                return &(_node->val); 
            }
            local_iterator & operator++()
            { 
                /* TODO */ 
                _node = _node->next;
			    return *this;
            }
            local_iterator operator++(int) 
            { 
                /* TODO */ 
                local_iterator copy(*this);
                _node = _node->next; 
                return copy;
            }

            bool operator==(const local_iterator &other) const noexcept 
            { 
                /* TODO */ 
                return this->_node == other._node;
            }
            bool operator!=(const local_iterator &other) const noexcept 
            { 
                /* TODO */ 
                return this->_node != other._node;
            }
    };

private:

    size_type _bucket(size_t code) const 
    { 
        /* TODO */ 
        return _range_hash(code, _bucket_count);
    }
    size_type _bucket(const Key & key) const 
    { 
        /* TODO */ 
        return _range_hash(_hash(key), _bucket_count);
    }
    size_type _bucket(const value_type & val) const 
    { 
        /* TODO */ 
        return _range_hash(_hash(val.first), _bucket_count);
    }

    HashNode*& _find(size_type code, size_type bucket, const Key & key) 
    { 
        HashNode** temp = &_buckets[bucket];
        while (*temp != nullptr) {
            if (_equal((*temp)->val.first, key)) {
                return *temp;
            }
            temp = &((*temp)->next);
        }
        return *temp;
    }

    HashNode*& _find(const Key & key) 
    { 
        return _find(_hash(key), _bucket(key), key);
    }

    HashNode * _insert_into_bucket(size_type bucket, value_type && value) 
    { 
        HashNode*& temp = _buckets[bucket];
        HashNode* newNode = new HashNode(std::move(value), temp);
        temp = newNode;

        if (!_head || _bucket(_head->val.first) >= bucket) {
            _head = newNode;
        }

        ++_size;
        return newNode;
    }

    void _move_content(UnorderedMap & src, UnorderedMap & dst) { /* TODO */ }

public:
    explicit UnorderedMap(size_type bucket_count, const Hash & hash = Hash { },
                const key_equal & equal = key_equal { }) 
    { 
                _bucket_count = next_greater_prime(bucket_count);
                _hash = hash;
                _equal = equal;
                _buckets = new HashNode*[_bucket_count] {};
                _size = 0;
                _head = nullptr;
        /* TODO */ 
    }

    ~UnorderedMap()
    { 
        /* TODO */ 
        clear();
        _bucket_count = 0;
        delete [] _buckets;
    }

    UnorderedMap(const UnorderedMap & other): _buckets{} 
    {
        operator=(other);
    }

    UnorderedMap(UnorderedMap && other) noexcept
    : _head(std::exchange(other._head, nullptr)),
      _hash(std::move(other._hash)),
      _equal(std::move(other._equal)),
      _size(std::exchange(other._size, 0)),
      _buckets(std::exchange(other._buckets, new HashNode* [other._bucket_count] {})),
      _bucket_count(other._bucket_count)
    {
       
    }

    UnorderedMap & operator=(const UnorderedMap & other) 
    { 
        if (this == &other)
            return *this;

        if (_buckets != nullptr) {
            clear();
            delete[] _buckets;
        }

        _bucket_count = next_greater_prime(other._bucket_count);
        _buckets = new HashNode*[_bucket_count]{};

        for (size_type i = 0; i < _bucket_count; ++i) {
            HashNode* ptr = other._buckets[i];
            while (ptr != nullptr) {
                _buckets[i] = new HashNode(ptr->val, _buckets[i]);
                ptr = ptr->next;
            }
        }

        _head = get_Head();

        _size = other._size;
        _equal = other._equal;
        _hash = other._hash;

        return *this;        
    }

    UnorderedMap & operator=(UnorderedMap && other) 
    { 
       if (this != &other) 
        {
            clear(); // Clear the current map
            delete[] _buckets; // Deallocate the current bucket array

            // Copy members from 'other' to the current object
            _head = other._head;
            _hash = other._hash;
            _equal = other._equal;
            _size = other._size;
            _buckets = other._buckets;
            _bucket_count = other._bucket_count;

            // Reset 'other' to a "null" state
            other._buckets = new HashNode*[_bucket_count] {}; // Allocate new bucket array
            other._size = 0;
            other._head = nullptr;
        }

        return *this;
    }

    void clear() noexcept 
    { 
        for (size_type i = 0; i < _bucket_count; ++i) 
        {
            while (_buckets[i] != nullptr) {
                auto delNode = _buckets[i];
                _buckets[i] = _buckets[i]->next;
                delete delNode;
            }
            _buckets[i] = nullptr;
        }
        _head = nullptr;
        _size = 0;
    }

    size_type size() const noexcept 
    {
        return _size;
    }

    bool empty() const noexcept 
    { 
        return _size == 0; 
    }

    size_type bucket_count() const noexcept 
    { 
        /* TODO */ 
        return _bucket_count;
    }

    iterator begin() 
    {
        /* TODO */ 
        if (_size == 0)
        {
            return end();
        }
        return iterator(this, _head->next);
    }
    iterator end() 
    { 
        /* TODO */ 
        return iterator(this, nullptr);
    }

    const_iterator cbegin() const 
    { 
        /* TODO */ 
        if (_size == 0)
        {
            return cend();
        }
        return const_iterator(this, _head->next);;
    };
    const_iterator cend() const 
    { 
        /* TODO */ 
        return const_iterator(this, nullptr);
    };

    local_iterator begin(size_type n) 
    { 
        /* TODO */ 
        return local_iterator(_buckets[n]);
    }
    local_iterator end(size_type n) 
    { 
        /* TODO */ 
        return local_iterator(nullptr);
    }

    size_type bucket_size(size_type n) 
    { 
        auto curr = _buckets[n];
        size_type bucketSize = 0;

        while (curr != nullptr) {
            ++bucketSize;
            curr = curr->next;
        }

        return bucketSize;
    }

    float load_factor() const 
    { 
        return static_cast<float>(_size) / _bucket_count;
    }

    size_type bucket(const Key & key) const 
    { 
        /* TODO */
        _bucket(key);
    }

    std::pair<iterator, bool> insert(value_type && value) 
    {
        if (_find(value.first)) {
            return std::make_pair(find(value.first), false);
        }
        
        size_type index = _bucket(value.first);
        HashNode* newNode = _insert_into_bucket(index, std::move(value));
        return std::make_pair(iterator(this, newNode), true);
    }

    std::pair<iterator, bool> insert(const value_type & value) 
    { 
        if (_find(value.first)) {
            return std::make_pair(find(value.first), false);
        }
        size_type index = _bucket(value.first);
        value_type copyVal = value;
        HashNode* newNode = _insert_into_bucket(index, std::move(copyVal));
        return std::make_pair(iterator(this, newNode), true);
    }

    iterator find(const Key & key) 
    {
        return iterator(this, _find(key));
    }

    T& operator[](const Key & key) 
    {
       HashNode* found = _find(key);
        if (found != nullptr) {
        return found->val.second;
        }

        value_type newValue(key, T());
        iterator curr = insert(std::move(newValue)).first;
        return curr->second;
    }

    iterator erase(iterator pos) 
    {
        HashNode*& found = _find((*pos).first);

        if (found != nullptr) 
        {
            iterator curr(this, found);
            ++curr;

            if (found == _head) {
                _head = curr._ptr;
            }

            auto delNode = found;
            found = found->next;
            delete delNode;
            --_size;

            return curr;
        }

        return end();
    }

    size_type erase(const Key & key) 
    {
        HashNode* found = _find(key);
        if (found != nullptr) 
        {
            iterator curr(this, found);
            erase(curr);
            return 1;
        }
        return 0;
    }

    template<typename KK, typename VV>
    friend void print_map(const UnorderedMap<KK, VV> & map, std::ostream & os);
};

template<typename K, typename V>
void print_map(const UnorderedMap<K, V> & map, std::ostream & os = std::cout) {
    using size_type = typename UnorderedMap<K, V>::size_type;
    using HashNode = typename UnorderedMap<K, V>::HashNode;

    for(size_type bucket = 0; bucket < map.bucket_count(); bucket++) {
        os << bucket << ": ";

        HashNode const * node = map._buckets[bucket];

        while(node) {
            os << "(" << node->val.first << ", " << node->val.second << ") ";
            node = node->next;
        }

        os << std::endl;
    }
}
