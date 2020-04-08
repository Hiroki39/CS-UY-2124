#include <iostream>
using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial( unsigned numPages )
		: numOfPages(numPages)
	{}
	void displayNumPages() const
	{ cout << numOfPages << endl; }
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
	Book( unsigned numPages)
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
		cout << "Pages: ";
		PrintedMaterial::displayNumPages();
		cout << "Index pages: ";
		cout << numOfIndexPages << endl; 
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
	TextBook t(5430, 23);
	Novel n(213);
	Magazine m(6);

	t.displayNumPages();
	n.displayNumPages();
	m.displayNumPages();

	cout << "\nA PrintedMaterial material object!\n";
	PrintedMaterial pm(2345);
	pm.displayNumPages();

	cout << "\nA PrintedMaterial variable containing a TextBook value\n";
	pm = t; // like putting a t into a vector of PrintedMaterials
	pm.displayNumPages();

	cout << "Try using pointer to base type\n";
	PrintedMaterial* pmPtr;
	pmPtr = &t; // like putting t into a vector but
	            // we are actually putting the address of t
	            // into a vector pointers of pointers to
	            // PrintedMaterials. We'll "say" we are putting

	pmPtr->displayNumPages(); 
}
