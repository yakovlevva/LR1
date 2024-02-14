#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm> // for std::sort

using namespace std;

class Array {
public:
    typedef double value_type;
    typedef double* iterator;
    typedef const double* const_iterator;
    typedef double& reference;
    typedef const double& const_reference;
    typedef size_t size_type;

    Array(const size_type n);
    Array(const Array& array);
    Array(iterator first, iterator last);
    ~Array() { delete[] ptr; }

    Array& operator=(const Array&);

    iterator begin() { return ptr; }
    const_iterator begin() const { return ptr; }
    iterator end() { return ptr + Count; }
    const_iterator end() const { return ptr + Count; }

    size_type size() const { return Count; }

    void resize(size_type newsize);

    size_type capacity() const { return sizemem; }

    bool empty() const { return Count == 0; }

    reference operator[](size_type index);
    const_reference operator[](size_type index) const;
    reference front() { return ptr[0]; }
    const_reference front() const { return ptr[0]; }

    reference back() { return ptr[size() - 1]; }
    const_reference back() const { return ptr[size() - 1]; }

    void swap(Array& other);

    void assign(const value_type& v);

    void push_back(const value_type& v);
    void pop_back() {
        ptr[Count - 1] = 0;
        Count--;
    }

    void clear() { Count = 0; }

    void show() {
        for (int i = 0; i < Count; i++) {
            cout.precision(3);
            cout << fixed << ptr[i] << " ";
        }
        cout << '\n';
    }

    void sort(bool ascending = true);

private:
    value_type* ptr;
    size_type Count;
    static const size_type min = 10;
    size_type sizemem;
};

double summary(const Array& arr) {
    double sum = 0;
    for (int i = 0; i < arr.size(); i++)
        sum += arr[i];
    return sum;
}

double average(const Array& arr) {
    return summary(arr) / arr.size();
}

void helper(Array& arr) {
    double f = 0;

    for (int i = arr.size() - 1; i > 0; i--) {
        if (arr[i] < 0) {
            f = arr[i];
            break;
        }
    }

    f /= 2;

    for (int i = 0; i < arr.size(); i++)
        (arr.begin())[i] = (arr.begin())[i] + f;
}

void Array::push_back(const value_type& v) {
    if (Count == sizemem)
        resize(sizemem * 2);
    ptr[Count++] = v;
}

void Array::resize(size_type newsize) {
    value_type* s = new value_type[newsize];
    for (size_type i = 0; i < Count; ++i)
        s[i] = ptr[i];
    delete[] ptr;
    ptr = s;
    sizemem = newsize;
}

Array::Array(iterator first, iterator last) {
    if (first < last) {
        sizemem = (last - first);
        ptr = new value_type[sizemem];
        for (int i = 0; i < sizemem; ++i)
            ptr[i] = *(first + i);
        Count = sizemem;
    }
}

Array::Array(const size_type n) {
    sizemem = n;
    ptr = new value_type[n];
    Count = 0;
}

double& Array::operator[](size_type index) {
    if (index < Count)
        return ptr[index];
}

const double& Array::operator[](size_type index) const {
    if (index < Count)
        return ptr[index];
}

void Array::sort(bool ascending) {
    if (ascending)
        sort(ptr, ptr + Count);
    else
        sort(ptr, ptr + Count, greater<double>());
}

int main() {
    int size, c = 1;
    double elem, sum = 0, aver = 0;

    cin >> size;

    Array arr(size);

    for (int i = 0; i < size; i++) {
        cin >> elem;
        arr.push_back(elem);
    }

    cout << arr.size() << '\n';
    arr.show();

    sum = summary(arr);
    aver = average(arr);

    arr.push_back(sum);
    arr.push_back(aver);

    arr.show();

    helper(arr);

    arr.show();

    while (true) {
        cin >> c;

        if (c == 0) {
            break;
        } else {
            switch (c) {
                case 1:
                    cin >> elem;
                    arr.push_back(elem);
                    cout << "+:" << arr.size() << '\n';
                    arr.show();
                    sum = summary(arr);
                    aver = average(arr);
                    arr.push_back(sum);
                    arr.push_back(aver);
                    arr.show();
                    helper(arr);
                    arr.show();
                    break;
                case 2:
                    arr.pop_back();
                    cout << "-:" << arr.size() << '\n';
                    arr.show();
                    sum = summary(arr);
                    aver = average(arr);
                    arr.push_back(sum);
                    arr.push_back(aver);
                    arr.show();
                    helper(arr);
                    arr.show();
                    break;
                case 3:
                    int option;
                    cout << "Enter 1 for ascending or 0 for descending: ";
                    cin >> option;
                    if (option == 1)
                        arr.sort(true);
                    else if (option == 0)
                        arr.sort(false);
                    cout << "Sorted array: ";
                    arr.show();
                    break;
            }
        }
    }
    return 0;
}
