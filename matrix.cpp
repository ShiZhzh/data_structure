#include<iostream>
#include<exception>
#include<sstream>
#include<string.h>
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
class matrixSizeMismath:public exception{
    public:
    matrixSizeMismath(const string str):message(str){}
    const char* what(){
        return message.c_str();
    } 
    private:
    string message;
};
template<class T>
class matrix{
    template<class C>friend int anti_mapping(int r,int c,const matrix<C>&m);
    template<class C>friend ostream& operator<<(ostream&,const matrix<C>&);
    template<class C>friend istream& operator>>(istream&,matrix<C>&);
    public:
        matrix(int theRows=0,int theColumns=0){
            if(theColumns<0||theRows<0){
                throw illegalParameterValue("行列均不可小于0!");
            }
            if((theColumns==0||theRows==0)&&(theColumns!=0||theRows!=0)){
                throw illegalParameterValue("行列均不可为0!");
            }
            this->theColumns=theColumns;
            this->theRows=theRows;
            element=new T[theColumns*theRows];
        };
        matrix(const matrix<T>&m){
            theColumns=m.theColumns;
            theRows=m.theRows;
            element=new T[theColumns*theRows];
            copy(m.element,m.element+theColumns*theRows,element);
        }
        ~matrix(){
            delete[]element;
        }
        int rows(){return theRows;}
        int columns(){return theColumns;}
        T& operator()(int i,int j)const{
            if(i<0||i>theRows||j<0||j>theColumns){
                throw matrixSizeMismath("错误的矩阵索引!");
            }
            return element[anti_mapping(i,j,this)];
        }
        matrix<T>& operator=(const matrix<T>&);
        //matrix<T> operator+()const;
        matrix<T> operator+(const matrix<T>&)const;
        matrix<T> operator-(const matrix<T>&)const;
        matrix<T> operator*(const matrix<T>&)const;
        matrix<T>& operator+=(const T&);
    private:
        int theRows,
            theColumns;
        T* element;
};
template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>&m){
    theColumns=m.theColumns;
    theRows=m.theRows;
    element=new T[theColumns*theRows];
    copy(m.element,m.element+theColumns*theRows,element);
    return *this;
}
template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>&m)const{
    if(theRows!=m.theRows||theColumns!=m.theColumns){
        throw matrixSizeMismath("大小不匹配!");
    }
    matrix<T>w(theRows,theColumns);
    for(int i=0;i<theRows*theColumns;i++){
        w.element[i]=element[i]+m.element[i];
    }
    return w;
}
template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>&m)const{
    if(theRows!=m.theRows||theColumns!=m.theColumns){
        throw matrixSizeMismath("大小不匹配!");
    }
    matrix<T>w(theRows,theColumns);
    for(int i=0;i<theRows*theColumns;i++){
        w.element[i]=element[i]-m.element[i];
    }
    return w;
}
template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>&m)const{
    if(theColumns!=m.theRows){
        throw matrixSizeMismath("大小不匹配!");
    }
    matrix<T>w(theRows,m.theColumns);
    int idx=0;
    for(int i=1;i<=theRows;i++){
        for(int j=1;j<=m.theColumns;j++){
            T sum=0;
            for(int h=1;h<=theColumns;h++){
                sum+=element[anti_mapping(i,h,*this)]*m.element[anti_mapping(h,j,m)];
            }
            w.element[idx++]=sum;
        }
    }
    return w;
}
template<class T>
matrix<T>& matrix<T>::operator+=(const T&e){
    for(int i=0;i<theColumns*theRows;i++){
        element[i]+=e;
    }
    return *this;
}
template<class C>
int anti_mapping(int r,int c,const matrix<C>&m){
    int idx=(r-1)*m.theColumns+c-1;
    return idx;
}
template<class C>
ostream& operator<<(ostream&o,const matrix<C>&m){
    for(int i=1;i<=m.theRows;i++){
        for(int j=1;j<=m.theColumns;j++){
            o<<m.element[anti_mapping(i,j,m)]<<"\t";
        }
        o<<endl;
    }
    o<<endl;
    return o;
}
template<class C>
istream& operator>>(istream&in,matrix<C>&m){
    for(int i=0;i<m.theColumns*m.theRows;i++){
        in>>m.element[i];
    }
    return in;
}

int main(){
    try{
        int c,r;
        cout<<"row:";cin>>r;cout<<"column:";cin>>c;
        matrix<int>m1(r,c);cin>>m1;
        cout<<"row:";cin>>r;cout<<"column:";cin>>c;
        matrix<int>m2(r,c);cin>>m2;
        matrix<int>m3;
        char op[3]={0};
        cout<<"operater:";
        cin>>op;
        if(!strcmp(op,"+=\0")){
            m1+=2;cout<<m1;
        }
        else if(!strcmp(op,"-\0")){
            m3=m1-m2;cout<<m3;
        }
        else if(!strcmp(op,"*\0")){
            m3=m1*m2;
            cout<<m3;
        }
        else if(!strcmp(op,"+\0")){
            m3=m1+m2;cout<<m3;
        }
        else{
            throw illegalParameterValue("命令不存在!");
        }
        return 0;
    }
    catch(illegalParameterValue&e){
        cout<<"Except:"<<e.what();
    }
    catch(matrixSizeMismath&e){
        cout<<"Except:"<<e.what();
    }
    catch(exception& e){
        cout<<"Except:"<<e.what();
    }
}