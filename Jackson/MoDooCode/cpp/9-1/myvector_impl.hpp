template <typename T>
Vector<T>::Vector(int n) : data_(new T[n]), capacity_(n), length_(0) {}

template <typename T>
void Vector<T>::push_back(const T value) {
    if (length_ == capacity_) {
        auto tmp = data_;
        data_ = new T[capacity_ * 2];
        for (int i = 0; i < length_; ++i) {
            data_[i] = tmp[i];
        }
        delete[] tmp;
        capacity_ *= 2;
    }
    data_[length_++] = value;
}

template <typename T>
const T &Vector<T>::operator[](int i) { return data_[i]; }

template <typename T>
T Vector<T>::operator[](int i) const { return data_[i]; }

template <typename T>
void Vector<T>::remove(int x) {
    for (int i = x + 1; i < length_; ++i) {
        data_[i - 1] = data_[i];
    }
    --length_;
}

template <typename T>
int Vector<T>::size() { return length_; }

template <typename T>
Vector<T>::~Vector() { delete[] data_; }