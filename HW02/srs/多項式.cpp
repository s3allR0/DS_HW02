#include<iostream>
#include<cmath>
using namespace std;

class Term {
    friend class Polynomial;
private:
    float coef; //係數
    int exp;    // 指數
};
class Polynomial {
    private:
        Term* termArray;// 動態存儲非零項
        int capacity;// termArray 的大小
        int termCount;//當前非零項的數量
    public:
        //創建一個零多項式
        Polynomial(int C= 8):capacity(C),termCount(0){
            termArray=new Term[capacity];
        }
        //輸入
        void input(){
            cout<<"輸入多項式(0作為結尾):\n";
            while(1){
                float coef;
                int exp;
                cin >> coef;
                if (coef==0)break;
                cin >> exp;
                AddTerm(coef,exp);
            }
        }
        //加一個非零項
        void AddTerm(float coef,int exp){
            if (coef==0)return;//零項,結束函數
            for (int i=0;i<termCount;i++){
                if (termArray[i].exp==exp){//如果係數相同
                    termArray[i].coef+=coef;//兩項相加合併
                    if (termArray[i].coef==0){ // 如果係數相加後為零，移除該項
                        for (int j = i;j<termCount - 1;j++) {
                            termArray[j]=termArray[j+1];
                        }
                        termCount-=1;
                    }
                    return;
                }
            }
            if (termCount==capacity)Resize(); // 如果容量不足，擴展空間
            termArray[termCount].coef=coef;
            termArray[termCount].exp=exp; 
            termCount++;
        }
        //擴充陣列大小
        void Resize() {
            capacity *= 2;
            Term* newArray = new Term[capacity];
            for (int i = 0; i < termCount; ++i) {
                newArray[i] = termArray[i];
            }
            delete[] termArray;
            termArray = newArray;
        }
        //加
        Polynomial Add(Polynomial &other) {
            Polynomial Ans(capacity+other.capacity);//Ans的大小為兩多項式的capacity相加
            for (int i=0;i<termCount;i++) {
                Ans.AddTerm(termArray[i].coef, termArray[i].exp);//先將多項式A當作Ans的原函式
            }
            for (int i=0;i<other.termCount;i++) {
                Ans.AddTerm(other.termArray[i].coef,other.termArray[i].exp);//依靠函式AddTerm完成加法
            }
            return Ans;
        }
        //乘
        Polynomial Mult(Polynomial& other) {
            Polynomial Ans(capacity*other.capacity);//Ans的大小為兩多項式的capacity相乘
            for (int i = 0;i< termCount;i++) {
                for (int j = 0; j <other.termCount;j++) {
                    float newCoef=termArray[i].coef*other.termArray[j].coef;//把係數相乘
                    int newExp=termArray[i].exp+other.termArray[j].exp;//指數相加
                    Ans.AddTerm(newCoef, newExp);//送進去
                }
            }
            return Ans;
        }
        //f(x)
        float Eval(float x) {
            float Ans = 0;
            for (int i = 0; i < termCount; i++) {//把每一項帶入X,加起來
                Ans += termArray[i].coef * pow(x, termArray[i].exp);
            }
            return Ans;
        }
        //印
        void Print(){
            if (termCount==0){
                cout<<"0"<<'\n';
                return;
            }
            for (int i = 0;i<termCount; i++){
                if (i > 0&&termArray[i].coef>0)cout<<"+";
                cout<<termArray[i].coef<<"x^"<<termArray[i].exp;
            }
            cout<<'\n';
        }
};
int main() {
    Polynomial poly_A, poly_B;
    cout << "輸入第一個多項式";
    poly_A.input();
    cout << "輸入第二個多項式";
    poly_B.input();
    cout << "第一個多項式為:";
    poly_A.Print();
    cout << "第二個多項式為:";
    poly_B.Print();
    cout << "poly_A+poly_B=";
    Polynomial sum = poly_A.Add(poly_B);
    sum.Print();
    cout << "poly_A*poly_B=";
    Polynomial pro = poly_A.Mult(poly_B);
    pro.Print();
    float x;
    cout << "輸入X=";
    cin >> x;
    float rt_A = poly_A.Eval(x), rt_B = poly_B.Eval(x);
    cout << "poly_A:f(" << x << ")=" << rt_A<<"\n";
    cout << "poly_B:f(" << x << ")=" << rt_B;
}