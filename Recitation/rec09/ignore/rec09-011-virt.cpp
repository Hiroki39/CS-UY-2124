#include <iostream>
using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial( unsigned numPages )
		: numOfPages(numPages)
	{}
	virtual
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

	pm = t; // like putting a TextBook into a vector of PrintedMaterials
	pm.displayNumPages();

	cout << "\nUsing PrintedMaterial* to \"store\" a TextBook object\n";
	cout << "Now with the virtual mechanism involved\n";
          // should work now that the virtual mechanism is being invoked
	PrintedMaterial* pmPtr;
	pmPtr = &t; // like putting a t into a vector
	            // of pointers to PrintedMaterial
	            // (that is, pointers to the Base class)
	pmPtr->displayNumPages();
}
