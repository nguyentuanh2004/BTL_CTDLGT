#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <set>

#include "D:\Cpp_Programs\Nam2\ImplementDataStructures\Vector.cpp"
#define endl "\n"
#define int long long
#define TuAnh main
using namespace std;
class Answer {
private:
    Vector<string> ans;
public:
    Answer() {
        ans.assign({"", "", "", ""});
    }
    string getAns(int i) {return ans[i];}
    void setAns(int i, string s) {ans[i] = s;}
    friend istream& operator>> (istream& is, Answer& a) {
        for (int i = 0; i < 4; i++) getline(is, a.ans[i]);
        return is;
    }
    friend ostream& operator<< (ostream& os, Answer& a) {
        for (int i = 0; i < 4; i++) os << a.ans[i] << endl;
        return os;
    }
};
class Test {
private:
    string Question;
    Answer Ans;
    int correctAns;
public:
    Test() {}
    string getQs() {return Question;}
    string getAnswer(int i) {return Ans.getAns(i);}
    int getCorrectAns() {return correctAns;}
    void setCorrectAns(int x) {correctAns = x;}
    void setAnswer(int i, string s) {Ans.setAns(i, s);}
    friend istream& operator>> (istream& is, Test& t) {
        getline(is, t.Question);
        is >> t.Ans;
        is >> t.correctAns;
        is.ignore();
        return is;
    }
    friend ostream& operator<< (ostream& os, Test& t) {
        os << t.Question << endl;
        os << t.Ans;
        os << t.correctAns;
        return os;
    }
};
TuAnh() {
    ifstream ifs; ofstream ofs;
    ifs.open("input_26.txt");
    ofs.open("output_26.txt");
    int n; ifs >> n; ifs.ignore();
    Vector<Test> LTest;
    for (int i = 0; i < n; i++) {
        Test temp;
        ifs >> temp;
        LTest.push_back(temp);
    }
    for (int i = 0; i < n; i++) {
        ofs << LTest[i] << endl;
    }

    srand(time(NULL));

    int k;
    do {
        cout << "Enter number of questions of new test: ";
        cin >> k;
    } while (k > n);

    Vector<Test> newTest;

    set<int> se;
    while (se.size() < k) {
        int num = rand();
        num %= n;
        se.insert(num);
    }

    for (auto x : se) {
        newTest.push_back(LTest[x]);
    }

    for (int i = 0; i < newTest.size(); i++) {
        int num = rand();
        num %= 4;
        if (num == newTest[i].getCorrectAns()) newTest[i].setCorrectAns(3 - num);
        else if (3 - num == newTest[i].getCorrectAns()) newTest[i].setCorrectAns(num);
        string tg1 = newTest[i].getAnswer(num);
        string tg2 = newTest[i].getAnswer(3 - num);
        newTest[i].setAnswer(num, tg2);
        newTest[i].setAnswer(3 - num, tg1);
    }
    //for (auto x : newTest) cout << x << endl;

    int user_point = 0;
    for (int i = 0; i < newTest.size(); i++) {
        cout << newTest[i].getQs() << endl;
        for (int j = 0; j < 4; j++) {
            cout << j << ". " << newTest[i].getAnswer(j) << endl;
        }
        int user_ans; cin >> user_ans;
        if (user_ans == newTest[i].getCorrectAns()) ++user_point;
    }

    cout << "You got " << user_point << " point! Congrats!!!";

}