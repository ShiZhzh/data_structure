#include<iostream>
#include<exception>
using namespace std;
class illegalParameterValue:public exception{
    public:
    illegalParameterValue(const string str):message(str){}
    const char* what(){
        return message.c_str();
    } 
    private:
    string message;
};
class stackEmpty:public exception{
    public:
    stackEmpty(){}
    const char* what(){
        return message.c_str();
    } 
    private:
    string message="stack is empty!";
};
template<class T>
class stack{
    public:
        virtual ~stack(){}
        virtual bool empty() const=0;
        virtual int size() const=0;
        virtual T& top()=0;
        virtual void pop()=0;
        virtual void push(const T& theElement)=0;
};
template<class T>
class arrayStack:public stack<T>{
    public:
        arrayStack(int initialCapacity){
            if(initialCapacity<1){
                throw illegalParameterValue("Initial Capacity must > 0!");
            }
            arrayLength=initialCapacity;
            stack=new T[arrayLength];
            stackTop=-1;
        };
        ~arrayStack(){delete[]stack;}
        bool empty()const{return stackTop==-1;}
        int size()const{return stackTop+1;}
        T& top(){
            if(stackTop==-1){throw stackEmpty();}
            else{return stack[stackTop];}
        }
        void pop(){
            if(stackTop==-1){throw stackEmpty();}
            else{
                stack[stackTop--].~T();
            }
        }
        void push(const T& theElement){
            if(stackTop==arrayLength-1){
                T* temp=new T[arrayLength*2];
                T* del=nullptr;
                copy(stack,stack+stackTop+1,temp);
                del=stack;
                stack=temp;
                arrayLength*=2;
                delete[] del;
            }
            stack[++stackTop]=theElement;
        }

    protected:
        int stackTop;
        int arrayLength;
        T* stack;
};
int main(){
    try{
        int n,a;
        cin>>n;
        arrayStack<int>s(1);
        for(int i=0;i<n;i++){
            cin>>a;
            s.push(a);
        }
        cout<<s.top();
        return 0;
    }
    catch(illegalParameterValue&i){
        cout<<i.what();
    }
    catch(stackEmpty&i){
        cout<<i.what();
    }
}