#include <vector>

#define DOUBLE_DEREFERENCED "This input-iterator was dereferenced twice"

template <typename T>

class InputIterator
{
private:
    std::vector<T> _vec;

public:
    InputIterator() : _vec() {};
    InputIterator(std::vector<T> vec) : _vec(vec) {};

    class iterator
    {
    private:
        typename std::vector<T> _vector;
        typename std::vector<T>::iterator _iter;

        int _currentElement;

        int _size;
        mutable bool _alreadyDereferenced;
    
    public:

        typedef T value_type;
        typedef T &reference;
        typedef T *pointer;
        typedef std::ptrdiff_t difference_type;
        typedef std::input_iterator_tag iterator_category;

        iterator(const std::vector<T> &vector, bool isEnd) : _vector(vector), _size(_vector.size()),
                                                             _alreadyDereferenced(false)
        {
            if (isEnd)
            {
                _currentElement = _size;
                _iter = _vector.end();
            }
            else
            {
                _currentElement = 0;
                _iter = _vector.begin(); 
            }
        }

        iterator &operator++()
        {
            _currentElement++;
            _iter++;
            _alreadyDereferenced = false;
            
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp = *this;

            _currentElement++;
            _iter++;
            _alreadyDereferenced = false;

            return temp;
        }

        T operator*() const
        {
            if (_alreadyDereferenced == true)
            {
                throw std::runtime_error(DOUBLE_DEREFERENCED);
            }
            else
            {
                _alreadyDereferenced = true;
                return *(this->_iter);
            }
        }

        const T *operator->() const
        {
            if (_alreadyDereferenced == true)
            {
                throw std::runtime_error(DOUBLE_DEREFERENCED);
            }
            else
            {
                _alreadyDereferenced = true;
                return &(*(this->_iter));
            }
        }

        bool operator==(const iterator &rhs) const
        {
            return (this->_currentElement == rhs._currentElement);
        }

        bool operator!=(const iterator &rhs) const
        {
            return (this->_currentElement != rhs._currentElement);
        }
    };

    iterator begin()
    {
        iterator it(this->_vec, false);
        return it;
    }

    iterator end()
    {
        iterator it(this->_vec, true);
        return it;
    }
};
