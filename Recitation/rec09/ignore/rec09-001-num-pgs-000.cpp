#include <iostream>
using namespace std;

class PrintedMaterial {
public:
protected:
private:
	unsigned numOfPages;
};

class Magazine : public PrintedMaterial {
public:
protected:
private:
	unsigned numOfPages;
};

class Book : public PrintedMaterial {
public:
protected:
private:
	unsigned numOfPages;
};

class TextBook : public Book {
public:
protected:
private:
	unsigned numOfPages;
};

class Novel : public Book {
public:
protected:
private:
	unsigned numOfPages;
};

// tester/modeler code
int main()
{
	TextBook t;
	Novel n;
	Magazine m;
}
