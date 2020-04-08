#include <iostream>
using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial( unsigned numPages )
		: numOfPages(numPages)
	{}
	void displayNumPages() const
	{ cout << numOfPages; }
protected:
private:
	unsigned numOfPages;
};

class Magazine : public PrintedMaterial {
public:
	Magazine( unsigned numPages )
		: PrintedMaterial(numPages)
	{}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book( unsigned numPages )
		: PrintedMaterial(numPages)
	{}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook( unsigned numPages, unsigned numIndxPgs  )
		: Book(numPages),
		  numOfIndexPages(numIndxPgs)
	{}
	void displayNumPages() const
	{
		cout << numOfIndexPages << endl;
		cout << numOfPages;
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel( unsigned numPages )
		: Book(numPages)
	{}
protected:
private:
};

// tester/modeler code
int main()
{
	TextBook t(5430, 234);
	Novel n(213);
	Magazine m(6);

	t.displayNumPages();
	n.displayNumPages();
	m.displayNumPages();
}
