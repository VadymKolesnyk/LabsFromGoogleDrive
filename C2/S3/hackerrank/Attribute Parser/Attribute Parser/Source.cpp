#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <list>
using namespace std;

class Attribute
{
private:
	string name;
	string value;
public:
	Attribute(string name, string value);
	string getName();
	string getValue();
};

Attribute::Attribute(string name, string value)
{
	this->name = name;
	this->value = value;
}
string Attribute::getName()
{
	return this->name;
}
string Attribute::getValue()
{
	return this->value;
}

class Tag
{
private:
	string name;
	list<Attribute> att;
public:
	string getName();
	Tag(string name, list<Attribute> att);
	Tag();
	list<Attribute> getAttributes();
};
list<Attribute> Tag::getAttributes()
{
	return this->att;
}

string Tag::getName()
{
	return this->name;
}
Tag::Tag() {}
Tag::Tag(string name, list<Attribute> att)
{
	this->name = name;
	this->att = att;
}

class Node
{
private:
	Tag tag;
	list<Node*> child;
	Node* parent = nullptr;
public:
	list<Node*> getChild();
	Node* getParent();
	string getTagName();
	void addChild(Node* c);
	void addParent(Node* p);
	list<Attribute> getTagAttributes();

	Node();
	Node(string name, list<Attribute> att);
};

list<Attribute> Node::getTagAttributes()
{
	return this->tag.getAttributes();
}

Node::Node(string name, list<Attribute> att): tag(name, att) {}
Node::Node() {}
string Node::getTagName()
{
	return this->tag.getName();
}
void Node::addChild(Node* c)
{
	this->child.push_back(c);
}
void Node::addParent(Node* p)
{
	this->parent = p;
}

list<Node*> Node::getChild()
{
	return this->child;
}

Node* Node::getParent()
{
	return this->parent;
}

int main() {
	int N, Q;
	cin >> N >> Q;
	Node* root = new Node;
	Node* current = root;
	string s;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	for (int i = 0; i < N; i++)
	{
		getline(cin, s);
		if (s[1] != '/')
		{
			list<Attribute> att;
			string name;
			string::size_type pos = s.find(' ', 0);
			if (pos == string::npos)
			{
				pos = s.find('>', 0);
				name = s.substr(1, pos - 1);
			}
			else
			{
				name = s.substr(1, pos - 1);
				while (pos != string::npos)
				{
					string::size_type newpos = s.find(' ', pos + 1);
					string nameatt = s.substr(pos + 1, newpos - pos - 1);
					pos = s.find('"', newpos + 1);
					newpos = s.find('"', pos + 1);
					string valueatt = s.substr(pos + 1, newpos - pos - 1);
					Attribute at(nameatt, valueatt);
					att.push_back(at);
					pos = s.find(' ', pos + 1);
				}
			}
			Node* n = new Node(name, att);
			current->addChild(n);
			n->addParent(current);
			current = n;
		}
		else 
		{
			current = current->getParent();
		}
	}
	vector<string> result(Q, "Not Found!");
	for (int i = 0; i < Q; i++)
	{
		bool b = false;
		string s;
		getline(cin, s);
		string::size_type pos = s.find('~', 0);
		string name = s.substr(0, pos);
		string attname = s.substr(pos + 1, s.length() - pos);
		pos = 0;
		string::size_type newpos = name.find('.', pos);
		while (newpos != string::npos)
		{
			string subname = name.substr(pos, newpos - pos);
			b = false;
			for (Node* n : current->getChild())
			{
				if (n->getTagName() == subname)
				{
					current = n;
					b = true;
					break;
				}
			}
			pos = newpos + 1;
			newpos = name.find('.', pos);
		}
		string subname = name.substr(pos, name.length() - pos);
		b = false;
		for (Node* n : current->getChild())
		{
			if (n->getTagName() == subname)
			{
				current = n;
				b = true;
				break;
			}
		}
		if (b)
		{
			list<Attribute> att = current->getTagAttributes();
			for (Attribute a : att)
			{
				if (a.getName() == attname)
				{
					result[i] = a.getValue();
					break;
				}
			}
		}
		current = root;
	}

	for (string r : result)
	{
		cout << r << endl;
	}

	return 0;
}

/* 
10 0
<t1 a1 = "v1" a2 = "v2">
<t2 a1 = "v1" a2 = "v2" a3 = "v3">
</t2>
<t3>
<t4 a1 = "a1">
</t4>
</t3>
</t1>
<t5 a1 = "v1" a2 = "v2">
</t5>
*/