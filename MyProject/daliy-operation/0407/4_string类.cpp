#include <iostream>
#include <cstring>
using namespace std;


int main(int argc, char const *argv[])
{
    string s1;
    string s2("what's up");
    string s3(10,'a');
    string s4(s2);
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;

 /*   cin >> s1;
    cout << s1 << endl;
    s1 += "hxx";
    cout << s1 << endl;
    s2 += s3;
    cout << s2 << endl;

    string s("nihaoya");
    cout << s[3] << endl;

    s[1] = 'y';
    cout << s << endl;
    cout << s.at(1) << endl;

    try
    {
        cout << s.at(10) << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(exception& e)
    {
        cout << e.what() <<endl;
    }

    char buf[32] = {0};
    string s5("helloworld");
    s5.copy(buf,5,2);
    cout << buf << endl;
*/
/*    string s("helloworld");
    cout << s.length() << endl;
    if (s.empty())
    {
        cout << "字符串为空" <<endl;
    }
    else
    {
        cout << "字符串不空"<<endl;
    }*/
/*
    string s("what's up");

    s = "hello";
    cout << s << endl;
    const char *ss = "this is a cat";

    s.assign(ss);
    cout << s << endl;

    s.assign(ss,4);
    cout << s << endl;
    s.assign(6,'h');
    cout << s << endl;

*/
/*
    string s("helloworld");
    string ss("what's up");
    s += "111";
    cout<< s << endl;
    const char *sss = "haixx";
    s.append(sss);
    cout << s << endl;
    s.append(sss,2);// 把sss的前两个字符接到s后面；
    cout << s << endl;

    s.append(ss);
    cout << s << endl;
    s.append(ss,4,2);
    cout << s << endl;
    s.append(10,'l');
    cout << s << endl;
*/
    string s("helloworld");
    string ss("nihaoya");
    if (ss.compare(s) > 0)
    {
        cout<< "ss > s" << endl;
    }
    else
    {
        cout << "ss < s" << endl;
    }
    cout << s.substr() <<endl;
    cout << s.substr(5,4) <<endl; //从第五个开始连续4个；

    int p;
    string sa("hello");
    string ssa("world");
    p = sa.find("o");
    cout<< p << endl;
    p = sa.find("x");
    cout<< p << endl;
    p = sa.find("ll");
    cout<< p << endl;

    p = sa.find(ssa);
    cout<< p << endl;
    p = sa.rfind('o');
    cout << p << endl;

    sa.replace(2,4,"hxx");
    cout << sa << endl;
    sa.replace(5,4,ssa);
    cout << sa << endl;

    string str("helloworldhelloworldhelloworldhelloworldhelloworldhelloworldhelloworldhelloworld");
    p = str.find("world");
    while (p != -1)
    {
        str.replace(p,5,"xxx");
        p = str.find("world");
    }
    cout << str << endl;

    string r("helloworld");
    string r1("what's up");
    r.insert(0,r1);
    cout<<r<<endl;
    r.insert(10,r1);
    cout << r << endl;
    r.insert(10,5,'x');
    cout << r << endl;
    r.erase(0,10);
    cout << r <<endl;
    return 0;
}
