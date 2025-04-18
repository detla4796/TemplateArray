#include <iostream>

using namespace std;

template<typename T>
class Array
{
    protected:
    T* data;
    int size;
    int c;
    public:
    Array (int icapacity = 10) : size(0), c(icapacity)
    {
        data = new T[c];
    }
    Array (const Array<T>& o) : size(o.size), c(o.c)
    {
        data = new T[c];
        for (int i = 0; i < size; i++)
        {
            data[i] = o.data[i];
        }
    }
    virtual ~Array()
    {
        delete[] data;
    }
    virtual void add (const T& t)
    {
        int newC = c * 2;
        T* newData = new T[newC];
        for (int i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        c = newC;
        data[size++] = t;
    }
    virtual void checkBound(int index) const = 0;
    virtual void remove(int index) = 0;
    T& operator[](int index)
    {
        checkBound(index);
        return data[index];
    }
    const T& operator[](int index) const
    {
        checkBound(index);
        return data[index];
    }
    int getSize() const
    {
        return size;
    }
    Array<T>& operator=(const Array<T>& o)
    {
        if (this != &o)
        {
            delete[] data;
            size = o.size;
            c = o.c;
            data = new T[c];
            for (int i = 0; i < size; i++)
            {
                data[i] = o.data[i];
            }
        }
        return *this;
    }
    int find(const T& t) const
    {
        for (int i = 0; i < size; i++)
        {
            if (data[i] == t)
            {
                return i;
            }
        }
    }
};

template<typename T>
class SortedArray : public Array<T>
{
    public:
    SortedArray(int icapacity = 10) : Array<T>(icapacity) {}

    virtual void add(const T& t) override
    {
        int newC = this->c * 2;
        T* newData = new T[newC];
        for (int i = 0; i < this->getSize(); i++)
        {
            newData[i] = this->data[i];
        }
        delete[] this->data;
        this->data = newData;
        this->c = newC;
        int i = 0;
        while (i < this->size && this->data[i] < t)
        {
            i++;
        }
        for (int j = this->size; j > i; j--)
        {
            this->data[j] = this->data[j - 1];
        }
        this->data[i] = t;
        this->size++;
    }
    virtual void checkBound(int index) const override 
    {
        if (index < 0 || index >= this->size)
        {
            throw out_of_range("Index out of range");
        }
    }
    virtual void remove(int index) override 
    {
        checkBound(index);
        for (int i = index; i < this->size - 1; i++)
        {
            this->data[i] = this->data[i + 1];
        }
        this->size--;
    }
};

int main()
{
    SortedArray<int> arr;
    arr.add(5);
    arr.add(2);
    arr.add(1);
    arr.add(3);
    arr.add(4);

    cout << "Sorted array: ";
    for (int i = 0; i < arr.getSize(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    int sValue = 3;
    int p = arr.find(sValue);
    cout << "Element " << sValue << " found at index " << p << endl;

    arr.remove(2);
    cout << "After removing element at index 2: ";
    for (int i = 0; i < arr.getSize(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}