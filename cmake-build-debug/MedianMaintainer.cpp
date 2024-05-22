// 对顶堆 动态维护中位数， 支持删除操作
template <typename T>
class MedianMaintainer {
public:
    MedianMaintainer() {
        init();
    }

    void add(const T& val_) {
        if (val_ <= *greater.begin()) {
            less.insert(val_);
            less_sum += val_;
        }
        else {
            greater.insert(val_);
            greater_sum += val_;
        }
        adjust();
    }

    void remove(const T& val) {
        auto itLess = less.find(val);
        if (itLess != less.end()) {
            less.erase(itLess);
            less_sum -= val;
        }
        else {
            auto itGreater = greater.find(val);
            if (itGreater != greater.end()) {
                greater.erase(itGreater);
                greater_sum -= val;
            }
        }
        adjust();
    }

    T getMiddle() { // 个数为偶数时，选择 第 count/2 小 的数
        if(!less.empty())   return *less.rbegin();
        return 0;
    }

    int getLessSize() {
        return  less.size();
    }

    int getGreaterSize() {
        return greater.size();
    }

    ll getLessSum() {
        return less_sum;
    }

    ll getGreaterSum() {
        return greater_sum;
    }

private:
    void init() {
        less.clear();
        greater.clear();
        less_sum = greater_sum = 0;
    }

    void adjust() {
        while (less.size() > greater.size() + 1) {
            auto it = prev(less.end());
            less_sum -= *it;
            greater_sum += *it;
            greater.insert(*it);
            less.erase(it);
        }
        while (greater.size() > less.size()) {
            auto it = greater.begin();
            less_sum += *it;
            greater_sum -= *it;
            less.insert(*it);
            greater.erase(it);
        }
    }
    multiset<T> less, greater;
    ll less_sum{}, greater_sum{};
};