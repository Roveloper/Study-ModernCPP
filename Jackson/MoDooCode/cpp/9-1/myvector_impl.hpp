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

Vector<bool>::Vector(int n) : data_(new unsigned int[n / 32 + 1]), capacity_(n / 32 + 1), length_(0) {
    for (int i = 0; i < capacity_; ++i) {
        data_[i] = 0;
    }
}

void Vector<bool>::push_back(bool s) {
    if (capacity_ * 32 <= length_) {
        unsigned int* temp = new unsigned int[capacity_ * 2];
        for (int i = 0; i < capacity_; ++i) {
            temp[i] = data_[i];
        }
        for (int i = capacity_; i < 2 * capacity_; ++i) {
            temp[i] = 0;
        }

        delete[] data_;
        data_ = temp;
        capacity_ *= 2;
    }

    if (s) {
        data_[length_ / 32] |= (1 << (length_ % 32));
    }
    ++length_;
}

bool Vector<bool>::operator[](int i) {
    return (data_[i / 32] & (1 << (i % 32))) != 0;
}

void Vector<bool>::remove(int x) {
    for (int i = x + 1; i < length_; ++i) {
        int prev = i - 1;
        int curr = i;

        if (data_[curr / 32] & (1 << (curr % 32))) { // curr의 데이터가 true이면
            data_[prev / 32] |= (1 << (prev % 32)); // prev의 데이터를 true로 변경
        }
        else { // curr의 데이터가 false이면
            unsigned int all_ones_except_prev = 0xFFFFFFFF; // 모든 데이터가 1인 unsigned int
            all_ones_except_prev ^= (1 << (prev % 32)); // prev의 위치만 0으로 변경 --> 11111011라면
            data_[prev / 32] &= all_ones_except_prev; // prev의 위치만 0이 되고, 나머지는 그대로 유지
        }
    }
    length_--;
}

int Vector<bool>::size() { return length_; }
Vector<bool>::~Vector() { delete[] data_;}