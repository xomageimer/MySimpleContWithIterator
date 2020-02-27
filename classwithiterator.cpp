#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;

template <typename It>
struct Iterator{
private:
    typedef It value_type;

    It* current;
public:
    explicit Iterator(It* his_iterator):current(his_iterator){};
    Iterator(const Iterator& it) : current(it->current){}

    bool operator!=(const Iterator& rhs) const{
        return current != rhs.current;
    };
    bool operator==(const Iterator& rhs) const{
        return current == rhs->current;
    };
    bool operator++(){
        return ++current;
    }
    It& operator*(){
        return *current;
    }
};

template<typename C>
struct Conteiner{
private:
    typedef Iterator<C> iterator;

public:
    explicit Conteiner() = default;
    Conteiner(initializer_list<C> init_list);

    [[nodiscard]] iterator begin();
    [[nodiscard]] iterator end();

    [[nodiscard]] iterator cbegin() const;
    [[nodiscard]] iterator cend() const;

private:
    const size_t size;
    unique_ptr<C> data;
};
template<typename C>
Conteiner<C>::Conteiner(initializer_list<C> init_list) : size(init_list.size()), data(new C[size]){
    copy(init_list.begin(), init_list.end(), data.get());
}
template<typename C>
typename Conteiner<C>::iterator Conteiner<C>::begin(){
    return iterator{data.get()};
}
template<typename C>
typename Conteiner<C>::iterator Conteiner<C>::end(){
    return iterator{data.get() + size};
}
template<typename C>
typename Conteiner<C>::iterator Conteiner<C>::cbegin() const {
    return iterator{data.get()};
}
template<typename C>
typename Conteiner<C>::iterator Conteiner<C>::cend() const {
    return iterator{data.get() + size};
}


int main(){
    Conteiner<string> v {"wabalabadubabuba", "goopa", "dood", "LOOOL DUDE"};


    for (const auto& p : v){
        std::cout << p << " ";
    }
}


