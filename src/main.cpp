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
    ~Array()
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
    void remove(int index)
    {
        for (int i = index; i < size - 1; i++)
        {
            data[i] = data[i + 1];
        }
        size--;
    }
    T& operator[](int index)
    {
        return data[index];
    }
    const T& operator[](int index) const
    {
        return data[index];
    }
    int getSize() const
    {
        return size;
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
};

int main()
{
    Array<int> arr;
    arr.add(1);
    arr.add(4);
    arr.add(2);
    arr.add(6);
    arr.add(3);

    for (int i = 0; i < arr.getSize(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    arr.remove(3);
    for (int i = 0; i < arr.getSize(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    SortedArray<int> sortedArr;
    sortedArr.add(1);
    sortedArr.add(4);
    sortedArr.add(2);
    sortedArr.add(6);
    sortedArr.add(3);

    for (int i = 0; i < sortedArr.getSize(); i++)
    {
        cout << sortedArr[i] << " ";
    }
    cout << endl;
}