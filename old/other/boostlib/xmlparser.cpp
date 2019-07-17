#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <utility>
#include <set>

class foo{
    std::string name;
    int i;
    float f;

public:
    foo():name(""), i(0), f(0){};
    foo(std::string str, int i, float f);
    const std::string &get_str() const      {   return name;         }
    void set_str(const std::string &str)    {   foo::name = str;     }
    int get_i() const                       {   return i;            }
    void set_i(int i)                       {   foo::i = i;          }
    float get_f() const                     {   return f;            }
    void set_f(float f)                     {   foo::f = f;          }

    friend std::ostream &operator<<(std::ostream &os, const foo &foo1);
    bool operator==(const foo &rhs) const;
    bool operator<(const foo &rhs) const;
    bool operator>(const foo &rhs) const;
    bool operator<=(const foo &rhs) const;
    bool operator>=(const foo &rhs) const;
    bool operator!=(const foo &rhs) const;


};

foo::foo(std::string str, int i, float f) : name(std::move(str)), i(i), f(f) {}
std::ostream &operator<<(std::ostream &os, const foo &foo1) {
    os << "name: " << foo1.name << " i: " << foo1.i << " f: " << foo1.f;
    return os;
}

bool foo::operator==(const foo &rhs) const {
    return name == rhs.name &&
           i == rhs.i &&
           f == rhs.f;
}

bool foo::operator!=(const foo &rhs) const {
    return !(rhs == *this);
}

bool foo::operator<(const foo &rhs) const {
    return name < rhs.name;
}

bool foo::operator>(const foo &rhs) const {
    return rhs < *this;
}

bool foo::operator<=(const foo &rhs) const {
    return !(rhs < *this);
}

bool foo::operator>=(const foo &rhs) const {
    return !(*this < rhs);
}


int parser() {

    boost::property_tree::ptree tree;
    std::set<foo> f;

    /*foo f1("name1", 1, 1.1F);
    foo f2("name2", 2, 2.2F);
    foo f3("name3", 3, 3.3F);

    f.insert(f1);
    f.insert(f2);
    f.insert(f3);

    std::string in = ".int";
    std::string fl = ".float";
    std::string s;


    for (auto &it: f){
        tree.put(it.get_str(), "");
        s = it.get_str() + in;
        tree.put(s, it.get_i());
        s = it.get_str() + fl;
        tree.put(s, it.get_f());
    }

    boost::property_tree::write_xml("test.xml", tree);*/



    boost::property_tree::read_xml("test.xml", tree);

    for (boost::property_tree::ptree::value_type &it : tree){
        std::string name = it.first;
        std::string path;
        path = name + ".int";
        auto i = tree.get<int>(path);
        path = name + ".float";
        auto fl = tree.get<float>(path);
        std::cout << name << ' ' << i << ' ' << fl << std::endl;
    }
    return 0;
}