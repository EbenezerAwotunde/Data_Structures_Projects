#ifndef QUEUE_H
#define QUEUE_H
#include "List.h"

template <typename T, typename Container = List<T>>
class Queue {

    template <typename T1, typename C1>
    friend bool operator==(const Queue<T1, C1>&, const Queue<T1, C1>&);

    public:
        // Aliases for accessing data types outside of the class
        using container_type  = Container;
        using value_type      = typename Container::value_type;
        using size_type       = typename Container::size_type;
        using reference       = typename Container::reference;
        using const_reference = typename Container::const_reference;
        using iterator        = typename Container::iterator;
        using const_iterator  = typename Container::const_iterator;

    private:
        Container c;

    public:
        // The constructors, destructor, and assignment operators are done for you
        Queue() = default;
        Queue(const Queue& other) = default;
        Queue(Queue&& other) = default;
        ~Queue() = default;
        Queue& operator=(const Queue& other) = default;
        Queue& operator=(Queue&& other) = default;

        reference front() 
        { 
            /* TODO */ 
            c.front();
        }
        const_reference front() const 
        { 
            /* TODO */ 
            c.front();
        }
        reference back() 
        { 
            /* TODO */ 
            c.back();
        }
        const_reference back() const 
        { 
            /* TODO */ 
            c.back();
        }

        bool empty() const 
        { 
            /* TODO */ 
            c.empty();
        }
        size_type size() const 
        { 
            /* TODO */ 
            c.size();
        }

        void push(const value_type& value) 
        { 
            /* TODO */ 
            c.push_back(value);
        }
        void push(value_type&& value) 
        { 
            /* TODO */
            c.push_back(std::move(value)); 
        }
        void pop() 
        { 
            /* TODO */ 
            c.pop_front();
        }
};

template <typename T, typename Container>
inline bool operator==(const Queue<T, Container>& lhs, const Queue<T, Container>& rhs) 
{ 
    /* TODO */ 
    if(lhs.size() == rhs.size())
    {
        auto left_iter = lhs.c.begin();
        auto right_iter = rhs.c.begin();

        while (left_iter != lhs.c.end())
        {
            if (*left_iter != *right_iter)
            {
                return false;
            }
            left_iter++;
            right_iter++;
        }
        return true;
    }
    else 
    {
        return false;
    }
}

#endif
