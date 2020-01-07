#include <iostream>
#include <cstring>
#include <list>
using namespace std;
 
 
template <typename T>
class Deque
{
private:
    list<T> element;
public:
    Deque(){} 
   ~Deque(){}  
    void push_front(T& elmnt)
    { 
       element.push_front(elmnt); 
   }   
    void push_back(T& elmnt)
    {    
        element.push_back(elmnt);  
    }    
    auto empty()
    {   
        return element.empty();
    }
    auto pop_front()
    {
        if(!element.empty()) 
        { 
           auto tmp = element.front(); 
           element.pop_front();
            return tmp;
        }    
        else    
        return -1;
    }    
    auto pop_back()   
    { 
       if(!element.empty())
       {
            auto tmp = element.back();
            element.pop_back();
            return tmp;
       }
       else
            return -1;  
    } 
    auto front()
    {
        if(!element.empty())
            return element.front();
        else
            return -1;
    }
    auto back()
    {
         if(!element.empty()) 
           return element.back();
        else
            return -1;
    }
    auto size()
    {
        return element.size();
    }
};
int main(){ 
   Deque<int> deque;
   int n;
   cin >> n;
   char s[100];
   for(auto i = 0; i < n; i++){
        cin >> s;
        if(!strcmp(s,"push_back")){
            int n;
            cin >> n;
            deque.push_back(n);
        }
        else if(!strcmp(s,"push_front")){
            int n;
            cin >> n;
            deque.push_front(n);
        }
        else if(!strcmp(s,"pop_front"))
            cout << deque.pop_front() << endl;
        else if(!strcmp(s,"pop_back"))
            cout << deque.pop_back() << endl;
        else if(!strcmp(s,"front"))
            cout << deque.front() << endl;
        else if(!strcmp(s,"back"))
            cout << deque.back() << endl;
        else if(!strcmp(s,"size"))
            cout << deque.size() << endl;
        else if(!strcmp(s,"empty"))
            cout << deque.empty() << endl;
    }
    return 0;
}
 
