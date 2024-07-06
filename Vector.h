#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef> // size_t
#include <stdexcept> // std::out_of_range
#include <type_traits> // std::is_same

template <class T>
class Vector {
public:
    class iterator;
private:
    T* array;
    size_t _capacity, _size;

    // You may want to write a function that grows the vector
    void grow() 
    { 
        /* TODO */ 
        if(array == nullptr)
        {
            array = new T[1];
            _capacity = 1;
        }
        else
        {
            T* tempArray = new T[_capacity*2];
            for(size_t i=0; i < _capacity; i++)
            {
                tempArray[i] = std::move(array[i]);
            }
            delete[] array;
            array = std::move(tempArray);
            _capacity *= 2;
        }
    }

public:
    Vector() noexcept 
    { 
        /* TODO */ 
        _capacity = 0;
        _size = 0;
        array = nullptr;
    }
    Vector(size_t count, const T& value) 
    { 
        /* TODO */ 
        _size = _capacity = count;
        array = new T[count];
        for (size_t i = 0; i < count; ++i)
        {
            array[i] = value;
        }
    }
    explicit Vector(size_t count) 
    { 
        /* TODO */ 
        _size = _capacity = count;
        array = new T[_size];
        for (size_t i = 0; i < _size; ++i)
        {
            array[i] = T();
        }
    }
    // Copy constructor
    Vector(const Vector& other) 
    {  
        /* TODO */ 
        _capacity = other._capacity;
        _size = other._size;
        array = new T[other._size];
        for (size_t i = 0; i < other._size; i++)
        {
            array[i] = other.array[i];
        }

    }
    //Move constructor 
    Vector(Vector&& other) noexcept 
    { 
        /* TODO */
        _size = other._size;
        _capacity = other._capacity;
        array = other.array;

        other._size = 0;
        other._capacity = 0;
        other.array = nullptr;
    }

    // Destructor 
    ~Vector() 
    { 
        /* TODO */ 
        delete[] array;
    }

    // copy assignment
    Vector& operator=(const Vector& other) 
    { 
        /* TODO */ 
        if (this != &other) 
        {
            delete[] array;

            _capacity = other._capacity;
            _size = other._size;
            array = new T[_size];

            for (size_t i = 0; i < _size; i++)
            {
                array[i] = other.array[i];
            }
        }
        return *this;
    }

    // move assingment 
    Vector& operator=(Vector&& other) noexcept 
    { 
        /* TODO */ 
        if (this != &other) 
        {
            delete[] array;
            _size = other._size;
            _capacity = other._capacity;
            array = other.array;

            other._size = 0;
            other._capacity = 0;
            other.array = nullptr;
        }
        return *this;
    }

    iterator begin() noexcept 
    { 
        /* TODO */ 
        return iterator(array);
    }
    iterator end() noexcept 
    { 
        /* TODO */
        return iterator(array + _size);
    }

    [[nodiscard]] bool empty() const noexcept 
    { 
        /* TODO */ 
        return _size == 0;
    }
    size_t size() const noexcept 
    { 
        /* TODO */ 
        return _size;
    }
    size_t capacity() const noexcept 
    { 
        /* TODO */ 
        return _capacity;
    }

    T& at(size_t pos) 
    { 
        /* TODO */ 
        if (pos >= _size)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            return array[pos];  
        }
    }
    const T& at(size_t pos) const 
    { 
        /* TODO */ 
        if (pos >= _size)
        {
            throw std::out_of_range("Out of Range ");
        }
        else
        {
            return array[pos];  
        }
    }
    T& operator[](size_t pos) 
    { 
        /* TODO */ 
        return array[pos];

    }
    const T& operator[](size_t pos) const 
    { 
        /* TODO */ 
        return array[pos];
    }
    T& front() 
    { 
        /* TODO */ 
        return array[0];
    }
    const T& front() const 
    { 
        /* TODO */ 
        return array[0];
    }
    T& back() 
    { 
        /* TODO */
        return array[_size -1];
    }
    const T& back() const 
    { 
        /* TODO */ 
        return array[_size -1];
    }

    void push_back(const T& value) 
    { 
        /* TODO */ 
        if (_size == _capacity)
        {
            grow();
        }
        array[_size] = value;
        _size++;
    }
    void push_back(T&& value) 
    { 
        /* TODO */ 
        if (_size == _capacity)
        {
            grow();
        }
        array[_size] = std::move(value);
        _size++;
    }
    void pop_back() 
    { 
        /* TODO */ 
        _size--;
    }
    //insert 
    iterator insert(iterator pos, const T& value) 
    { 
        /* TODO */ 
        size_t index = pos - begin();
        if (_size == _capacity)
            grow();
        for(size_t i = _size; i > index; i--)
        {
            array[i] = std::move(array[i-1]);
        }
        array[index] = value;
        _size++;
        return &array[index];

    }
    //insert with move 
    iterator insert(iterator pos, T&& value) 
    {
         /* TODO */ 
         size_t index = pos - begin();
        if (_size == _capacity)
            grow();
        for(size_t i = _size; i > index; i--)
        {
            array[i] = std::move(array[i-1]);
        }
        array[index] = std::move(value);
        _size++;
        return &array[index];
    }
    // insert multiple 
    iterator insert(iterator pos, size_t count, const T& value) 
    { 
        /* TODO */ 
        size_t index = pos - begin();
        size_t tempSize = _size;
        _size += count;

        while (_size > _capacity)
        {
            grow();
        }

        pos = begin() + index;
        // Shift elements to make space for the new ones
        for (size_t i = tempSize; i > index; --i)
        {
            array[i + count - 1] = std::move(array[i - 1]);
        }

        // Insert the new elements
        for (size_t i = index; i < index + count; i++)
        {
            array[i] = std::move(value);
        }
        return pos;
    }
    iterator erase(iterator pos) 
    { 
        /* TODO */ 
        size_t index = pos - begin();
        if(index == _size-1)
        {
            --_size;
            return end();
        }
        else
        {
            for (size_t i = index; i < _size-1; i++)
            {
                array[i] = std::move(array[i+1]);
            }
            --_size;
            return iterator(array + index);
        }
    }
    iterator erase(iterator first, iterator last) 
    { 
        /* TODO */ 
        size_t firstIndex = first - begin();
        size_t lastIndex = last - begin();
        size_t difference = lastIndex - firstIndex;
        if  (firstIndex > lastIndex)
        {
            throw std::invalid_argument("Invalid Argument");
        }
        if(firstIndex == _size-1 || firstIndex == lastIndex ||firstIndex + difference > _size|| lastIndex > _size)
        {
            throw std::out_of_range("Out of range");
        }
        else 
        {
            for(size_t i = firstIndex; i + difference < _size; i++)
            {
                array[i] = std::move(array[i+difference]);
            }
            _size-=difference;
            return first;
        }
        // Ask about when first and last are the same, how is it possible to return end()
        // when we don't remove the last index only the first, we'd  have to go out of bounds to 
        // remove the very last index, because the index of the last element is size-1
        // what to do when first is the last element and when they equal each other 
    }

    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
    private:
        // Points to some element in the vector (or nullptr)
        T* _ptr;

    public:
        iterator() 
        {
            /* TODO */ 
            _ptr = nullptr; 
        }
        iterator(T* ptr) 
        { 
            /* TODO */ 
            _ptr = ptr;
        }

        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept 
        { 
            /* TODO */ 
            return *_ptr;
        }
        [[nodiscard]] pointer operator->() const noexcept 
        { 
            /* TODO */ 
            return _ptr;
        }
        
        // Prefix Increment: ++a
        iterator& operator++() noexcept 
        { 
            /* TODO */ 
            ++_ptr;
			return *this;
        }
        // Postfix Increment: a++
        iterator operator++(int) noexcept 
        { 
            /* TODO */ 
            iterator copy(_ptr);
            ++(_ptr); 
            return copy;
        }
        // Prefix Decrement: --a
        iterator& operator--() noexcept 
        { 
            /* TODO */ 
            --_ptr;
			return *this;
        }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept 
        { 
            /* TODO */ 
            iterator copy(_ptr);
            --_ptr; 
            return copy;
        }

        iterator& operator+=(difference_type offset) noexcept 
        { 
            /* TODO */ 
            _ptr += offset;
            return *this;
        }
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept 
        { 
            /* TODO */ 
            iterator copy(_ptr);
            copy += offset;
            return copy;
        }
        
        iterator& operator-=(difference_type offset) noexcept 
        { 
            /* TODO */ 
            _ptr -= offset;
            return *this;
        }
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept 
        { 
            /* TODO */ 
            iterator copy(_ptr);
            copy -= offset;
            return copy;
        }
        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept 
        { 
            /* TODO */ 
            return _ptr - rhs._ptr;
        }
        
        [[nodiscard]] reference operator[](difference_type offset) const noexcept 
        { 
            /* TODO */ 
            return *(_ptr + offset);
        }

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept 
        { 
            /* TODO */
            return _ptr == rhs._ptr;
        }
        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept 
        { 
            /* TODO */ 
            return _ptr != rhs._ptr;
        }
        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept 
        { 
            /* TODO */ 
            return _ptr < rhs._ptr;
        }
        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept 
        { 
            /* TODO */ 
            return _ptr > rhs._ptr;
        }
        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept 
        { 
            /* TODO */ 
            return _ptr <= rhs._ptr;
        }
        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept 
        { 
            /* TODO */ 
            return _ptr >= rhs._ptr;
        }
    };


    void clear() noexcept 
    { 
        /* TODO */ 
        _size = 0;
    }
};

// This ensures at compile time that the deduced argument _Iterator is a Vector<T>::iterator
// There is no way we know of to back-substitute template <typename T> for external functions
// because it leads to a non-deduced context
namespace {
    template <typename _Iterator>
    using is_vector_iterator = std::is_same<typename Vector<typename _Iterator::value_type>::iterator, _Iterator>;
}

template <typename _Iterator, bool _enable = is_vector_iterator<_Iterator>::value>
[[nodiscard]] _Iterator operator+(typename _Iterator::difference_type offset, _Iterator const& iterator) noexcept 
{ 
    /* TODO */ 
    _Iterator copy(iterator);
    copy += offset;
    return copy;
}

#endif
