namespace sjtu {
    class CrossArray{
    private:
        int **lines_;      // pointers to arrays for each line
        int *sizes_;       // sizes of each line (0 if nullptr)
        int capacity_;     // maximum number of lines allowed
        int count_;        // number of inserted lines

        int total_elements_() const {
            int total = 0;
            for (int i = 0; i < capacity_; ++i) {
                if (lines_ && lines_[i] != nullptr) total += sizes_[i];
            }
            return total;
        }
    public:
        explicit CrossArray(int lines) : lines_(nullptr), sizes_(nullptr), capacity_(lines), count_(0) {
            if (capacity_ < 0) capacity_ = 0;
            if (capacity_ > 0) {
                lines_ = new int*[capacity_];
                sizes_ = new int[capacity_];
                for (int i = 0; i < capacity_; ++i) {
                    lines_[i] = nullptr;
                    sizes_[i] = 0;
                }
            }
        }

        CrossArray(const CrossArray & o) : lines_(nullptr), sizes_(nullptr), capacity_(o.capacity_), count_(o.count_) {
            if (capacity_ > 0) {
                lines_ = new int*[capacity_];
                sizes_ = new int[capacity_];
                for (int i = 0; i < capacity_; ++i) {
                    if (o.lines_ && o.lines_[i] != nullptr && o.sizes_[i] > 0) {
                        sizes_[i] = o.sizes_[i];
                        lines_[i] = new int[sizes_[i]];
                        for (int j = 0; j < sizes_[i]; ++j) lines_[i][j] = o.lines_[i][j];
                    } else {
                        lines_[i] = nullptr;
                        sizes_[i] = 0;
                    }
                }
            }
        }

        CrossArray & WhichGreater(CrossArray & o) {
            int a = total_elements_();
            int b = o.total_elements_();
            return (a >= b) ? *this : o;
        }

        bool IsSame(const CrossArray & o) {
            return this == &o;
        }

        bool InsertArrays(const int * Input, int size) {
            if (count_ >= capacity_) return false;
            if (size < 0) return false;
            if (size == 0) {
                lines_[count_] = nullptr;
                sizes_[count_] = 0;
                ++count_;
                return true;
            }
            int *arr = new int[size];
            for (int i = 0; i < size; ++i) arr[i] = Input[i];
            lines_[count_] = arr;
            sizes_[count_] = size;
            ++count_;
            return true;
        }

        void AppendArrays(const int * Input,int Line,int size) {
            if (size <= 0) return; // nothing to append
            int oldSize = sizes_[Line];
            int newSize = oldSize + size;
            if (oldSize == 0 || lines_[Line] == nullptr) {
                int *arr = new int[newSize];
                for (int i = 0; i < size; ++i) arr[i] = Input[i];
                if (lines_[Line]) delete [] lines_[Line];
                lines_[Line] = arr;
                sizes_[Line] = newSize;
                return;
            }
            int *newArr = new int[newSize];
            for (int i = 0; i < oldSize; ++i) newArr[i] = lines_[Line][i];
            for (int i = 0; i < size; ++i) newArr[oldSize + i] = Input[i];
            delete [] lines_[Line];
            lines_[Line] = newArr;
            sizes_[Line] = newSize;
        }

        void DoubleCrossLength() {
            int newCap = (capacity_ > 0) ? (capacity_ * 2) : 1;
            int **newLines = new int*[newCap];
            int *newSizes = new int[newCap];
            for (int i = 0; i < newCap; ++i) {
                if (i < capacity_) {
                    newLines[i] = lines_ ? lines_[i] : nullptr;
                    newSizes[i] = sizes_ ? sizes_[i] : 0;
                } else {
                    newLines[i] = nullptr;
                    newSizes[i] = 0;
                }
            }
            if (lines_) delete [] lines_;
            if (sizes_) delete [] sizes_;
            lines_ = newLines;
            sizes_ = newSizes;
            capacity_ = newCap;
        }

        const int * AtArray(int i) {
            return lines_ ? lines_[i] : nullptr;
        }

        int & At(int i , int j) {
            return lines_[i][j];
        }

        ~CrossArray() {
            if (lines_) {
                for (int i = 0; i < capacity_; ++i) {
                    if (lines_[i] != nullptr) delete [] lines_[i];
                }
                delete [] lines_;
            }
            if (sizes_) delete [] sizes_;
            lines_ = nullptr;
            sizes_ = nullptr;
            capacity_ = 0;
            count_ = 0;
        }

    };
}
