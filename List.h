#pragma once

#include <cstddef> // size_t
#include <iterator> // std::bidirectional_iterator_tag
#include <type_traits> // std::is_same, std::enable_if

template <class T>
class List {
    private:
    struct Node {
        Node *next, *prev;
        T data;
        explicit Node(Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev} {}
        explicit Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{data} {}
        explicit Node(T&& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{std::move(data)} {}
    };

    template <typename pointer_type, typename reference_type>
    class basic_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = pointer_type;
        using reference         = reference_type;
    private:
        friend class List<value_type>;
        using Node = typename List<value_type>::Node;

        Node* node;

        explicit basic_iterator(Node* ptr) noexcept : node{ptr} {}
        explicit basic_iterator(const Node* ptr) noexcept : node{const_cast<Node*>(ptr)} {}

    public:
        basic_iterator()
        {
            /* TODO */ 
            node = nullptr;
        };
        basic_iterator(const basic_iterator&) = default;
        basic_iterator(basic_iterator&&) = default;
        ~basic_iterator() = default;
        basic_iterator& operator=(const basic_iterator&) = default;
        basic_iterator& operator=(basic_iterator&&) = default;

        reference operator*() const {
            // TODO
            return node->data;
        }
        pointer operator->() const {
            // TODO
            return &(node->data);
        }

        // Prefix Increment: ++a
        basic_iterator& operator++() {
            // TODO
            node = node->next;
			return *this;
        }
        // Postfix Increment: a++
        basic_iterator operator++(int) {
            // TODO
            basic_iterator copy(*this);
            node = node->next; 
            return copy;
        }
        // Prefix Decrement: --a
        basic_iterator& operator--() {
            // TODO
            node = node->prev;
			return *this;
        }
        // Postfix Decrement: a--
        basic_iterator operator--(int) {
            // TODO
            basic_iterator copy(*this);
            node = node->prev; 
            return copy;
        }

        bool operator==(const basic_iterator& other) const noexcept {
            // TODO
            return this->node == other.node;
        }
        bool operator!=(const basic_iterator& other) const noexcept {
            // TODO
            return this->node != other.node;
        }
    };

public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = basic_iterator<pointer, reference>;
    using const_iterator  = basic_iterator<const_pointer, const_reference>;

private:
    Node head, tail;
    size_type _size;

public:
    List() {
        // TODO - Don't forget to initialize the list beforehand
        _size = 0; 
        head.next = &tail;
        head.prev = nullptr;
        tail.prev = &head;
        tail.next = nullptr;
    }
    List( size_type count, const T& value ) {
        // TODO - Don't forget initialize the list beforehand
        head.next = &tail;
        tail.prev = &head;
        for (size_t i = 0; i < count; i++)
        {
            push_back(value);
        }
        _size = count;
    }
    explicit List( size_type count ) {
        // TODO - Don't forget initialize the list beforehand
        _size = 0;
        head.next = &tail;
        tail.prev = &head;
        for (size_t i = 0; i < count; i++)
        {
            push_back(T());
        }
        _size = count;
    }
    //Copy Constructor
    List( const List& other ) {
        // TODO - Don't forget initialize the list beforehand
        head.next = &tail;
        tail.prev = &head;
        _size = 0;
        for (basic_iterator it = other.begin(); it != other.end(); it++)
        {
            push_back(*it);
        }
        _size = other._size;
    }
    // Move Constructor
    List( List&& other ) {
        // TODO - Don't forget initialize the list beforehand
        head.next = &tail;
        tail.prev = &head;
        _size = 0;

        head = other.head;
        tail = other.tail;
        head.next = other.head.next;
        tail.prev = other.tail.prev;
        other.head.next->prev = &head;
        other.tail.prev->next = &tail;

        other.head.next = &other.tail;
        other.tail.prev = &other.head;
        _size = other._size;
        other._size = 0;
    }
    ~List() {
        // TODO
        clear();
    }
    List& operator=( const List& other ) {
        // TODO
        if (&other == this)
        {
            return *this;
        }
        clear();
        head = other.head;
        tail = other.tail;
        head.next = &tail;
        tail.prev = &head;
        for (basic_iterator it = other.begin(); it != other.end(); it++)
        {
            push_back(*it);
        }
        _size = other._size;
        return *this;
    }
    List& operator=( List&& other ) noexcept {
        // TODO
        if (&other == this)
        {
            return *this;
        }
        clear();
        head = other.head;
        tail = other.tail;
        head.next = other.head.next;
        tail.prev = other.tail.prev;
        other.head.next->prev = &head;
        other.tail.prev->next = &tail;

        other.head.next = &other.tail;
        other.tail.prev = &other.head;
        _size = other._size;
        other._size = 0;
        return *this;
    }

    reference front() {
        // TODO
        return head.next->data;
    }
    const_reference front() const {
        // TODO
        return head.next->data; 
    }
	
    reference back() {
        // TODO
        return tail.prev->data;
    }
    const_reference back() const 
    {
        // TODO
        return tail.prev->data;
    }
	
    iterator begin() noexcept 
    {
        // TODO
        if (empty())
        {
            return iterator(&tail);
        }
        else
        {
            return iterator(head.next);
        }
    }
    const_iterator begin() const noexcept {
        // TODO
        if (empty())
        {
            return const_iterator(&tail);
        }
        else
        {
            return const_iterator(head.next);
        }
    }
    const_iterator cbegin() const noexcept {
        // TODO
        if (empty())
        {
            return const_iterator(&tail);
        }
        else
        {
            return const_iterator(head.next);
        }
    }

    iterator end() noexcept {
        // TODO
        return iterator(&tail);
    }
    const_iterator end() const noexcept {
        // TODO
        return const_iterator(&tail);
    }
    const_iterator cend() const noexcept {
        // TODO
        return const_iterator(&tail);
    }

    bool empty() const noexcept {
        // TODO
        if (_size == 0)
            return true;
        else 
            return false;
    }

    size_type size() const noexcept {
        // TODO
        return _size;
    }

    void clear() noexcept {
        // TODO
        while(_size != 0)
        {
            pop_back();
        }
    }

    iterator insert( const_iterator pos, const T& value ) {
        // TODO
        Node* newNode = new Node(value);

        newNode->next = pos.node;
        newNode->prev = pos.node->prev;
        pos.node->prev = newNode;
        newNode->prev->next = newNode;
        _size++;
        return iterator(newNode);
    }
    iterator insert( const_iterator pos, T&& value ) {
        // TODO
        Node* newNode = new Node(std::move(value));

        newNode->next = pos.node;
        newNode->prev = pos.node->prev;
        pos.node->prev = newNode;
        newNode->prev->next = newNode;
        _size++;
        return iterator(newNode);
    }

    iterator erase( const_iterator pos ) 
    {
        // TODO

        Node* copy = pos.node->next;
        pos.node->prev->next = pos.node->next;
        pos.node->next->prev = pos.node->prev;
        delete pos.node;
        _size--;
        return iterator(copy);
    }

    void push_back( const T& value ) {
        // TODO
        insert(iterator(&tail), value);
    }
    void push_back( T&& value ) {
        // TODO
        insert(iterator(&tail), std::move(value));
    }

    void pop_back() {
        // TODO
        if(!empty())
        {
            erase(iterator(tail.prev));
        }
    }
	
    void push_front( const T& value ) {
        // TODO
        insert(iterator(head.next), value);
    }
	void push_front( T&& value ) {
        // TODO
        insert(iterator(head.next), std::move(value));
    }

    void pop_front() {
        // TODO
        if(!empty())
        {
            erase(iterator(head.next));
        }
        
    }

    /*
      You do not need to modify these methods!
      
      These method provide the non-const complement 
      for the const_iterator methods provided above.
    */
    iterator insert( iterator pos, const T & value) { 
        return insert((const_iterator &) (pos), value);
    }

    iterator insert( iterator pos, T && value ) {
        return insert((const_iterator &) (pos), std::move(value));
    }

    iterator erase( iterator pos ) {
        return erase((const_iterator&)(pos));
    }
};


/*
    You do not need to modify these methods!

    These method provide a overload to compare const and 
    non-const iterators safely.
*/
 
namespace {
    template<typename Iter, typename ConstIter, typename T>
    using enable_for_list_iters = typename std::enable_if<
        std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::iterator, 
            Iter
        >{} && std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::const_iterator,
            ConstIter
        >{}, T>::type;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) == rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) == lhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) != rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) != lhs;
}