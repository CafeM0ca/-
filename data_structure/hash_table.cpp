#include <iostream>
#include <forward_list>
#include <array>
#include <random>
#include <string>
using namespace std;
class hash_table
{
private:
    array<forward_list<int>,12> table;
public:
    void insert(const string& value){
        int idx = convert_to_index(value);
        //table[idx].insert_after(table[idx].end(), hashing(value));
        table[idx].push_front(hashing(value));
        cout << "insert value: " << value << " index is : " << idx << endl;
    }
    int convert_to_index(const string& value){
        return value.size() % 13;    
    }
    int hashing(const string& value){
        int sum = 0;
        for(auto itr : value){
            sum += static_cast<int>(itr);
        }
        return sum;
    }
    bool find(const string& value){
        int idx = convert_to_index(value);
        int v = hashing(value);
        for(const auto& itr : table[idx]){
            if(itr == v){
                return true;
            }
        }
        return false;
    }
    friend ostream& operator<<(ostream& os, const hash_table& ht){
        size_t idx = 0;
        for(auto i : ht.table){
            os << "idx: " << idx++ << " :";
            for(auto itr = i.cbegin(); itr != i.cend(); itr++){
                os << *itr << " ";
            }
            os << "\n";
        }
        return os;
    }
    
};    
int main()
{
    hash_table ht;
    ht.insert("minsu");
    ht.insert("jinyong");
    ht.insert("fucking");
    ht.insert("delicious");
    cout << ht << endl;
    cout << ht.find("minsu") << endl;
    cout << ht.find("fucking") << endl;
    cout << ht.find("asodfjaos") << endl;
    return 0;
}

